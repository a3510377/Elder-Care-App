#pragma once

#include <Arduino.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>

#ifndef NTP_TIMEZONE
// Greenwich Mean Time(GMT) GMT+8
  #define NTP_TIMEZONE 8
#endif

struct WifiConfig {
  String SSID;
  String Password;
};

static bool onApHandler(AsyncWebServerRequest *request);

class Network {
 public:
  std::unique_ptr<DNSServer> dnsServer;
  std::unique_ptr<AsyncWebServer> server;
  std::unique_ptr<AsyncEventSource> sse;

  void init(void);

  bool setupConfigPortal(void);
  bool startConfigPortal(void);
  bool startConfigPortal(char const *apName, char const *password);

  void handlerRoot(AsyncWebServerRequest *request);

  String getScanWifiInfo(void);
  WifiConfig getWifiConfig(void);

 protected:
  ulong _last_update_time;
  ulong _last_send_scan_time;
  ulong _config_portal_start_time;
};
