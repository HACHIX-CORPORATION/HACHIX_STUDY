package main

import (
	"log"

	"gotrading/app/controllers"
	"gotrading/config"
	"gotrading/utils"
)

func main() {
	utils.LoggingSettings(config.Config.LogFile)
	controllers.StreamIngestionData()
	controllers.StartWebServer()
	log.Println(controllers.StartWebServer())
}
