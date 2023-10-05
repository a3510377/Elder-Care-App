#include "network.h"

#include <SPIFFS.h>
#include <WiFi.h>
#include <sntp.h>
#include <time.h>

#include "variable.h"

void Network::init() {
  WifiConfig config = getWifiConfig();
  if (config.SSID == "") startConfigPortal();
  else WiFi.begin(config.SSID, config.Password);

  Serial.print("try connect to SSID: ");
  Serial.print(config.SSID);
  Serial.println(" ::::");
}

void Network::autoUpdateNTP() {
  ulong now = millis();
  if ((_last_update_NTP_time + 18e5 < now || !_last_update_NTP_time) &&
      WiFi.isConnected()) {  // 30min
    _last_update_NTP_time = now;
    Serial.println("start");
    configTime(NTP_TIMEZONE * 60 * 60, 0, "pool.ntp.org", "time.windows.com",
               "time.google.com");
    Serial.println("done");
  }
}

void Network::startConfigPortal() {
  if (!WiFi.isConnected()) {
    WiFi.persistent(false);
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.persistent(true);
  } else WiFi.mode(WIFI_AP_STA);

#ifdef WIFI_DEFAULT_PASSWORD
  WiFi.softAP(WIFI_DEFAULT_SSID, WIFI_DEFAULT_PASSWORD);
#else
  WiFi.softAP(WIFI_DEFAULT_SSID);
#endif

  delay(500);  // wait IP summon
  Serial.print(F("AP IP address: "));
  Serial.println(WiFi.softAPIP());

  _ssid = _password = "";

  dnsServer.reset(new DNSServer());
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(DNS_PORT, "*", WiFi.softAPIP());

  server.reset(new AsyncWebServer(80));
  server->on("/", HTTP_GET,
             [this](AsyncWebServerRequest *request) { handlerRoot(request); });

  server->on("/", HTTP_POST, [this](AsyncWebServerRequest *request) {
    handlerPostRoot(request);
  });

  /* ----- captive portal check. ----- */
  // https://en.wikipedia.org/wiki/Captive_portal#References
  // Apple
  server->on(String(F("/hotspot-detect.html")).c_str(),
             [this](AsyncWebServerRequest *request) { handlerRoot(request); });
  // Windows
  server->on(String(F("/ncsi.txt")).c_str(),
             [this](AsyncWebServerRequest *request) { handlerRoot(request); });
  //  ChromeOS, Android
  server->on(String(F("/generate_204")).c_str(),
             [this](AsyncWebServerRequest *request) { handlerRoot(request); });

  server->onNotFound([](AsyncWebServerRequest *request) {
    if (onApHandler(request)) return;

    request->send(404, "text/plain", "Not Fond!!");
  });

  if (sse != NULL) delete sse;
  sse = new AsyncEventSource("/events");
  sse->onConnect([this](AsyncEventSourceClient *client) {
    client->send(NULL, "hello");
    client->send(getScanWifiInfo().c_str(), "wifi_info");
  });
  server->addHandler(sse).setFilter(ON_AP_FILTER);

  server->begin();
  _config_portal_start_time = millis();

  while (1) {
    // DNS
    dnsServer->processNextRequest();

    if (millis() - _last_send_scan_time > 1e4) {
      _last_send_scan_time = millis();
      sse->send(getScanWifiInfo().c_str(), "wifi_info");
    }

    if (_ssid != "") {
      if (_ssid != _old_ssid || _password != _old_password) {
        _old_ssid = _ssid;
        _old_password = _password;

        if (WiFi.SSID() != "") WiFi.disconnect();

        Serial.print("try connect to SSID: ");
        Serial.print(_ssid);
        Serial.print(", Password: ");
        Serial.println(_password);

        WiFi.begin(_ssid, _password);
        _connect_start_time = millis();
      }

      // 1 and 3 have STA enabled
      if ((WiFiGenericClass::getMode() & WIFI_MODE_STA) != 0) {
        wl_status_t status = WiFi.status();
        if (!status || status >= WL_DISCONNECTED) {
          // TODO Fix this thread unsafe
          if (millis() - _connect_start_time > 1e4) _ssid = "";
        } else {
          Serial.print(F("WiFi connect status: "));
          Serial.println(status);

          // TODO Fix this thread unsafe
          _ssid = "";

          // turn off ap
          WiFi.mode(WIFI_STA);

          if (status == WL_CONNECTED) {
            server.reset();
            dnsServer.reset();
            sse->close();

            saveWifiConfig(WifiConfig {_old_ssid, _password});

            // stop root while loop
            break;
          }
        }
      }
    }

    vTaskDelay(1);
  }
}

