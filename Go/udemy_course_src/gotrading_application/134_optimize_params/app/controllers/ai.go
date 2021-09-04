package controllers

import (
	"fmt"
	"log"
	"strconv"
	"strings"
	"time"

	"github.com/markcheno/go-talib"
	"golang.org/x/sync/semaphore"

	"gotrading/app/models"
	"gotrading/bitflyer"
	"gotrading/config"
	"gotrading/tradingalgo"
)

type AI struct {
	API                  *bitflyer.APIClient
	ProductCode          string
	CurrencyCode         string
	CoinCode             string
	UsePercent           float64
	MinuteToExpires      int
	Duration             time.Duration
	PastPeriod           int
	SignalEvents         *models.SignalEvents
	OptimizedTradeParams *models.TradeParams
	TradeSemaphore       *semaphore.Weighted
	StopLimit            float64
	StopLimitPercent     float64
	BackTest             bool
	StartTrade           time.Time
}

// TODO Use mutex
var Ai *AI

func NewAI(productCode string, duration time.Duration, pastPeriod int, UsePercent float64) *AI {
	apiClient := bitflyer.New(config.Config.ApiKey, config.Config.ApiSecret)
	var signalEvents *models.SignalEvents
	if config.Config.BackTest {
		signalEvents = models.NewSignalEvents()
	} else {
		signalEvents = models.GetSignalEventsByCount(1)
	}
	codes := strings.Split(productCode, "_")
	Ai = &AI{
		API:              apiClient,
		ProductCode:      productCode,
		CoinCode:         codes[0],
		CurrencyCode:     codes[1],
		UsePercent:       UsePercent,
		MinuteToExpires:  1,
		PastPeriod:       pastPeriod,
		Duration:         duration,
		SignalEvents:     signalEvents,
		TradeSemaphore:   semaphore.NewWeighted(1),
		BackTest:         config.Config.BackTest,
		StartTrade:       time.Now().UTC(),
		StopLimitPercent: config.Config.StopLimitPercent,
	}

	Ai.UpdateOptimizeParams()
	return Ai
}

func (ai *AI) Buy(candle models.Candle) (childOrderAcceptanceID string, isOrderCompleted bool) {
	if ai.BackTest {
		cloudBuy := ai.SignalEvents.Buy(ai.ProductCode, candle.Time, candle.Close, 1.0, false)
		return "", cloudBuy
	}

	// TODO
	return childOrderAcceptanceID, isOrderCompleted
}

func (ai *AI) Sell(candle models.Candle) (childOrderAcceptanceID string, isOrderCompleted bool) {
	if ai.BackTest {
		couldSell := ai.SignalEvents.Sell(ai.ProductCode, candle.Time, candle.Close, 1.0, false)
		return "", couldSell
	}

	// TODO
	return childOrderAcceptanceID, isOrderCompleted
}

func (ai *AI) UpdateOptimizeParams() {
	df, _ := models.GetAllCandle(ai.ProductCode, ai.Duration, ai.PastPeriod)
	ai.OptimizedTradeParams = df.OptimizeParams()
	log.Printf("action=UpdateOptimizeParams optimized_trade_params=%+v", ai.OptimizedTradeParams)
}

