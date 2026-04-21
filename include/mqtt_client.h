#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

void initCredentials();
int manageMQTT();
void initSendMQTT();
void sendMQTT(AlarmInfo *info);
void receiveMQTT();

#endif