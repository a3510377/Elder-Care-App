#include "network.h"

#include <SPIFFS.h>
#include <WiFi.h>
#include <sntp.h>
#include <time.h>

#include "variable.h"

void Network::init() {
  WiFi.persistent(false);
  setupConfigPortal();

  // WifiConfig config = getWifiConfig();
  // if (config.SSID == "") {
  // }
}

bool Network::setupConfigPortal() {
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

  dnsServer.reset(new DNSServer());
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(DNS_PORT, "*", WiFi.softAPIP());

  server.reset(new AsyncWebServer(80));
  server->on("/", HTTP_GET,
             [this](AsyncWebServerRequest *request) { handlerRoot(request); });

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

  sse.reset(new AsyncEventSource("/events"));
  sse->onConnect([this](AsyncEventSourceClient *client) {
    client->send(NULL, "hello");
    client->send(getScanWifiInfo().c_str(), "wifi_info");
  });
  server->addHandler(sse.get()).setFilter(ON_AP_FILTER);

  server->begin();
  _config_portal_start_time = millis();

  while (1) {
    // DNS
    dnsServer->processNextRequest();

    if (millis() - _last_send_scan_time > 1e4) {
      _last_send_scan_time = millis();
      sse->send(getScanWifiInfo().c_str(), "wifi_info");
    }

    yield();
  }
}

// path "/"
void Network::handlerRoot(AsyncWebServerRequest *request) {
  if (onApHandler(request)) return;

  request->send(
      200, "text/html",
      "<!DOCTYPE html><html><head><title>ElderCareWatch Wifi 設定</title><meta "
      "name=viewport content='width=device-width, "
      "initial-scale=1'/"
      "><style>html{font-family:Arial,sans-serif}h1{text-align:center;"
      "background-color:#0a1128;font-size:1.8rem;color:white;padding:20px;"
      "margin:0}body{margin:0}.card{background-color:white;box-shadow:2px 2px "
      "12px 1px "
      "rgba(140,140,140,.5)}form{padding:10px}input[type='submit']{border:none;"
      "color:#fefcfb;background-color:#034078;padding:8px;margin-bottom:10px;"
      "font-size:16px;width:100px;border-radius:4px;transition-duration:.4s;"
      "cursor:pointer}input[type='submit']:hover{background-color:#0f5697}"
      "input[type='text'],input[type='number']{width:50%;min-width:none;"
      "padding:5px;margin:5px;border:1px solid "
      "#ccc;border-radius:4px}label{font-size:1.2rem}</style></"
      "head><body><h1>ElderCareWatch Wifi 設定</h1><div "
      "style='padding:5%'><div class=card><form action=/ method=POST><label "
      "for=ssid>SSID</label><input type=text list=sl id=ssid "
      "name=ssid/><br/><label for=pass>Password</label><input type=text "
      "id=pass name=pass/><br/><label for=ip>IP</label><input type=text id=ip "
      "name=ip value=''/><br/><label for=gateway>Gateway</label><input "
      "type=text id=gateway name=gateway value=''/><br/><input type=submit "
      "value=Submit/></form><datalist "
      "id=sl></datalist></div></div><script>(()=>{const "
      "e=document.getElementById('sl');new "
      "EventSource('/"
      "events').addEventListener('wifi_info',(({data:n})=>{e.innerHTML='',(n="
      "JSON.parse(n)).forEach((({ssid:n})=>{var "
      "t=document.createElement('option');t.value=n,e.appendChild(t)}))}))})();"
      " </script></body></html>");
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

WifiConfig Network::getWifiConfig() {
  WifiConfig config;

  if (SPIFFS.exists(WIFI_CONFIG_PATH)) {
    File configFile = SPIFFS.open(WIFI_CONFIG_PATH, "r");
    while (configFile.available()) {
      String line = configFile.readStringUntil('\n');
      int separatorIndex = line.indexOf(':');

      if (separatorIndex != -1) {
        String key = line.substring(0, separatorIndex);
        String value = line.substring(separatorIndex + 1);

        if (key == "SSID") config.SSID = value;
        else if (key == "Password") config.Password = value;
      }
    }
  }

  return config;
}

static bool onApHandler(AsyncWebServerRequest *request) {
  if (!request->host()) {
    request->redirect("http://" + request->client()->localIP().toString());
    return true;
  }
  return false;
}
