//
//  Created by Flavio Ferrandi on 14/06/21.
//  Copyright © 2021 Flavio Ferrandi. All rights reserved.
//

#ifndef TrackleBase_h
#define TrackleBase_h

#include "trackle.h"
#include <Arduino.h>

#include "mbedtls/platform.h"
#include "mbedtls/error.h"
#include "mbedtls/base64.h"

uint8_t deviceId[DEVICE_ID_LENGTH] = {0x00};
const uint8_t server[PUBLIC_KEY_LENGTH] = {0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42, 0x00, 0x04, 0x2B, 0x19, 0x9D, 0xC9, 0xF2, 0xB0, 0x2D, 0xD1, 0xF1, 0x7D, 0xF0, 0x2B, 0xD1, 0xEC, 0xD1, 0x57, 0xD6, 0x74, 0x51, 0xD7, 0x9C, 0x09, 0xE1, 0x70, 0x43, 0x4A, 0x5B, 0xC2, 0x40, 0xC0, 0x49, 0x67, 0x34, 0xC8, 0xA4, 0xF8, 0xB4, 0xF7, 0xFB, 0xB4, 0xD0, 0x3F, 0xCC, 0xAF, 0x1F, 0xAA, 0x2E, 0x1D, 0x76, 0x82, 0xCF, 0x3A, 0x1A, 0x0B, 0x42, 0x38, 0x14, 0x6D, 0x54, 0x42, 0x05, 0xDC, 0x4D, 0x27};
uint8_t client[PRIVATE_KEY_LENGTH] = {0x00};
size_t der_size = sizeof(client);
size_t pem_size;

int convert_pem_to_der(const unsigned char *input, size_t ilen,
                       unsigned char *output, size_t *olen)
{
  int ret;
  const unsigned char *s1, *s2, *end = input + ilen;
  size_t len = 0;

  s1 = (unsigned char *)strstr((const char *)input, "-----BEGIN");
  if (s1 == NULL)
    return (-1);

  s2 = (unsigned char *)strstr((const char *)input, "-----END");
  if (s2 == NULL)
    return (-1);

  s1 += 10;
  while (s1 < end && *s1 != '-')
    s1++;
  while (s1 < end && *s1 == '-')
    s1++;
  if (*s1 == '\r')
    s1++;
  if (*s1 == '\n')
    s1++;

  if (s2 <= s1 || s2 > end)
    return (-1);

  ret = mbedtls_base64_decode(NULL, 0, &len, (const unsigned char *)s1, s2 - s1);
  if (ret == MBEDTLS_ERR_BASE64_INVALID_CHARACTER)
    return (ret);

  if (len > *olen)
    return (-1);

  if ((ret = mbedtls_base64_decode(output, len, &len, (const unsigned char *)s1,
                                   s2 - s1)) != 0)
  {
    return (ret);
  }

  *olen = len;

  return (0);
}

static uint32_t getMillis(void);
void log_callback(const char *msg, int level, const char *category, void *attribute, void *reserved);
int connect_cb_udp(const char *address, int port);
int disconnect_cb_udp();
void time_cb(time_t time, unsigned int param, void *reserved);
void default_time_cb(time_t time, unsigned int param, void *reserved)
{
  log_callback("Received time from Trackle", INFO, "Trackle", NULL, NULL);
  time_cb(time, param, reserved);
}
int send_cb_udp(const unsigned char *buf, uint32_t buflen, void *tmp);
int receive_cb_udp(unsigned char *buf, uint32_t buflen, void *tmp);

int my_connect(const char *p_ssid, const char *p_pass); //wifi
int my_connect(uint8_t *mac);                           //ethernet
int my_connect();                                       //ethernet

int my_configure_ip(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1);

void my_loop();

class TrackleEsp32 : public Trackle
{
public:
  void begin(const char *device_id, const char *client_private_key)
  {
    log_callback("Initializing Trackle configuration", INFO, "Trackle", NULL, NULL);

    //check device id if string or char
    uint8_t str_len = strlen(device_id);
    if (str_len >= 24) //convert from string device_id
    {
      for (int i = 0; i < (str_len / 2); i++)
      {
        sscanf(device_id + 2 * i, "%02x", (unsigned int *)&deviceId[i]);
        //printf("bytearray %d: %02x\n", i, deviceId[i]);
      }
    }
    else // device_id already char array
    {
      for (int i = 0; i < 12; i++)
      {
        deviceId[i] = device_id[i];
      }
    }
    setDeviceId(deviceId);

    if (strlen(client_private_key) >= 200) //pem key
    {
      convert_pem_to_der((const unsigned char *)client_private_key, strlen(client_private_key), (unsigned char *)client, &der_size);
    }
    else //der key
    {
      memcpy(client, client_private_key, 121);
    }

    setKeys(server, client);
    setMillis(getMillis);
    setLogCallback(log_callback);
    setLogLevel(WARN);
    setSendCallback(send_cb_udp);
    setReceiveCallback(receive_cb_udp);
    setConnectCallback(connect_cb_udp);
    setDisconnectCallback(disconnect_cb_udp);
    setSystemTimeCallback(default_time_cb);
    setKeepalive(30 * 1000);
  }

  int connect(const char *p_ssid, const char *p_pass)
  {
    log_callback("Starting WiFi connection", INFO, "Trackle", NULL, NULL);
    int res = my_connect(p_ssid, p_pass);
    if (res >= 0)
    {
      return Trackle::connect();
    }
    else
    {
      log_callback("Error with WiFi connection", ERROR, "Trackle", NULL, NULL);
      return res;
    }
  }

  int connect(uint8_t *mac)
  {
    log_callback("Starting Ethernet connection", INFO, "Trackle", NULL, NULL);
    int res = my_connect(mac);
    if (res >= 0)
    {
      return Trackle::connect();
    }
    else
    {
      log_callback("Error with Ethernet connection", ERROR, "Trackle", NULL, NULL);
      return res;
    }
  }

  int connect()
  {
    log_callback("Starting Ethernet connection", INFO, "Trackle", NULL, NULL);
    int res = my_connect();
    if (res >= 0)
    {
      return Trackle::connect();
    }
    else
    {
      log_callback("Error with Ethernet connection", ERROR, "Trackle", NULL, NULL);
      return res;
    }
  }

  int configureIp(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1)
  {
    log_callback("Configuring ip address", INFO, "Trackle", NULL, NULL);
    return my_configure_ip(local_ip, gateway, subnet, dns1);
  }

  void loop()
  {
    my_loop();
    Trackle::loop();
  }
};

TrackleEsp32 Trackle;

#endif /* TrackleBase_h */