// path "/"
// method "POST"
void Network::handlerPostRoot(AsyncWebServerRequest *request) {
  if (onApHandler(request)) return;

  if (_ssid != "") {
    request->send(200, "text/plain;charset=utf-8",
                  "錯誤，當前正在嘗試連接至 " + _ssid + " 請稍後...");
    return;
  }

  if (request->hasParam("ssid", true)) {
    _ssid = request->getParam("ssid", true)->value();
  }
  if (_ssid == "") {
    request->send(400, "text/plain;charset=utf-8", F("錯誤，ssid 是必要參數"));
    return;
  }
  if (request->hasParam("password", true)) {
    _password = request->getParam("password", true)->value();
  }
  request->send(200, "text/plain;charset=utf-8",
                "操作完成，正在嘗試連線至: " + _ssid);
}

// path "/"
// method "GET"
void Network::handlerRoot(AsyncWebServerRequest *request) {
  if (onApHandler(request)) return;

  request->send(200, "text/html;charset=utf-8", HOME_PAGE);
}

String Network::getScanWifiInfo() {
  String json = "[";

  int n = WiFi.scanComplete();
  if (n == WIFI_SCAN_FAILED) WiFi.scanNetworks(true);
  else if (n != WIFI_SCAN_RUNNING) {
    for (int i = 0; i < n; ++i) {
      if (i) json += ",";
      String ssid = WiFi.SSID(i);

      ssid.replace("\"", "\\\"");

      json += "{";
      json += "\"rssi\":" + String(WiFi.RSSI(i));
      json += ",\"ssid\":\"" + ssid + "\"";
      json += ",\"channel\":" + String(WiFi.channel(i));
      json += ",\"secure\":" + String(WiFi.encryptionType(i));
      json += "}";
    }

    WiFi.scanDelete();
    if (WiFi.scanComplete() == WIFI_SCAN_FAILED) {
      WiFi.scanNetworks(true);
    }
  }
  json += "]";

  return json;
}

static bool hasIP(String str) {
  for (size_t i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) return false;
  }
  return true;
}

static bool onApHandler(AsyncWebServerRequest *request) {
  if (!hasIP(request->host())) {
    request->redirect("http://" + request->client()->localIP().toString());
    return true;
  }
  return false;
}

WifiConfig Network::getWifiConfig() {
  WifiConfig config;

  if (SPIFFS.exists(WIFI_CONFIG_PATH)) {
    File configFile = SPIFFS.open(WIFI_CONFIG_PATH, FILE_READ);
    while (configFile.available()) {
      String line = configFile.readStringUntil('\n');
      int separatorIndex = line.indexOf(':');

      if (separatorIndex != -1) {
        String key = line.substring(0, separatorIndex);
        String value = line.substring(separatorIndex + 1);

        value.replace("\r", "");

        if (key == "SSID") config.SSID = value;
        else if (key == "Password") config.Password = value;
      }
    }
  }

  return config;
}

void Network::saveWifiConfig(WifiConfig config) {
  File configFile = SPIFFS.open(WIFI_CONFIG_PATH, FILE_WRITE);
  if (!configFile) {
    Serial.println(F("Error opening wifi config file for writing"));
    return;
  }

  configFile.print("SSID:");
  configFile.println(config.SSID);
  configFile.print("Password:");
  configFile.println(config.Password);
  configFile.close();
}