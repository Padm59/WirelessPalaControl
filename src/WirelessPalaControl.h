#ifndef WirelessPalaControl_h
#define WirelessPalaControl_h

#include "Main.h"
#include "base\Utils.h"
#include "base\MQTTMan.h"
#include "base\Application.h"

const char appDataPredefPassword[] PROGMEM = "ewcXoCt4HHjZUvY1";

#include "data\status1.html.gz.h"
#include "data\config1.html.gz.h"

#include <PolledTimeout.h>
#include <Palazzetti.h>

class WebPalaControl : public Application
{
private:
#define HA_MQTT_GENERIC 0

  typedef struct
  {
    byte type = HA_MQTT_GENERIC;
    uint32_t port = 1883;
    char username[128 + 1] = {0};
    char password[150 + 1] = {0};
    struct
    {
      char baseTopic[64 + 1] = {0};
    } generic;
  } MQTT;

#define HA_PROTO_DISABLED 0
#define HA_PROTO_MQTT 1

  typedef struct
  {
    byte protocol = HA_PROTO_DISABLED;
    char hostname[64 + 1] = {0};
    uint16_t uploadPeriod = 60;
    MQTT mqtt;
  } HomeAutomation;

  HomeAutomation m_ha;
  int m_haSendResult = 0;
  WiFiClient m_wifiClient;

  Palazzetti m_Pala;

  bool m_needPublish = false;
  Ticker m_publishTicker;

  MQTTMan m_mqttMan;

  int myOpenSerial(uint32_t baudrate);
  void myCloseSerial();
  int mySelectSerial(unsigned long timeout);
  size_t myReadSerial(void *buf, size_t count);
  size_t myWriteSerial(const void *buf, size_t count);
  int myDrainSerial();
  int myFlushSerial();
  void myUSleep(unsigned long usecond);

  void mqttConnectedCallback(MQTTMan *mqttMan, bool firstConnection);
  void mqttCallback(char *topic, uint8_t *payload, unsigned int length);
  void publishTick();

  void SetConfigDefaultValues();
  void ParseConfigJSON(DynamicJsonDocument &doc);
  bool ParseConfigWebRequest(AsyncWebServerRequest *request);
  String GenerateConfigJSON(bool forSaveFile);
  String GenerateStatusJSON();
  bool AppInit(bool reInit);
  const uint8_t *GetHTMLContent(WebPageForPlaceHolder wp);
  size_t GetHTMLContentSize(WebPageForPlaceHolder wp);
  void AppInitWebServer(AsyncWebServer &server, bool &shouldReboot, bool &pauseApplication);
  void AppRun();

public:
  WebPalaControl(char appId, String fileName);
};

#endif
