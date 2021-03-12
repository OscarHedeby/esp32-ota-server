#include "OTAUpdate.h"

namespace ota
{
    int getVersionStatus()
    {
        /*
            We want first to read last time we checked the server for a new version.
            If it's older than x, then we want to check the server for a new version.
            If we get a heigher version number than what we have currently installed,
            we download it and install it.
        */

        // We should start by checking our connection
        // We check if it's more than x time since we last checked for a new version
        if ((millis() - lastVersionUpdateCheck) > versionUpdateDelay)
        {
            WiFiClientSecure secureWifiClient;
            HTTPClient http;

            const std::string endpoint = "https://www.my-server/version";

            http.begin(secureWifiClient, endpoint.c_str());

            int httpResponseCode = http.GET();

            // If the responseCode is less than 0, we have a local problem
            // If the responseCode is above 0 it's an http response code
            if (httpResponseCode > 0)
            {
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);
                // We check if a new version is available
                newestVersionFromServer = std::string(http.getString().c_str());
                if (newestVersionFromServer != currentVersion)
                {
                    Serial.print("New version found: ");
                    Serial.println(newestVersionFromServer.c_str());
                    lastVersionUpdateCheck = 0;
                    http.end();
                    return 1;
                }
                Serial.println("No new version found");
            }
            else
            {
                Serial.print("Error code: ");
                Serial.println(httpResponseCode);
            }

            http.end();
        }
        lastVersionUpdateCheck = millis();

        return 0;
    }

    int downloadAndInstallNewVersion()
    {
        /*
            We connect to the server endpoint which returns a .bin file.
            We start the update and return 1 if successfull.
        */
       
        WiFiClientSecure client;
        client.setInsecure(); // Insecure as DUCK - change to use a cert.

        std::string endpoint = "https://www.my-server/update?version=" + newestVersionFromServer;

        t_httpUpdate_return ret = httpUpdate.update(client, endpoint.c_str());

        switch (ret)
        {
        case HTTP_UPDATE_FAILED:
            Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
            return 0;

        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("HTTP_UPDATE_NO_UPDATES");
            return 0;

        case HTTP_UPDATE_OK:
            Serial.println("Update: OK");
            currentVersion = newestVersionFromServer;
            return 1;
        }

        return 0;
    }
}