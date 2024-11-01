#include <LiquidCrystal.h>

//-------Temperature----------//

int lm35Pin = A0;
float temp_voltage = 0;
float temp = 0;
int temp_data = 0;

//------Light----------------//

#define MAX_ADC_READING           1023
#define ADC_REF_VOLTAGE           5.0
#define REF_RESISTANCE            150
#define LUX_CALC_SCALAR           12518931
#define LUX_CALC_EXPONENT         -1.405

int ldr_pin = A1 ;
int   ldrRawData;
float resistorVoltage, ldrVoltage;
float ldrResistance;
float ldrLux;

//------Humidity---------------//

int sensor_pin = A2; 
int output_value;

//--------Gas-----------------//

int gas_pin = A3;
int gas, co2lvl;

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

void temperature_sensor(){
  temp_data = analogRead(lm35Pin);
  temp_voltage = (temp_data / 1023.0)*5000;
  temp = temp_voltage /10.0; 
  
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.setCursor(6, 1);
  lcd.print("C");
  delay(300);
}

void ldr_sensor(){
  ldrRawData = analogRead(ldr_pin);
  resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;
  ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
  ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
  ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);
  
  lcd.setCursor(0, 0);
  lcd.print("Light Density");
  lcd.setCursor(0,1);
  lcd.print(ldrLux);
  lcd.setCursor(6, 1);
  lcd.print("LUX");
  delay(300);
}

void humidity_sensor(){
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,0,0,100);
  
  lcd.setCursor(0, 0);
  lcd.print("Humidity");
  lcd.setCursor(0,1);
  lcd.print(output_value);
  lcd.setCursor(3,1);
  lcd.print("%");
  delay(300);
}

void gas_sensor(){
  gas = analogRead(gas_pin);
  co2lvl = gas-120;
  co2lvl = map(co2lvl,0,1024,400,5000);
  
  lcd.setCursor(0, 0);
  lcd.print("CO2");
  lcd.setCursor(0,1);
  lcd.print(co2lvl);
  lcd.setCursor(3,1);
  lcd.print(" PPM");
  delay(300);
}

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  
  lcd.clear();
  temperature_sensor();
  delay(3000);
  lcd.clear();
  humidity_sensor();
  delay(3000);
  lcd.clear();
  gas_sensor();
  delay(3000);
  lcd.clear();
  ldr_sensor();
  delay(3000);
  lcd.clear();
  
}
