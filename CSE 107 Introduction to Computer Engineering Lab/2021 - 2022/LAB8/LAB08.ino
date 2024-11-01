char* str = "Today is the 10th day of the December";
int cursor = 0, ascii;
char current;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  current = str[cursor];
  if (current<= 57 && current >= 48)
  {
    Serial.print(current);
    Serial.println(" is a number.");
  } else if (current<= 122 && current >= 97)
  {
    Serial.print(current);
    Serial.println(" is a lowercase.");
  } else if (current<= 90 && current >= 65)
  {
    Serial.print(current);
    Serial.println(" is a capital.");
  } 
  
  if (current == '\0')
  {
    Serial.println("----------------");
    cursor = 0;
    delay(5000);
  }else
  {
    cursor +=1;
    delay(150);
  }
}
