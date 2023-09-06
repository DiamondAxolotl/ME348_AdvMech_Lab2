 const byte numChars = 32;
char receivedChars[numChars];
char tempChar[numChars]; // temporary array used for parsing

boolean newData = false;
  
  void setup() {
    Serial.begin(115200);
 
}   

void loop() {
  Serial.println("<hello from arduino>");

}
