#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <PMS.h>
#include <Wire.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define I2C_SCL 23
#define I2C_SDA 22
#define PMS7003_RX 1
#define PMS7003_TX 3

HardwareSerial SerialPMS(1);
PMS pms(SerialPMS);
PMS::DATA data;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_SDA, I2C_SCL);
  SerialPMS.begin(9600, SERIAL_8N1, PMS7003_RX, PMS7003_TX);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true)
      ;
  }
  pms.passiveMode();
  pms.wakeUp();
}

void loop() {
  // byte error, address;
  // int nDevices;
  // Serial.println("Scanning...");
  // nDevices = 0;
  // for (address = 1; address < 127; address++) {
  //   Wire.beginTransmission(address);
  //   error = Wire.endTransmission();
  //   if (error == 0) {
  //     Serial.print("I2C device found at address 0x");
  //     if (address < 16) {
  //       Serial.print("0");
  //     }
  //     Serial.println(address, HEX);
  //     nDevices++;
  //   } else if (error == 4) {
  //     Serial.print("Unknow error at address 0x");
  //     if (address < 16) {
  //       Serial.print("0");
  //     }
  //     Serial.println(address, HEX);
  //   }
  // }
  // if (nDevices == 0) {
  //   Serial.println("No I2C devices found\n");
  // } else {
  //   Serial.println("done\n");
  // }
  // if (pms.read(data)) {
  //   Serial.print("PM 1.0 (ug/m3): ");
  //   Serial.println(data.PM_AE_UG_1_0);

  //   Serial.print("PM 2.5 (ug/m3): ");
  //   Serial.println(data.PM_AE_UG_2_5);

  //   Serial.print("PM 10.0 (ug/m3): ");
  //   Serial.println(data.PM_AE_UG_10_0);

  //   Serial.println();
  // }
  pms.requestRead();
  if (pms.readUntil(data)) {
    Serial.println();

    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();
  }
}
