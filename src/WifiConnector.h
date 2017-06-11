#include <ESP8266WiFi.h>

class WifiConnector {
private:
  const char* ssid     = "VictorT";
  const char* password = "13940202";

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
