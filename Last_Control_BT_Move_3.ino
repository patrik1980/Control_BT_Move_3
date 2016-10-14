#include <SoftwareSerial.h> // includo la libreria per la comunicazione seriale
#include <Servo.h>
Servo myServo;

int rxPin = 12;
int txPin = 11;

SoftwareSerial bluetooth(rxPin, txPin);
String message; //string that stores the incoming message

const int controlPin1 = 6;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStateSwitchPin = 5;
const int potPin = A0;

int onOffSwitchState = 0;
int previousonOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1; 

void setup() {

 pinMode(7, OUTPUT);
 
     pinMode(directionSwitchPin, INPUT);
     pinMode(onOffSwitchStateSwitchPin,INPUT);
     pinMode(controlPin1, OUTPUT);
     pinMode(controlPin2, OUTPUT);
     pinMode(enablePin, OUTPUT);
     digitalWrite(enablePin, LOW); 

   myServo.attach(7);  //Add Servo
   straight(); 
   
  Serial.begin(9600); // initialization
  bluetooth.begin(9600); //set baud rate
  Serial.println("On-Line..."); 
}

void loop()
{  
   while (bluetooth.available())
   message = char(bluetooth.read());
   {              
      char dato= bluetooth.read(); // "dato" è il valore che viene ricevuto dalla seriale
      //char dato= Serial.read(); // "dato" test per forzare valori da monitor seriale
      Serial.println( message ); //monitor per vedere dati inviati da app
       switch(dato)
       {
        case '3': 
         {
        // Left
        myServo.write(90);
        Serial.println( dato ); //monitor per vedere dati inviati da app
           break;
         }
        case '1': 
         {
        // Left
        myServo.write(160);
        Serial.println( dato ); //monitor per vedere dati inviati da app
           break;
         }
         case '2': 
         {
        // right 
        myServo.write(10);
        Serial.println( dato ); //monitor per vedere dati inviati da app
           break;           
         }
         case '4': 
         {
        // Stop 

  if (motorDirection == 1 ){
    digitalWrite (controlPin1, LOW);
    digitalWrite (controlPin2, LOW);
  }
   else {
    digitalWrite (controlPin1, LOW);
    digitalWrite (controlPin2, LOW);
  }
    Serial.println( dato ); //monitor per vedere dati inviati da app
           break;           
         }
         case '7': 
         {
        // Stop 
   onOffSwitchState =
   digitalRead(onOffSwitchStateSwitchPin);
   delay(1);
   directionSwitchState =
   digitalRead(directionSwitchPin);
   motorSpeed = analogRead(0);
   if ( onOffSwitchState != previousonOffSwitchState){
    if ( onOffSwitchState == HIGH) {
         motorEnabled = !motorEnabled;
      }
   }
  if (directionSwitchState != 
      previousDirectionSwitchState ){
        if (directionSwitchState == LOW){        
        motorDirection = !motorDirection;  
      }
  }
  if (motorDirection == 1 ){
    digitalWrite (controlPin1, LOW);
    digitalWrite (controlPin2, LOW);
  }
   else {
    digitalWrite (controlPin1, LOW);
    digitalWrite (controlPin2, LOW);
  }
  if (motorEnabled == 1) {
    analogWrite (enablePin, motorSpeed);
  }
  else {
    analogWrite (enablePin, 0);
  }
  previousDirectionSwitchState =
  directionSwitchState;
  previousonOffSwitchState = onOffSwitchState;
        Serial.println( dato ); //monitor per vedere dati inviati da app
           break;           
         }
         case '5': 
         {
        // forward 

  if (motorDirection == 1 ){
    digitalWrite (controlPin1, HIGH);
    digitalWrite (controlPin2, LOW);
  }
   else {
    digitalWrite (controlPin1, HIGH);
    digitalWrite (controlPin2, LOW);
  }
    Serial.println( dato ); //monitor per vedere dati inviati da app
           break;           
         } 
         case '8': 
         {
        // forward 
   onOffSwitchState =
   digitalRead(onOffSwitchStateSwitchPin);
   delay(1);
   directionSwitchState =
   digitalRead(directionSwitchPin);
   motorSpeed = analogRead(110)/4;
   if ( onOffSwitchState != previousonOffSwitchState){
    if ( onOffSwitchState == HIGH) {
         motorEnabled = !motorEnabled;
      }
   }
  if (directionSwitchState != 
      previousDirectionSwitchState ){
        if (directionSwitchState == HIGH){        
        motorDirection = !motorDirection;  
      }
  }
  if (motorDirection == 1 ){
    digitalWrite (controlPin1, LOW);
    digitalWrite (controlPin2, HIGH);
  }
   else {
    digitalWrite (controlPin1, HIGH);
    digitalWrite (controlPin2, LOW);
  }
  if (motorEnabled == 1) {
    analogWrite (enablePin, motorSpeed);
  }
  else {
    analogWrite (enablePin, 0);
  }
  previousDirectionSwitchState =
  directionSwitchState;
  previousonOffSwitchState = onOffSwitchState;
        Serial.println( dato ); //monitor per vedere dati inviati da app
           break;           
         }
         case '6':
         {
        // backward 
 
  if (motorDirection == 1 ){
    digitalWrite (controlPin1, LOW);
    digitalWrite (controlPin2, HIGH);
  }
   else {
    digitalWrite (controlPin1, LOW);
    digitalWrite (controlPin2, HIGH);
  }
    Serial.println( dato ); //monitor per vedere dati inviati da app
           break;           
         } 
         case '9': 
         {
        // backward 
         onOffSwitchState =
   digitalRead(onOffSwitchStateSwitchPin);
   delay(1);
   directionSwitchState =
   digitalRead(directionSwitchPin);
   motorSpeed = analogRead(110)/4;
   if ( onOffSwitchState != previousonOffSwitchState){
    if ( onOffSwitchState == HIGH) {
         motorEnabled = !motorEnabled;
      }
   }
  if (directionSwitchState != 
      previousDirectionSwitchState ){
        if (directionSwitchState == HIGH){        
        motorDirection = !motorDirection;  
      }
  }
  if (motorDirection == 1 ){
    digitalWrite (controlPin2, HIGH);
    digitalWrite (controlPin1, LOW);
  }
   else {
    digitalWrite (controlPin2, LOW);
    digitalWrite (controlPin1, HIGH);
  }
  if (motorEnabled == 1) {
    analogWrite (enablePin, motorSpeed);
  }
  else {
    analogWrite (enablePin, 0);
  }
  previousDirectionSwitchState =
  directionSwitchState;
  previousonOffSwitchState = onOffSwitchState;
        Serial.println( dato ); //monitor per vedere dati inviati da app
           break;           
         }              
       }       
   }


}

/**
 * Move the steering in middle position
 */
  void straight()
  {
  if(myServo.read()==180)
  {
    // from right to middle
    myServo.write(50); 
  }
  else if(myServo.read()==0)
  {
    // from left to middle
    myServo.write(110);
  }   
}

