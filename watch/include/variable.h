#pragma once

#define PULSE_SENSOR_PIN A0
#define DNS_PORT 53

#define NOTIFY_PIN 17

#ifdef CONFIG_WIFI_CONFIG_PATH
  #define WIFI_CONFIG_PATH CONFIG_WIFI_CONFIG_PATH
#else
  #ifndef WIFI_CONFIG_PATH
    #define WIFI_CONFIG_PATH "/wifi_config"
  #endif
#endif

#ifdef CONFIG_WIFI_DEFAULT_SSID
  #define WIFI_DEFAULT_SSID CONFIG_WIFI_DEFAULT_SSID
#else
  #ifndef WIFI_DEFAULT_SSID
    #define WIFI_DEFAULT_SSID "ElderCareWatch"
  #endif
#endif

#ifdef CONFIG_WIFI_DEFAULT_PASSWORD
  #define WIFI_DEFAULT_PASSWORD CONFIG_WIFI_DEFAULT_PASSWORD
#endif

const char HOME_PAGE[] PROGMEM =
    "<!DOCTYPE html><html><head><title>ElderCareWatch Wifi 設定</title><meta "
    "name='viewport' content='width=device-width, "
    "initial-scale=1'/"
    "><style>html{font-family:Arial,sans-serif}h1{text-align:center;background-"
    "color:#0a1128;font-size:1.8rem;color:white;padding:20px;margin:0}body{"
    "margin:0}.card{background-color:white;box-shadow:2px 2px 12px 1px "
    "rgba(140,140,140,.5)}form{padding:10px}input[type='submit']{border:none;"
    "color:#fefcfb;background-color:#034078;padding:8px;margin-bottom:10px;"
    "font-size:16px;width:100px;border-radius:4px;transition-duration:.4s;"
    "cursor:pointer}input[type='submit']:hover{background-color:#0f5697}input{"
    "width:90%;padding:5px;margin:5px;border:1px solid "
    "#ccc;border-radius:4px}label{font-size:1.2rem} "
    "</style></head><body><h1>ElderCareWatch Wifi 設定</h1><div style='width: "
    "100%'><div style='margin: 20px auto; width: 90%; max-width: 800px'><div "
    "class=card><form action=/ method=POST><label "
    "for=ssid>SSID</label><br/><input type=text list=sl id=ssid "
    "name='ssid'/><br/><label for=password>Password</label><br/><input "
    "type=text id=password name='password'/><br/><input type=submit "
    "value='Submit'/></form><datalist "
    "id=sl></datalist></div></div></div><script>(()=>{const "
    "e=document.getElementById('sl');new "
    "EventSource('/"
    "events').addEventListener('wifi_info',(({data:n})=>{e.innerHTML='',(n="
    "JSON.parse(n)).forEach((({ssid:n})=>{var "
    "t=document.createElement('option');t.value=n,e.appendChild(t)}))}))})(); "
    "</script></body></html>";
