boolean wasPressed[9];
int currentState[9];

char cmd[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

void setup() {
  //setup pins
  for (int i = 2; i <= 10; i++) {
    pinMode(i, INPUT_PULLUP);
    digitalRead(i);
    wasPressed[i - 2] = false;
    currentState[i - 2] = false;
  }
  if (digitalRead(9)==LOW) wasPressed[7]=true;
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  //setup communication
  Serial.begin(115200);
}

void loop() {
  for (int i = 2; i <= 8; i++) {
    currentState[i-2] = digitalRead(i);//read button state
    if (!wasPressed[i - 2] && currentState[i - 2] == LOW) { //if the state of the pin changed
      Serial.write(cmd[i - 2]); //send the data
      wasPressed[i - 2] = true; //update the last button state
    }
    if (currentState[i-2] == HIGH) wasPressed[i-2] = false;
  }
  currentState[7] = digitalRead(9);
  if (!wasPressed[7] && currentState[7] == HIGH) { //if the state of the pin changed
    Serial.write(cmd[8]); //send the data
    wasPressed[7] = true;//update the last button state
  }
  if (wasPressed[7] && currentState[7] == LOW) { //if the state of the pin changed
    Serial.write(cmd[7]); //send the data
    wasPressed[7] = false;//update the last button state
  }
  currentState[8]= digitalRead(10);
  if (!wasPressed[8] && currentState[8] == LOW) { //if the state of the pin changed
    Serial.write(cmd[9]); //send the data
    wasPressed[8] = true;//update the last button state
  }
  serialEvent();
  delay(100);
}
void serialEvent() { //if any data was sent
  if (Serial.available() > 0) { //and there's at least 1 byte to look at
    int data = Serial.read();//read the data
    //do something with it if you want
    if (data == 49) {
      digitalWrite(12, HIGH);
    }
    if (data == 48) {
      digitalWrite(12, LOW);
    }
  }
}

