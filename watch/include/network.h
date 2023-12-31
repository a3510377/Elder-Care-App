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
  String ID;
};

static bool hasIP(String str);
static bool onApHandler(AsyncWebServerRequest *request);

class Network {
 public:
  std::unique_ptr<DNSServer> dnsServer;
  std::unique_ptr<AsyncWebServer> server;
  AsyncEventSource *sse;

  void init(void);
  void autoUpdateNTP(void);

  void startConfigPortal(void);
  void handlerRoot(AsyncWebServerRequest *request);
  void handlerPostRoot(AsyncWebServerRequest *request);
  String getScanWifiInfo(void);

  WifiConfig getWifiConfig(void);
  void saveWifiConfig(WifiConfig config);

  inline String getID() {
    return _id;
  }

 protected:
  ulong _last_update_time;
  ulong _last_send_scan_time;
  ulong _connect_start_time;
  ulong _config_portal_start_time;

  ulong _last_update_NTP_time;

  String _ssid, _password, _id, _old_ssid, _old_password;
};
