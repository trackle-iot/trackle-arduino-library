#include "trackle_esp32_prodino_eth.h"
#include "arduino_secrets.h"
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

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
  Trackle.begin(DEVICE_ID, PRIVATE_KEY);
  Trackle.post("setTarget", setTemperatureTarget);
  Trackle.get("temperature", temperatureTarget);
  Trackle.connect(mac);
}

void loop()
{
  Trackle.loop();
}
