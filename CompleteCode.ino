#include<SoftwareSerial.h >
#include<LiquidCrystal.h>
#include<TinyGPS++.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial mySerial(2,3);
SoftwareSerial serial_connection(10, 11); 
TinyGPSPlus gps;
float mq3 = A0;
int sensorThres = 200;
#define buzzer 9
long vibra = 13;
long TP_init();
int sms_count;
char msg;

void setup()
{
  mySerial.begin(9600);
  serial_connection.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(vibra , INPUT);
  pinMode(mq3 = A0, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  delay(500);
}

void loop()
{
   while(serial_connection.available())
  {
    gps.encode(serial_connection.read());
  }
  if(gps.location.isUpdated())
  {
   
    Serial.println("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 6);
    Serial.println("Speed MPH:");
    Serial.println(gps.speed.mph());
    Serial.println("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");
  }
  float analogSensor = analogRead(mq3 = A0);
  float sensor_volt;
  sensor_volt = analogSensor / 1024 * 5.0;
  Serial.print(" MQ3 Sensor: ");
  Serial.println(analogSensor);
  Serial.print("Sensor_volt = ");
  Serial.print(sensor_volt);
  Serial.println("V");
  long measurement = TP_init();
  Serial.print("measurement =");
  Serial.println(measurement);

  if (analogSensor > sensorThres)
  {
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Alcohol Detected");
    delay(500);
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("Take An Action");
    delay(500);
    delay(500);
    lcd.clear();
    delay(20);
    lcd.setCursor(0, 0);
    lcd.print("ADC Value=");
    delay(500);
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(analogSensor);
    delay(500);
    delay(500);
    lcd.clear();
    delay(20);
    lcd.setCursor(0, 0);
    lcd.print("Voltage Value=");
    delay(500);
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(sensor_volt);
    lcd.setCursor(5, 1);
    lcd.print("V");
    delay(500);
    delay(500);
    lcd.clear();
    {
      sent_SMS1();
    }
  }



  if (measurement > 200)
  {
    lcd.setCursor(3, 0);
    lcd.print("Vibration");
    delay(500);
    delay(500);
    lcd.setCursor(3, 1);
    lcd.print("Detected!!!");
    delay(500);
    delay(500);
    lcd.clear();
    delay(20);
    lcd.print("Value=");
    delay(500);
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(measurement);
    delay(500);
    delay(500);
    lcd.clear();

    {
      sent_SMS2();
    }
  }



  else
  {
    digitalWrite(buzzer, LOW);
    lcd.setCursor(5, 0);
    lcd.print("Hello!! ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(" ---Mr. Kishon---");
    lcd.setCursor(0, 0);
    delay(500);
    delay(500);
    lcd.clear();
    lcd.print("No Problem ");
    delay(500);
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("Have A Nice Day");
    delay(500);
    lcd.clear();


  }
}
long TP_init() {

  long measurement = pulseIn (vibra, HIGH);
  return measurement;
}

void sent_SMS1()
{
  lcd.setCursor(0, 0);
  lcd.print("Alcohol Detected!!!");
  delay(100);
  lcd.setCursor(2, 1);
  lcd.print("Sending SMS");
  delay(1000);
  delay(1000);
  delay(1000);
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"phone number\"\r");
  delay(1000);
  mySerial.println("Alcohol Detected");
  delay(100);
  mySerial.println("Latitude");
  mySerial.println (gps.location.lat(), 6);
  delay(100);
  mySerial.println("Longitude");
  mySerial.println( gps.location.lng(), 6);
  delay(100);
  mySerial.println((char)26);
  delay(1000);
  Serial.println(" SMS Sent!");
  lcd.setCursor(0, 1);
  lcd.print("===SMS Sent!!===");
  delay(2000);
  delay(2000);
  lcd.clear();
}



void sent_SMS2()
{
  lcd.setCursor(0, 0);
  lcd.print("Accident Alert!!");
  delay(100);
  lcd.setCursor(2, 1);
  lcd.print("Sending SMS");
  delay(1000);
  delay(1000);
  delay(1000);
  mySerial.println("AT+CMGF=1");
  delay(1000);  //
  mySerial.println("AT+CMGS=\"phone number\"\r");
  delay(1000);
  mySerial.println("Vibration Detected");
  delay(100);
  mySerial.println("Latitude");
  mySerial.println (gps.location.lat(), 6);
  delay(100);
  mySerial.println("Longitude");
  mySerial.println( gps.location.lng(), 6);
  delay(100);
  mySerial.println((char)26);
  delay(1000);
  Serial.println(" SMS Sent!");
  lcd.setCursor(0, 1);
  lcd.print("===SMS Sent!!===");
  delay(2000);
  delay(2000);
  lcd.clear();

}
