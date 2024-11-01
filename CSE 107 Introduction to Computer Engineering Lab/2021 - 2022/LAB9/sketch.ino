int palindrome(char* str, int head_index, int tail_index)
{
  if (head_index > tail_index) return 1;
  else
  {
    if (str[head_index] == str[tail_index])
      return palindrome(str, head_index + 1, tail_index - 1);
    else
      return 0;
  }
}

void setup() {
 Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
 char* str ="eyedipadanadapideye";
 int length_of_str = 19, result;
 Serial.print(str);
 result = palindrome(str, 0, length_of_str - 1);
 if (result == 1)
  Serial.println(" is a palindrome.");
  else
  Serial.println(" isn't a palindrome.");
}

void loop() {

}