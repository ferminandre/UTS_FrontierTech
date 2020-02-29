#include<Arduino.h>

const int buttonPin = 2;  

int buttonState = 0;     
int lastButtonState = 0; 
int startPressed = 0;    
int endPressed = 0;      
int holdTime = 0;        
bool status = false;

void setup() {
  pinMode(buttonPin, INPUT); // initialize the button pin as a input
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);        // initialize serial communication
}

void updateState() {
  if (buttonState == HIGH) {
      endPressed = millis();
      holdTime = endPressed - startPressed;
      Serial.println("You released the button");
      Serial.print("Time: ");
      Serial.print(holdTime/1000);
      Serial.println(" seconds");
      digitalWrite(LED_BUILTIN, HIGH);
      status = false;

  } else {
      startPressed = millis();
      Serial.println("You pressed the button");
      status = true;
  }
}
void loop() {
  buttonState = digitalRead(buttonPin); // read the button input

  if (buttonState != lastButtonState) { // button state changed
     updateState();
     
     lastButtonState = buttonState;
  }else if(millis()-startPressed>=10000 && status){
    Serial.println("sudah 10 detik");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    status=false;
  }else if (buttonState == LOW && status){
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
}