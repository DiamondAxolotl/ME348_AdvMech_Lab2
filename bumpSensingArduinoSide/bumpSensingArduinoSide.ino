int leftMotor;
int rightMotor;

const byte numChars = 32;
char receivedChars[numChars];
char tempChar[numChars]; // temporary array used for parsing

boolean newData = false;

int x=0;
int y=0;
int z=0;


//=====================================================

void setup() {
  Serial.begin(115200);
  pinMode(49, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);

  pinMode(3, OUTPUT); //left motor
  pinMode(2,OUTPUT); //left motor

Serial.println("<arduino is ready>");

}

//=====================================================

void loop() {
  recvWithStartEndMarkers();

  if (newData == true){
    
    strcpy(tempChar, receivedChars);
    parseData();
    SendBumpData();
    
    
  }
CommandMotors();

}

//============================================

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
                                                     
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();
                                                             
                                                                  
        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminates the string, frankly unsure why I need this
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============================================

void parseData(){

  //an interesting bug I found is that a char that was created in the Rpi and sent over to the arduino has a much higer chance
  //of being squashed by other char's that are sent along with is, this was solved in the sendString() function written on
  //the python side



  char *strtokIndexer; //doing char * allows strtok to increment across my string properly frankly im not sure why... my kingdom for a proper c++ class

  
  strtokIndexer = strtok(tempChar,","); //sets strtokIndexer = to everything up to the first comma in tempChar /0 //this line is broken
  leftMotor = atoi(strtokIndexer); //converts strtokIndexer into a int
  

  strtokIndexer= strtok(NULL, ","); //setting the first input to null causes strtok to continue looking for commas in tempChar starting from where it left off, im not really sure why 
  rightMotor = atoi(strtokIndexer);

  


  //now that we have extracted the data from the Rpi as floats, we can use them to command actuators somewhere else in the code
}

//============================================
void SendBumpData(){
  
  x=digitalRead(49);
  y=digitalRead(51);
  z=digitalRead(53);
  

  //Serial.print(receivedChars);
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.println(z);
  newData = false; 
}

//============================================

void CommandMotors(){  
  //analogWrite(3,leftMotor); 
  //analogWrite(2,rightMotor);
}
