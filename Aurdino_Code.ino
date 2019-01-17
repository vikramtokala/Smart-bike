#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#include <DHT.h>;
#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>   



#define I2C_ADDR 0x3F
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7
#define DHTPIN 2
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);
const int PulseWire = 0;       
const int LED13 = 13;          
int Threshold = 550;           
                               
                                
                               
PulseSensorPlayground pulseSensor;  


int trigPin1=10;
int echoPin1=3;

int trigPin2=4;
int echoPin2=5;

int trigPin3=6;
int echoPin3=7;



int chk;
float hum;  
float temp; 


void setup() {
  
  Serial.begin(115200);
   pulseSensor.analogInput(PulseWire);   
   pulseSensor.blinkOnPulse(LED13);       
   pulseSensor.setThreshold(Threshold);   

  
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");
   }
  dht.begin();
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
    
  lcd.setCursor(0,1);
   lcd.setBacklight(WHITE);
  
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  
}


uint8_t i=0;
uint8_t new_buttons=BUTTON_LEFT;


void loop() {
   
   
  uint8_t buttons = lcd.readButtons();
  if(buttons)
     new_buttons=buttons;
  
  
  hum= dht.readHumidity();
  temp= dht.readTemperature();

    long duration1, distance1;
  digitalWrite(trigPin1, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;
  
     
  long duration2, distance2;
  digitalWrite(trigPin2, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= (duration2/2) / 29.1;
    
  long duration3, distance3;
  digitalWrite(trigPin3, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3= (duration3/2) / 29.1;



  if (new_buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (new_buttons & BUTTON_UP) {
      lcd.print("Humidity:");
      lcd.print(hum);
      lcd.setCursor(0,1);
      lcd.print("Temperture:");
      lcd.print(temp); 
      lcd.setBacklight(RED);
    }
       if (new_buttons & BUTTON_DOWN) {
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("S1");
       lcd.print(distance1);
       lcd.setCursor(7,0);
       lcd.print("S2");
       lcd.print(distance2);
       lcd.setCursor(0,1);
       lcd.print("S3");
       lcd.print(distance3);
      
      } 
      int myBPM = pulseSensor.getBeatsPerMinute();  
                                           

if (pulseSensor.sawStartOfBeat()) {            
 Serial.println("♥  A HeartBeat Happened ! "); 
 Serial.print("BPM: ");                         
 Serial.println(myBPM);                         
}


      
        if (new_buttons & BUTTON_LEFT){
            lcd.setCursor(0,0);
            lcd.print("BPM:");
            lcd.print(myBPM);

        }
      
  Serial.print ( "Sensor1  ");
    Serial.print ( distance1);
    Serial.println("cm");
    Serial.print("Sensor2  ");
    Serial.print(distance2);
    Serial.println("cm");
    Serial.print("Sensor3  ");
    Serial.print(distance3);
    Serial.println("cm");
      
      
      }
}
  
  
