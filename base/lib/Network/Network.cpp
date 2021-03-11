#include "Network.h"

namespace network
{
    int connectToWiFi()
    {
        WiFi.begin(ssid, password);
        log_d("Connecting");
        if (WiFi.status() != WL_CONNECTED)
        {
            return 0;
        }
        return 1;
    }

    int getNetworkingStatus()
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            return 0;
        }
        log_i("Connected to WiFi network");
        return 1;
    }
}