//------------------------------------------------------------------------------------------------------------------------------------
//Пример управления ШИМ v.1.0
//основной канал автора на ютубе  "НеОбзор58"            https://www.youtube.com/channel/UC6mMZ4GGXMdpSGEy-j1EnxQ
//второй   канал автора на ютубе  "Доступная автоматика" https://www.youtube.com/channel/UCxfwRP66zE4zwn6lgvS6wQg
//сайт проекта http://www.simple-automation.ru/

//
//     желающим поддержать автора: карта Сбера 676280489001157828 получатель Григорий Валерьевич Ц.
//
//------------------------------------------------------------------------------------------------------------------------------------


//----------общие переменные и константы----------------------------------------------------------------------------------------------
//назначаем пины
const byte swt1_pin PROGMEM = D1;//
const byte swt2_pin PROGMEM = D2;//


const byte pinBuiltinLed PROGMEM = D4; //GPIO2

//----------работа с wi-fi файловой системой EEPROM-----------------------------------------------------------------------------------
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
ESP8266WebServer server(80);
bool ApMode, AccessMode;
String AccessLogin, AccessPassword;
String ssid, password, domain;
uint8_t ip1, ip2, ip3, ip4;
uint8_t ms1, ms2, ms3, ms4;
uint8_t gt1, gt2, gt3, gt4;
uint8_t dn1, dn2, dn3, dn4;
byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

const char* const ssidAP PROGMEM = "ESP_IRF520vvv";
const char* const passwordAP PROGMEM = "1223334444";

const char configSign[4] = { '#', 'G', 'R', 'S' };
const byte maxStrParamLength = 32;
String NameProg;//для совместимости

//-----------отбор---------------------------------------------------------------------------------------------------------
int8_t direct;
int16_t range1, range2;
int16_t prev_range1, prev_range2;

//--------------------------------------------------------------
String quoteEscape(const String& str)
{
  String result = "";
  int start = 0, pos;

  while (start < str.length()) {
    pos = str.indexOf('"', start);
    if (pos != -1) {
      result += str.substring(start, pos) + F("&quot;");
      start = pos + 1;
    } else {
      result += str.substring(start);
      break;
    }
  }
  return result;
}
//---------------------------------------------
bool readConfig()
{
  uint16_t offset = 0;
  Serial.println(F("Reading config from EEPROM"));
  for (byte i = 0; i < sizeof(configSign); i++)  {
    if (EEPROM.read(offset + i) != configSign[i])
      return false;
  }
  offset += sizeof(configSign);
  offset = readEEPROMString(offset, ssid);
  offset = readEEPROMString(offset, password);
  offset = readEEPROMString(offset, AccessLogin);
  offset = readEEPROMString(offset, AccessPassword);
  offset = readEEPROMString(offset, NameProg);

  EEPROM.get(offset, ApMode); offset += sizeof(ApMode);
  EEPROM.get(offset, AccessMode); offset += sizeof(AccessMode);

  EEPROM.get(offset, ip1);       offset += sizeof(ip1);
  EEPROM.get(offset, ip2);       offset += sizeof(ip2);
  EEPROM.get(offset, ip3);       offset += sizeof(ip3);
  EEPROM.get(offset, ip4);       offset += sizeof(ip4);

  EEPROM.get(offset, ms1);       offset += sizeof(ms1);
  EEPROM.get(offset, ms2);       offset += sizeof(ms2);
  EEPROM.get(offset, ms3);       offset += sizeof(ms3);
  EEPROM.get(offset, ms4);       offset += sizeof(ms4);

  EEPROM.get(offset, gt1);       offset += sizeof(gt1);
  EEPROM.get(offset, gt2);       offset += sizeof(gt2);
  EEPROM.get(offset, gt3);       offset += sizeof(gt3);
  EEPROM.get(offset, gt4);       offset += sizeof(gt4);

  EEPROM.get(offset, dn1);       offset += sizeof(dn1);
  EEPROM.get(offset, dn2);       offset += sizeof(dn2);
  EEPROM.get(offset, dn3);       offset += sizeof(dn3);
  EEPROM.get(offset, dn4);       offset += sizeof(dn4);

  return true;
}
//-------------------------------------
void writeConfig()
{
  uint16_t offset = 0;

  Serial.println(F("Writing config to EEPROM"));
  EEPROM.put(offset, configSign);

  offset += sizeof(configSign);
  offset = writeEEPROMString(offset, ssid);
  offset = writeEEPROMString(offset, password);
  offset = writeEEPROMString(offset, AccessLogin);
  offset = writeEEPROMString(offset, AccessPassword);
  offset = writeEEPROMString(offset, NameProg);

  EEPROM.put(offset, ApMode); offset += sizeof(ApMode);
  EEPROM.put(offset, AccessMode); offset += sizeof(AccessMode);

  EEPROM.put(offset, ip1); offset += sizeof(ip1);
  EEPROM.put(offset, ip2); offset += sizeof(ip2);
  EEPROM.put(offset, ip3); offset += sizeof(ip3);
  EEPROM.put(offset, ip4); offset += sizeof(ip4);

  EEPROM.put(offset, ms1);       offset += sizeof(ms1);
  EEPROM.put(offset, ms2);       offset += sizeof(ms2);
  EEPROM.put(offset, ms3);       offset += sizeof(ms3);
  EEPROM.put(offset, ms4);       offset += sizeof(ms4);

  EEPROM.put(offset, gt1);       offset += sizeof(gt1);
  EEPROM.put(offset, gt2);       offset += sizeof(gt2);
  EEPROM.put(offset, gt3);       offset += sizeof(gt3);
  EEPROM.put(offset, gt4);       offset += sizeof(gt4);

  EEPROM.put(offset, dn1);       offset += sizeof(dn1);
  EEPROM.put(offset, dn2);       offset += sizeof(dn2);
  EEPROM.put(offset, dn3);       offset += sizeof(dn3);
  EEPROM.put(offset, dn4);       offset += sizeof(dn4);

  EEPROM.commit();
}
//-----------------------------------------------------------------------
uint16_t readEEPROMString(uint16_t offset, String& str)
{
  char buffer[maxStrParamLength + 1];
  buffer[maxStrParamLength] = 0;
  for (byte i = 0; i < maxStrParamLength; i++) {
    if (! (buffer[i] = EEPROM.read(offset + i)))
      break;
  }
  str = String(buffer);
  return offset + maxStrParamLength;
}
//-----------------------------------------------------------------------
uint16_t writeEEPROMString(uint16_t offset, const String& str) {
  for (byte i = 0; i < maxStrParamLength; i++) {
    if (i < str.length())
      EEPROM.write(offset + i, str[i]);
    else
      EEPROM.write(offset + i, 0);
  }
  return offset + maxStrParamLength;
}
//-------------------------------------------------------------------------------------------------
//---------------------------WiFi setup functions--------------------------------------------------
//-------------------------------------------------------------------------------------------------
bool setupWiFiAsStation() {
  const uint32_t timeout = 40000;
  uint32_t maxtime = millis() + timeout;

  WiFi.mode(WIFI_STA);

  if (ssid.length() == 0) return false;

  Serial.println(F("Connecting to "));
  Serial.println(ssid);


  WiFi.begin(ssid.c_str(), password.c_str());

  if ((ip1 + ip2 + ip3 + ip4) != 0)
  {
    IPAddress ip(ip1, ip2, ip3, ip4);
    IPAddress subnet(ms1, ms2, ms4, ms4);
    IPAddress dns(dn1, dn2, dn3, dn4);
    IPAddress gateway(gt1, gt2, gt3, gt4);

    WiFi.config(ip, gateway, subnet, dns);

  }

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(pinBuiltinLed, LOW);
    delay(500);
    digitalWrite(pinBuiltinLed, HIGH);
    Serial.print(".");
    if (millis() >= maxtime) {
      Serial.println();
      Serial.println(ssid);
      //Serial.println(password);
      Serial.println(F(" fail!"));
      return false;
    }
  }
  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());


  return true;
}
//----------------------------------------------------------------
void setupWiFiAsAP()
{
  Serial.print(F("Configuring access point "));
  Serial.println(ssidAP);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssidAP, passwordAP);

  Serial.print(F("IP address: "));
  Serial.println(WiFi.softAPIP());



}
//----------------------------------------------------------------
void setupWiFi() {
  if (ApMode || (! setupWiFiAsStation())) setupWiFiAsAP();
  server.begin();

  Serial.println(F("HTTP started"));


}
//------------------------------------
String AddNull (String StrForAdd)
{
  if (StrForAdd.length() == 1)
    return "0" + StrForAdd;
  if (StrForAdd.length() == 0)
    return "00" + StrForAdd;

  return StrForAdd;
}
//--------------------------------------------------------------------------------------
#include "handles.h"
#include "h_switch.h"
#include "Control_direct.h"
#include "upg_spiffs.h"

