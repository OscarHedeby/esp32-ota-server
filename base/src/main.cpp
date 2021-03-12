#include <Arduino.h>
#include <OTAUpdate.cpp>
#include <Network.cpp>


void setup() {
  Serial.begin(115200);

  network::connectToWiFi();

  log_d("Connecting to endpoint");
  while(network::getNetworkingStatus() != 1)
  {
    delay(200);
    log_d(".");
  }
}

void loop() {
  if(ota::getVersionStatus() != 0)
  {
    ota::downloadAndInstallNewVersion();
  }
}