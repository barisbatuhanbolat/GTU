#define button 12
const int led = 8;
int i;                          //I declare led, button pins and some variables for program. 
//char transmittedData1[]={0};    
int transmittedData;
int n;
int n2;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(20000);
  pinMode(led, OUTPUT);               //I start Serial and I initialize button and led pins as a OUTPUT and INPUT.
  pinMode(button,INPUT);
  
}

void loop() {
  while (Serial.available()) {
    transmittedData=Serial.read()-48;               //I created a loop for serial comminication.
    //transmittedData1[0]=transmittedData;          //And  I used transmittedData variable to read a command from serial port.
    if(transmittedData==1){                         //I subtract 48 from serial data because serial keep things as CHAR. I turned these chars to ints and subtarct 48 from them to find commands. (Example Char 1 = Int 49)
      digitalWrite(led, HIGH);
    }
    if(transmittedData==2){                            // "1" is to light up led
      digitalWrite(led, LOW);                          // "2" is to light down led. 
    }                                                 
    if(transmittedData==3){
        i=0;                                                      
        while(i < 3) {
          i++;                                      //"3" is to blink led three times.
          digitalWrite(led, HIGH);
          delay(300);
          digitalWrite(led, LOW);
          delay(300);
        }    
    }
    if(transmittedData==4){
        n = Serial.parseInt();                //Fourth condition for receiving number from arduino and square it. 
        n2=n*n;                              //Sending squared number in serial port.
        Serial.println("\n");                 
        Serial.print(n2);
    }
    if(transmittedData==5){
        int j=0;
        while(true) {
          if(digitalRead(button) == 1) {              //If the button is pressed, sends "j" to the serial port and it increases the "j" value by one .
            Serial.println(j);
            j++;          
          }
          delay(300);
        }
     }
   }
}