//---------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  Serial.println();

analogWriteFreq(10000);
  pinMode(pinBuiltinLed, OUTPUT);
  pinMode(swt1_pin, OUTPUT);  digitalWrite(swt1_pin, LOW);
  pinMode(swt2_pin, OUTPUT);  digitalWrite(swt2_pin, LOW);


  prev_range1 = 0;
  range1 = 0;
  
  prev_range2 = 0;
  range2 = 0;
  


  EEPROM.begin(1024);
  if (! readConfig()) Serial.println(F("EEPROM is empty!"));


  setupWiFi();


  //-------------------------------------------------

  server.on("/", handleRoot);
  server.on("/index.html", handleRoot);
  server.on("/switch", h_switch);
  server.on("/save", h_save);
  server.on("/reboot", h_reboot);
  server.on("/wifi", h_wifi);
  server.on("/direct1", h_direct1);
  
  server.onNotFound(handleNotFound);
  server.on("/spiffs", HTTP_GET, handleSPIFFS);
  server.on("/spiffs", HTTP_POST, handleFileUploaded, handleFileUpload);
  server.on("/spiffs", HTTP_DELETE, handleFileDelete);
  server.on("/update", HTTP_GET, handleUpdate);
  server.on("/update", HTTP_POST, handleSketchUpdated, handleSketchUpdate);


  if (! SPIFFS.begin())
  {
    Serial.println(F("Unable to mount SPIFFS!"));
    return;
  }

}
//-------------------------------------------
void loop() {
  const uint32_t timeout = 180000; // 3 min.
  static uint32_t nextTime = timeout;
  static uint32_t nextTimeMQTT = timeout;

  if ((!ApMode) && (WiFi.status() != WL_CONNECTED) && ((WiFi.getMode() == WIFI_STA) || ((int32_t)(millis() - nextTime) >= 0)))  {
    setupWiFi();
    nextTime = millis() + timeout;
  }
  server.handleClient();

  if (direct == 1)  working_direct1();
  else working_stop();

}
//--------------------------------------------------------------------------------------
