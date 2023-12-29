#include <sMQTTBroker.h>
#include <env.h>

class MyBroker:public sMQTTBroker
{
public:
    bool onEvent(sMQTTEvent *event) override
    {
        switch(event->Type()) {
          case NewClient_sMQTTEventType: {
                  sMQTTNewClientEvent *e=(sMQTTNewClientEvent*)event;
                  if (e->Login() != MQTT_USERNAME || e->Password() != MQTT_PASSWORD) {
                      return false; 
                  }
              }
              break;
          case LostConnect_sMQTTEventType:
              WiFi.reconnect();
        }
        return true;
    }
};

MyBroker broker;

void setup()
{
    Serial.begin(115200);
    const char* ssid = WIFI_SSID;         
    const char* password = WIFI_PASSWORD; 
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
    
    const unsigned short mqttPort=1883;
    broker.init(mqttPort);
}

void loop() {
    broker.update();
}
