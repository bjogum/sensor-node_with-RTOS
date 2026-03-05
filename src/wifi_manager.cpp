#include <WiFiS3.h>

bool connectedToWiFi = false;

// kolla om vi är anslutan till wifi
// retunerar true om connected.
bool wifiIsConnected(){
    return (WiFi.status() == WL_CONNECTED);
}

// init, bara vid uppstart!
void initWiFi(){
    WiFi.begin(WIFI_SSID, WIFI_PASS);    
}

// hanterar wifi
void manageWiFi(){
    if (!wifiIsConnected()){
        if (connectedToWiFi){
            connectedToWiFi = false;
        printf("\n..WiFi disconneced..");
        printf("\n\n");
        }

    } else {
        if (!connectedToWiFi){
            connectedToWiFi = true;
            printf("\nConneced to WiFi: ");
            printf(WIFI_SSID);
            printf("\n\n");
        }
    }
}