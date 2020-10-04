
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <RBDdimmer.h>//

#define outputPin  11
#define zerocross  2// for boards with CHANGEBLE input pins
#define LAMPMAXVALUE 100

dimmerLamp dimmer(outputPin); //initialase port for dimmer for MEGA, Leonardo, UNO, Arduino M0, Arduino Zero
tmElements_t tm;

void setup() {
  Serial.begin(9600);
  delay(4000);
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE)
  pinMode(LED_BUILTIN, OUTPUT);
  dimmer.setState(ON);
}

void loop() {

  RTC.read(tm);
  dimmer.setState(ON);
  /* Serial.print(tm.Hour);  //Print commands commented out unless connected to serial to debug
    Serial.print("-");
    Serial.print(tm.Minute);
    Serial.print("-");
    Serial.println(tm.Second);
    delay(1000);
  */
  /*
    Sept thru April = on at 7am off at 9am on at 4pm dim at 10pm off at 11pm
    May thru August = on at 4pm dim at 10pm off at 11pm
  */

 // September thru April   
  if (tm.Month >= 9 || tm.Month < 5) {
    if (tm.Hour == 7 || tm.Hour == 8)
    {
      
      dimmer.setPower(75);
    }

    if (tm.Hour > 8 && tm.Hour < 16)
    {
      dimmer.setState(OFF);
    }
    if (tm.Hour >= 16 && tm.Hour <19)
    {
  
      dimmer.setPower(94);
    }
  }

// May thru August
  if (tm.Hour >= 19 && tm.Hour <= 21)
  {
  
    dimmer.setPower(94);
  }

  if (tm.Hour == 22)
  {
    dimmer.setPower(47);
  }

  if (tm.Hour == 23 || tm.Hour <= 6)
  {
    dimmer.setState(OFF);
  }
}
