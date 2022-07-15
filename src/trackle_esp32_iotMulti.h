#ifndef TrackleEthWifi_h
#define TrackleEthWifi_h

#include "trackle_base.h"

#include <ETH.h>

#ifdef ETH_CLK_MODE
#undef ETH_CLK_MODE
#endif
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT

#define ETH_POWER_PIN 5
#define ETH_TYPE ETH_PHY_LAN8720
#define ETH_ADDR 0
#define ETH_MDC_PIN 23
#define ETH_MDIO_PIN 18

static bool eth_connected = false;
static bool wifi_connected = false;
uint8_t network_type = 0; // 0 ethernet; 1 wifi
WiFiUDP udp;
wifi_event_id_t wifi_event_id = 0;

IPAddress server_ip;
int server_port;

void WiFiEvent(WiFiEvent_t event)
{
  switch (event)
  {
  case ARDUINO_EVENT_ETH_START:
    log_callback("Ethernet Started", INFO, "Trackle", NULL, NULL);
    ETH.setHostname("esp32-ethernet");
    break;
  case ARDUINO_EVENT_ETH_CONNECTED:
    log_callback("Ethernet Connected", INFO, "Trackle", NULL, NULL);
    break;
  case ARDUINO_EVENT_ETH_GOT_IP:
    log_callback("Ethernet MAC", INFO, "Trackle", NULL, NULL);
    log_callback(ETH.macAddress().c_str(), INFO, "Trackle", NULL, NULL);
    log_callback("Ethernet IPv4", INFO, "Trackle", NULL, NULL);
    log_callback(ETH.localIP().toString().c_str(), INFO, "Trackle", NULL, NULL);
    eth_connected = true;
    break;
  case ARDUINO_EVENT_ETH_DISCONNECTED:
    log_callback("Ethernet Disconnected", INFO, "Trackle", NULL, NULL);
    eth_connected = false;
    break;
  case ARDUINO_EVENT_ETH_STOP:
    log_callback("Ethernet Stopped", INFO, "Trackle", NULL, NULL);
    eth_connected = false;
    break;
  case ARDUINO_EVENT_WIFI_STA_START:
    log_callback("WIFI Started", INFO, "Trackle", NULL, NULL);
    WiFi.setHostname("esp32-WiFi");
    break;
  case ARDUINO_EVENT_WIFI_STA_CONNECTED:
    log_callback("WIFI Connected", INFO, "Trackle", NULL, NULL);
    break;
  case ARDUINO_EVENT_WIFI_STA_GOT_IP:
    log_callback("WiFi MAC", INFO, "Trackle", NULL, NULL);
    log_callback(WiFi.macAddress().c_str(), INFO, "Trackle", NULL, NULL);
    log_callback("WiFi IPv4", INFO, "Trackle", NULL, NULL);
    log_callback(WiFi.localIP().toString().c_str(), INFO, "Trackle", NULL, NULL);
    wifi_connected = true;
    break;
  case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
    log_callback("WiFi Disconnected", INFO, "Trackle", NULL, NULL);
    wifi_connected = false;
    break;
  case ARDUINO_EVENT_WIFI_STA_STOP:
    log_callback("WiFi Stopped", INFO, "Trackle", NULL, NULL);
    wifi_connected = false;
    break;
  default:
    break;
  }
}

void startWifi(const char *p_ssid, const char *p_pass)
{
  digitalWrite(ETH_POWER_PIN, LOW);
  WiFi.begin(p_ssid, p_pass);
  network_type = 1;
}

void startEth()
{
  WiFi.disconnect();
  digitalWrite(ETH_POWER_PIN, HIGH);
  ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
  network_type = 0;
}

static uint32_t getMillis(void)
{
  return millis();
}

void log_callback(const char *msg, int level, const char *category, void *attribute, void *reserved)
{
  printf("(%d) %s %s\n", level, category, msg);
}

int connect_cb_udp(const char *address, int port)
{
  int ret = -1;
  // printf("connect_cb_udp\n");
  server_port = port;
  udp.begin(server_port);
  udp.setTimeout(100);

  if (eth_connected || wifi_connected)
  {
    ret = WiFi.hostByName(address, server_ip);
    // printf("ret: %d, %s %d.%d.%d.%d\n", ret, address, server_ip[0], server_ip[1], server_ip[2], server_ip[3]);
    if (ret == 1)
      Trackle.connectionCompleted();
  }
  return ret;
}

int disconnect_cb_udp()
{
  udp.stop();
  return 1;
}

void time_cb(time_t time, unsigned int param, void *reserved)
{
}

int send_cb_udp(const unsigned char *buf, uint32_t buflen, void *tmp)
{
  int sent = 0;
  udp.beginPacket(server_ip, server_port);
  sent = udp.write(buf, buflen);
  udp.endPacket();

  if (sent > 0)
  {
    // printf("sent ");
    // printfln(sent);
  }
  return sent;
}

int receive_cb_udp(unsigned char *buf, uint32_t buflen, void *tmp)
{
  int rcv = 0;
  if (udp.parsePacket())
  {
    rcv = udp.read(buf, buflen);
  }
  if (rcv > 0)
  {
    // printf("rcv ");
    // printfln(rcv);
  }
  return rcv;
}

int my_configure_ip(IPAddress ip, IPAddress gateway, IPAddress subnet, IPAddress dns)
{
  WiFi.config(ip, gateway, subnet, dns);
  ETH.config(ip, gateway, subnet, dns);
  return 1;
}

void configWifiEvents()
{
  if (wifi_event_id <= 0)
    wifi_event_id = WiFi.onEvent(WiFiEvent);
}

int my_connect()
{
  configWifiEvents();
  startEth();
  return 1;
}

int my_connect(const char *p_ssid, const char *p_pass)
{
  configWifiEvents();
  startWifi(p_ssid, p_pass);
  return 1;
}

void my_loop()
{
}

#endif // TrackleEthWifi_h
