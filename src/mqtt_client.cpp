#include "alarm.h"

// -- avgör om datan behöver publiseras - Beroende på sensorer/status samt state --
// a) skicka all data vid "init" (även RSSI)
// b) skicka förändrad data || var 30e sek
// c) skicka heartbeat var 30e sek (bra trots LWT)
// d) LWT: Maxtid, 10s offline -> ESP ger larm 


    // Om: SKICKA datan (pub)


// TA EMOT data (sub) från ESP -> "state"
