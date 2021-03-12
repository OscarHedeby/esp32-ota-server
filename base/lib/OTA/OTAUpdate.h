#pragma once
#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

namespace ota
{
    std::string currentVersion = "0.0.0";

    unsigned long lastVersionUpdateCheck = 600000;

    // This should be changed depending on battery charge and settings
    unsigned long versionUpdateDelay = 600000;

    std::string newestVersionFromServer = "";

    /*
        - This will return the current updating status
        0 = No update available
        1 = New update available
    */
    int getVersionStatus();

    /*
        - When a new version is available, call this function to start download
        - WARNING! This function will block everything until it's done downloading!
        0 = No new version found
        1 = New version downloaded and installed
    */
    int downloadAndInstallNewVersion();
}