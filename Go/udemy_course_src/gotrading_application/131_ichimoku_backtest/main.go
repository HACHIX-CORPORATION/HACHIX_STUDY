package main

import (
    "import log"

	"gotrading/app/controllers"
	"gotrading/config"
	"gotrading/utils"
)

func main(){
	utils.LoggingSettings(config.Config.LogFile)
	controllers.StreamIngestionData()
    log.Println(controllers.StartWebServer())
}
