void setup() {
  Serial.begin(9600);
  dec2bin(5);
  Serial.print("\n");
  dec2bin(6);
  Serial.print("\n");
  dec2bin(100);
  Serial.print("\n");
  dec2bin(1000001);
  Serial.print("\n");
}

void loop() {

}

void dec2bin(int decimal_number)
{
  if (decimal_number != 0 && decimal_number != 1) dec2bin(decimal_number / 2);
  Serial.print(decimal_number % 2);
}
