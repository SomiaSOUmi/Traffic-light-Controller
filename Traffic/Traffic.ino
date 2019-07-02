#include <Adafruit_Circuit_Playground.h> 

int MJR = 0 ; 
int MNR = 0 ; 
int TL = 0 ; 
unsigned long t = 0 ; 
int s = 0 ; 
int cars[100] ;
unsigned long j = 0 ; 
unsigned long ti = 0 ; 
int w = 0 ; 
void setup() {
    CircuitPlayground.begin();  
}

void loop() {
  // initial state: “By default”, the traffic lights (TL) are green for the major road (MJR) and red for the minor road (MNR).
  for (int p=0; p<5; p++) {
   CircuitPlayground.setPixelColor(p, 0, 255, 0);
  }
  for (int p=5; p<10; p++) {
   CircuitPlayground.setPixelColor(p, 255, 0, 0);
  }
  MJR = 2 ; // green 
  MNR = 0 ; // red 
  if (TL == 0 ) { // we use the variable TL to know if we just move to the initial state or not 
      Serial.println("This state is 20 seconds long");
  t = millis() + 20*1000  ; // if TL has just changed into this state, then MJR will stay GREEN for at least 20 seconds irrespective,
  while (millis()< t){ // while waiting for the 20 second to pass we always make sure if there pedestrian crossing is pressed 
     if (CircuitPlayground.leftButton() or CircuitPlayground.rightButton()) {s = 1 ;} // if the pedestrian crossing is pressed we save the variable s to indicate that all the lights should turn red      
    
     if ( CircuitPlayground.slideSwitch() and w == 0 and j > 0) 
  {
    Serial.println ("The cars captured by the MJR's camera are: ");
    for (int p=0; p<j; p++)
    {
    Serial.println (" |--------------------|") ; 
    Serial.print (" | Car picture number |") ;  
    Serial.println (cars[p]) ;  
    
    }
    w = 1 ; // to indicate that there is no car has beed captured and to make sure that the table isnt displayed until a new car is captured 
  }
    }
    Serial.println (" 20 seconds has ended") ; 
  TL = 1 ; 
  }

  if (CircuitPlayground.leftButton() or CircuitPlayground.rightButton()) {s = 1 ;} // we always check if the pedestrian crossing is pressed or not 
 
  if (s == 1 ) // if pedestrian crossing then the two roads should change to red before moving to the initial state 
   {
    Serial.println (" The pedestrian crossing is pressed so the two roads change to red "); 
      for (int p=0; p<5; p++) {
       CircuitPlayground.setPixelColor(p, 255, 0, 0);
      }
      for (int p=5; p<10; p++) {
       CircuitPlayground.setPixelColor(p, 255, 0,0);
      }
      
      MJR = 0 ; 
      MNR = 0 ; 
      t = millis() + 15*1000  ; 
      Serial.println (" This state is 15 seconds long ") ; 
      while (millis()< t){
              if (MJR == 0 and CircuitPlayground.readCap(1)> 50  )
             {
              ti = millis() + 1000 ; 
              while (millis() < ti) {}
              if (CircuitPlayground.readCap(3))
              {
                cars[j] = j ; 
                j = j+1; 
                w = 0 ; 
                Serial.println ("A car has been saved by the camera") ;
              }
              }       

              if ( CircuitPlayground.slideSwitch() and w == 0 and j > 0) 
            {
              Serial.println ("The cars captured by the MJR's camera are: ");
              for (int p=0; p<j; p++)
              {
              Serial.println (" |--------------------|") ; 
              Serial.print (" | Car picture number |") ;  
              Serial.println (cars[p]) ;  
              
              }
              w = 1 ; // to indicate that there is no car has beed captured and to make sure that the table isnt displayed until a new car is captured 
            }
            
        } 
      Serial.println ("The 15 seconds has ended");
      TL = 0 ; // if we back to the initial state we need to wait a 20 seconds before changing to any other state 
      s = 0 ; 

   }
   
  if (CircuitPlayground.readCap(12) > 50 or CircuitPlayground.readCap(10) > 50) //A suitably positioned sensors on MNR are triggered when a vehicle approach the junction on either side
    {
      Serial.println ("The MNR sensor is triggered because a vehicle approach the junction on either side") ; 
      t = millis() + 5*1000  ; // a 5 seconds wait is counted before TL change starts
       Serial.println ("a 5 seconds wait is started");
      while (millis()< t){
       if (CircuitPlayground.leftButton() or CircuitPlayground.rightButton()) {s = 1 ;}
       if (MJR == 0 and CircuitPlayground.readCap(1)> 50  )
             {
              ti = millis() + 1000 ; 
              while (millis() < ti) {}
              if (CircuitPlayground.readCap(3))
              {
                cars[j] = j ; 
                j = j+1; 
                w = 0 ; 
                Serial.println ("A car has been saved by the camera") ;
              }
              }       

              if ( CircuitPlayground.slideSwitch() and w == 0 and j > 0) 
            {
              Serial.println ("The cars captured by the MJR's camera are: ");
              for (int p=0; p<j; p++)
              {
              Serial.println (" |--------------------|") ; 
              Serial.print (" | Car picture number |") ;  
              Serial.println (cars[p]) ;  
              
              }
              w = 1 ; // to indicate that there is no car has beed captured and to make sure that the table isnt displayed until a new car is captured 
            }
        
        } 
     Serial.println ("The 5 seconds has ended");
      for (int p=0; p<5; p++) {
       CircuitPlayground.setPixelColor(p, 255, 0, 0);
      }
      for (int p=5; p<10; p++) {
       CircuitPlayground.setPixelColor(p, 0, 255, 0);
      }

      MJR = 0 ; // red
      MNR = 2 ; // green 
      
  
          t = millis() + 20*1000  ; // we keep the current state (MJR red and MNR green) for 20 seconds before changing to the initial state 
          Serial.println ("The current state is 20 seconds long") ;
            while (millis()< t){
                   if (CircuitPlayground.leftButton() or CircuitPlayground.rightButton()) {s = 1 ;}
                            if (MJR == 0 and CircuitPlayground.readCap(1)> 50  ) // we always check if there is a car that crosses the red MJR 
                   {
                    ti = millis() + 1000 ; 
                    while (millis() < ti) {}
                    if (CircuitPlayground.readCap(3))
                    {
                      cars[j] = j ; 
                      j = j+1; 
                      w = 0 ; 
                      Serial.println ("A car has been saved ") ;
                    }
                    }  
                    
              } 
          Serial.println ("The 20 seconds has ended");
      TL = 0 ; 

    if ( CircuitPlayground.slideSwitch() and w == 0 and j > 0) 
      {
        Serial.println ("The cars captured by the MJR's camera are: ");
        for (int p=0; p<j; p++)
        {
        Serial.println (" |--------------------|") ; 
        Serial.print (" | Car picture number |") ;  
        Serial.println (cars[p]) ;  
        
        }
        w = 1 ; // to indicate that there is no car has beed captured and to make sure that the table isnt displayed until a new car is captured 
      }
        }


     if (MJR == 0 and CircuitPlayground.readCap(1)> 50  ) // while MJR is red if the touch sensor number 1 is pressed
     {
      t = millis() + 1000 ; 
      while (millis() < t) {}
      // after 1 second we check if the touch sensor is pressed. If so, we save the care number because the camera is positioned on MJR to detect if cars cross on the MJR red light
      if (CircuitPlayground.readCap(3))
      {
        cars[j] = j ; 
        j = j+1; 
        w = 0 ; 
        Serial.println ("A car has been saved ") ;
      }
      }

     if ( CircuitPlayground.slideSwitch() and w == 0 and j> 0) 
      {
            Serial.println ("The cars captured by the MJR's camera are: ");
        for (int p=0; p<j; p++)
        {
        Serial.println (" |--------------------|") ; 
        Serial.print (" | Car picture number |") ;  
        Serial.println (cars[p]) ;  
        
        }
        w = 1 ; // to indicate that there is no car has beed captured and to make sure that the table isnt displayed until a new car is captured 
      }
  
}
