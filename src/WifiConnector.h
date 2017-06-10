#include <ESP8266WiFi.h>

class WifiConnector {
private:
  const char* ssid     = "luca";
  const char* password = "123456781";

  const char* host = "109.185.158.161";
  const char* streamId   = "....................";
  const char* privateKey = "....................";

  bool connected = false;
  WiFiClient client;


public:
  void initializeConnection();
  bool isConnected();
  void sendRequest(char *link);
};
