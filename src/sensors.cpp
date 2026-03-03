// -- hanterar den "icke-blockerande" logiken -- 


void readPrio3SensorsAsync(){
    static int currentSensor = 0; // static -> sätts endast EN gång (init)
    
    // för att minimiera jitter för "låg-prio" sensorer - läs asynkront, en sensor åt gången.
    switch (currentSensor)
    {
    case 0: 
        //läs temp
        break;
    case 1:
        //läs humidity
        break;
    case 2:
        //läs water leak
        break;
    }

    currentSensor++;
    if (currentSensor >= 3){
        currentSensor = 0;
    }

};