#include "trackle_esp32_wifi.h"
#include "arduino_secrets.h"

double temperatureTarget = 20.0;
int setTemperatureTarget(const char *temperature)
{
  log_callback("Chiamata funzione setTemperatureTarget", INFO, "main.cpp", NULL, NULL);
  temperatureTarget = atof(temperature);
  return 1;
}

void setup()
{
  Serial.begin(115200);
  trackle.begin(DEVICE_ID, PRIVATE_KEY);
  trackle.post("setTarget", setTemperatureTarget);
  trackle.get("temperature", temperatureTarget);
  trackle.connect(SSID, PASSWORD);
}

void loop()
{
  trackle.loop();
}
