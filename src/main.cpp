#include <Arduino.h>

/*
-Se puede anadir un timer para una secuencia de inicio, por ejemplo
encender las luces solo la primera vez y flashearlas por 3 segundos
*/

///Define Buttons
//Reset Button
//int resetButtonPin = 13; //D7

//Button1
int button1Pin = 3; //D5
int led1Pin = 9; //D0
int button1State = 0; 

//Button2
int button2Pin = 6; //D2
int led2Pin = 12; //D1
int button2State = 0; 

//Buzzer
int buzzerpin = 13;

//int resetButtonState = 0;
boolean pollingForPresses = 1;

int lastbutton1State = LOW;
int lastbutton2State = LOW;

int lastResetState = LOW;

void resetButtons() {
  
  lastbutton1State = 0;
  lastbutton2State = 0;
 
  //resetButtonState = 0;
  lastResetState = 0;
  
  button1State = 0;
  button2State = 0;

  
  Serial.print("All the Buttons were reset! \n");
  
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);

  //digitalWrite(resetButtonPin, LOW);
  
  pollingForPresses = 1;
}

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  pinMode(buzzerpin,OUTPUT);

  // initialize the pushbutton pin as an input:
  //pinMode(resetButtonPin, INPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  //Inicializando leds
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);

  //
  tone(buzzerpin, 440, 500); //Haciendolo sonar en la primera oportunidad que se encienda
}

void timer(){

  int t = 0;

  while(t<3){
      delay(1000); //Contador de 1 segundo por puerto serial
      t = t + 1;
      Serial.print("Cuenta: ");
      Serial.println(t);
  }

  //Reinicio botones

  lastbutton1State = 0;
  lastbutton2State = 0;

  button1State = 0;
  button2State = 0;

  Serial.print("All the Buttons were reset! \n");
  
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);
  
  pollingForPresses = 1;
  //Timer de 20 segundos cuando se encienda boton
}

void buzzer(){
  //Routine to make a buzzer sound 
  tone(buzzerpin,500); //Suena a 440Hz por 3 segundos continuos
  delay(2000); //1.5 segundos
  noTone(buzzerpin);
}

void loop() {

  int reading1 = digitalRead(button1Pin);
  int reading2 = digitalRead(button2Pin);
 
  //int readingReset = digitalRead(resetButtonPin);

    if(pollingForPresses == 1){
      //Button 1
      if (reading1 != button1State && reading1 != lastbutton1State) {
        button1State = reading1;
        button1State = digitalRead(button1Pin);
          
              if (button1State == HIGH) {
                // turn LED on:
                  Serial.print("Button 1 ON \n");
                  digitalWrite(led1Pin, LOW); //Active Low
                  buzzer();
                  pollingForPresses = 0;
              }
         button1State = 0;
      }
   
      //Button 2
      if (reading2 != button2State && reading2 != lastbutton2State) {
        button2State = reading2;
        button2State = digitalRead(button2Pin);
          
              if (button2State == HIGH) {
                // turn LED on:
                Serial.print("Button 2 ON \n"); //Active Low
                digitalWrite(led2Pin, LOW);
                buzzer();
                pollingForPresses = 0;
              }
         button2State = 0;
      }
      
    }
   //Check reset button
   
    if (pollingForPresses==0) {

      timer();

      /*
      if (readingReset != resetButtonState && readingReset != lastResetState) {
              resetButtonState = digitalRead(resetButtonPin);
          
              if (resetButtonState == HIGH) {
                Serial.print("Reset button HIGH \n");
                resetButtons();
              }
         
         resetButtonState = 0;
      }
      */
    }

  //lastResetState = readingReset;
  lastbutton1State = reading1;  
  lastbutton2State = reading2;
}
