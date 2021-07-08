#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 3
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE); 

uint32_t delayMS;

#include <LiquidCrystal.h>
int relay_pin=13;
int buzzer=2;
float st=37.5;
float D=38.5;
float C=36.5;
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 =7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() { 
	pinMode(relay_pin,OUTPUT);
	pinMode(buzzer,OUTPUT);
	Serial.begin(9600);
	dht.begin();
	sensor_t sensor;
	dht.temperature().getSensor(&sensor);
	lcd.begin(16,2);
	lcd.print("    npoudelp");
	lcd.setCursor(0,2);
	lcd.print("      IKF");
	delay(2000);
	lcd.clear();
	lcd.print("Incubator v0.0.1");
	digitalWrite(relay_pin,HIGH);
	digitalWrite(buzzer,HIGH);
	delay(300);
	digitalWrite(relay_pin,LOW);
	digitalWrite(buzzer,LOW);
	lcd.clear();
	lcd.setCursor(0,0);
	delay(700);

}

void loop(){
	lcd.begin(16,2);
	sensors_event_t event;
	dht.temperature().getEvent(&event);
	float A=event.temperature; 
	if(A>=st){
		digitalWrite(relay_pin,HIGH);
	} 
	else{
		digitalWrite(relay_pin,LOW);
	}  
	if(A >= D or A <= C){
		digitalWrite(buzzer,HIGH);
	}  
	else{
		digitalWrite(buzzer,LOW);
	} 
	lcd.print("Temp: "); 
	lcd.print(A);


	dht.humidity().getEvent(&event);
	float B=event.relative_humidity;
	lcd.setCursor(0,2);
	lcd.print("Humi: ");    
	lcd.print(B);

	delay(2000);
	lcd.clear(); 


}
