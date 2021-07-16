#include "trackle_esp32_iotMulti.h"
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
  //trackle.configureIp(0U, 0U, 0U, 0U);  //optional set ip, gateway, subnet, dns
  trackle.connect();
}

void loop()
{
  trackle.loop();
}
