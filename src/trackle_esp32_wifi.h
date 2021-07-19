//
//  Created by Flavio Ferrandi on 14/06/21.
//  Copyright © 2021 Flavio Ferrandi. All rights reserved.
//

#ifndef TrackleEsp32Wifi_h
#define TrackleEsp32Wifi_h

#include "trackle_base.h"

#include <WiFi.h>
#include <WiFiUdp.h>
WiFiUDP udp;
IPAddress googleDNS(8, 8, 8, 8);

IPAddress server_ip;
int server_port;

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
  //printf("connect_cb_udp\n");
  server_port = port;
  udp.begin(server_port);
  udp.setTimeout(100);
  if (WiFi.isConnected())
  {
    ret = WiFi.hostByName(address, server_ip);
    //printf("%s %d.%d.%d.%d\n", address, server_ip[0], server_ip[1], server_ip[2], server_ip[3]);
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
  //printf("time_cb");
}

int send_cb_udp(const unsigned char *buf, uint32_t buflen, void *tmp)
{
  int sent = 0;
  udp.beginPacket(server_ip, server_port);
  sent = udp.write(buf, buflen);
  udp.endPacket();

  if (sent > 0)
  {
    //printf("sent ");
    //printfln(sent);
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
    //printf("rcv ");
    //printfln(rcv);
  }
  return rcv;
}

uint32_t last_check_wifi;
const uint32_t CHECK_WIFI_INTERVAL = 5000;
const char *ssid;
const char *pass;

int my_configure_ip(IPAddress ip, IPAddress gateway, IPAddress subnet, IPAddress dns)
{
  WiFi.config(ip, gateway, subnet, dns);
  return 1;
}

int my_connect(const char *p_ssid, const char *p_pass)
{
  ssid = p_ssid;
  pass = p_pass;
  WiFi.begin(ssid, pass);
  return 1;
}

void my_loop()
{
  if (millis() - last_check_wifi > CHECK_WIFI_INTERVAL)
  {
    last_check_wifi = millis();
    //printf("status: %d\n", WiFi.status());
    if (!WiFi.isConnected())
    {
      //printf("Connecting to %s\n", ssid);
      WiFi.begin(ssid, pass);
    }
  }
}

#endif /* TrackleEsp32Wifi_h */