func (ai *AI) Trade() {
	isAcquire := ai.TradeSemaphore.TryAcquire(1)
	if !isAcquire {
		log.Println("Could not get trade lock")
		return
	}
	defer ai.TradeSemaphore.Release(1)

	params := ai.OptimizedTradeParams

	df, _ := models.GetAllCandle(ai.ProductCode, ai.Duration, ai.PastPeriod)
	lenCandles := len(df.Candles)

	var emaValues1 []float64
	var emaValues2 []float64
	if params.EmaEnable {
		emaValues1 = talib.Ema(df.Closes(), params.EmaPeriod1)
		emaValues2 = talib.Ema(df.Closes(), params.EmaPeriod2)
	}

	var bbUp []float64
	var bbDown []float64
	if params.BbEnable {
		bbUp, _, bbDown = talib.BBands(df.Closes(), params.BbN, params.BbK, params.BbK, 0)
	}

	var tenkan, kijun, senkouA, senkouB, chikou []float64
	if params.IchimokuEnable {
		tenkan, kijun, senkouA, senkouB, chikou = tradingalgo.IchimokuCloud(df.Closes())
	}

	var outMACD, outMACDSignal []float64
	if params.MacdEnable {
		outMACD, outMACDSignal, _ = talib.Macd(df.Closes(), params.MacdFastPeriod, params.MacdSlowPeriod, params.MacdSignalPeriod)
	}

	var rsiValues []float64
	if params.RsiEnable {
		rsiValues = talib.Rsi(df.Closes(), params.RsiPeriod)
	}

	for i := 1; i < lenCandles; i++ {
		buyPoint, sellPoint := 0, 0
		if params.EmaEnable && params.EmaPeriod1 <= i && params.EmaPeriod2 <= i {
			if emaValues1[i-1] < emaValues2[i-1] && emaValues1[i] >= emaValues2[i] {
				buyPoint++
			}

			// TODO
			//if df.Volumes()[i] > 100 {
			//	buyPoint++
			//}

			if emaValues1[i-1] > emaValues2[i-1] && emaValues1[i] <= emaValues2[i] {
				sellPoint++
			}
		}

		if params.BbEnable && params.BbN <= i {
			if bbDown[i-1] > df.Candles[i-1].Close && bbDown[i] <= df.Candles[i].Close {
				buyPoint++
			}

			if bbUp[i-1] < df.Candles[i-1].Close && bbUp[i] >= df.Candles[i].Close {
				sellPoint++
			}
		}

		if params.MacdEnable {
			if outMACD[i] < 0 && outMACDSignal[i] < 0 && outMACD[i-1] < outMACDSignal[i-1] && outMACD[i] >= outMACDSignal[i] {
				buyPoint++
			}

			if outMACD[i] > 0 && outMACDSignal[i] > 0 && outMACD[i-1] > outMACDSignal[i-1] && outMACD[i] <= outMACDSignal[i] {
				sellPoint++
			}
		}

		//http://stock.kikuchisan.net/chart.html
		if params.IchimokuEnable {
			if chikou[i-1] < df.Candles[i-1].High && chikou[i] >= df.Candles[i].High &&
				senkouA[i] < df.Candles[i].Low && senkouB[i] < df.Candles[i].Low &&
				tenkan[i] > kijun[i] {
				buyPoint++
			}

			if chikou[i-1] > df.Candles[i-1].Low && chikou[i] <= df.Candles[i].Low &&
				senkouA[i] > df.Candles[i].High && senkouB[i] > df.Candles[i].High &&
				tenkan[i] < kijun[i] {
				sellPoint++
			}
		}

		if params.RsiEnable && rsiValues[i-1] != 0 && rsiValues[i-1] != 100 {
			if rsiValues[i-1] < params.RsiBuyThread && rsiValues[i] >= params.RsiBuyThread {
				buyPoint++
			}

			if rsiValues[i-1] > params.RsiSellThread && rsiValues[i] <= params.RsiSellThread {
				sellPoint++
			}
		}

		if buyPoint > 0 {
			log.Printf("action=Trade status=buy status=start sginal_events=%+v back_test=%t", ai.SignalEvents, ai.BackTest)
			_, isOrderCompleted := ai.Buy(df.Candles[i])
			if !isOrderCompleted {
				continue
			}
			ai.StopLimit = df.Candles[i].Close * ai.StopLimitPercent
			log.Printf("action=Trade status=buy status=%t sginal_events=%+v back_test=%t", isOrderCompleted, ai.SignalEvents, ai.BackTest)

		}

		if sellPoint > 0 || ai.StopLimit > df.Candles[i].Close {
			log.Printf("action=Trade status=sell status=start sginal_events=%+v back_test=%t", ai.SignalEvents, ai.BackTest)
			_, isOrderCompleted := ai.Sell(df.Candles[i])
			if !isOrderCompleted {
				continue
			}
			ai.StopLimit = 0.0
			// Go routine
			ai.UpdateOptimizeParams()
			log.Printf("action=Trade status=sell status=end sginal_events=%+v back_test=%t", ai.SignalEvents, ai.BackTest)
		}
	}
}

func (ai *AI) APISize(size float64) float64 {
	fixSize, err := strconv.ParseFloat(fmt.Sprintf("%.7f", size), 64)
	if err != nil {
		log.Printf("action=APISize err=%s", err)
		return size
	}
	return fixSize
}

func (ai *AI) GetAvaiableBalance() (availableCurrency, availableCoin float64) {
	// Only Bitflyer user
	balances, err := ai.API.GetBalance()
	if err != nil {
		log.Printf("action=GetAvaiableBalance err=%s", err)
		return
	}
	for _, balance := range balances {
		if balance.CurrentCode == ai.CurrencyCode {
			availableCurrency = balance.Available
		} else if balance.CurrentCode == ai.CoinCode {
			availableCoin = balance.Available
		}
	}
	log.Printf("action=GetAvaiableBalance availableCurrency=%f availableCoin=%f", availableCurrency, availableCoin)
	return availableCurrency, availableCoin
}

func (ai *AI) WaitUntilOrderComplete(childOrderAcceptanceID string, executeTime time.Time) bool {
	// Only Bitflyer user
	log.Printf("action=WaitUntilOrderComplete WaitUntilOrderComplete=%s", childOrderAcceptanceID)
	params := map[string]string{
		"product_code":              ai.ProductCode,
		"child_order_acceptance_id": childOrderAcceptanceID,
	}

	expire := time.After(time.Minute + (20 * time.Second))
	interval := time.Tick(15 * time.Second)
	return func() bool {
		for {
			select {
			case <-expire:
				log.Print("action=WaitUntilOrderComplete status=expired")
				return false
			case <-interval:
				listOrders, err := ai.API.ListOrder(params)
				if err != nil {
					log.Println("action=WaitUntilOrderComplete err=%s", err)
					return false
				}
				if len(listOrders) == 0 {
					return false
				}
				order := listOrders[0]
				log.Printf("action=WaitUntilOrderComplete childOrderAcceptanceID=%s order=%+v", childOrderAcceptanceID, order)
				if order.ChildOrderState == "COMPLETED" {
					if order.Side == "BUY" {
						couldBuy := ai.SignalEvents.Buy(ai.ProductCode, executeTime, order.AveragePrice, order.Size, true)
						if !couldBuy {
							log.Fatalf("action=WaitUntilOrderComplete status=buy childOrderAcceptanceID=%s order=%+v", childOrderAcceptanceID, order)
						}
						return couldBuy
					}

					if order.Side == "SELL" {
						couldSell := ai.SignalEvents.Sell(ai.ProductCode, executeTime, order.AveragePrice, order.Size, true)
						if !couldSell {
							log.Fatalf("action=WaitUntilOrderComplete status=sell childOrderAcceptanceID=%s order=%+v", childOrderAcceptanceID, order)
						}
						return couldSell
					}
					return false
				}
			}
		}
	}()
}
