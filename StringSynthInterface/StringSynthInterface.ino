boolean wasPressed[9];
int currentState[9];
int currentValue;

char cmd[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

void setup() {
  //setup pins
  for (int i = 2; i <= 10; i++) {
    pinMode(i, INPUT_PULLUP);
    wasPressed[i - 2] = false;
    currentState[i - 2] = false;
    currentValue = analogRead(A0);
  }
  pinMode(12, OUTPUT);
  //setup communication
  Serial.begin(115200);
}

void loop() {
  for (int i = 2; i <= 10; i++) {
    currentState[i] = digitalRead(i);//read button state
    if (!wasPressed[i] && currentState[i] == LOW) { //if the state of the pin changed
      Serial.write(cmd[i - 2]); //send the data
      wasPressed[i] = true;//update the last button state
    }
    if (currentState[i] == HIGH) wasPressed[i] = false;
  }
  serialEvent();
}
void serialEvent() { //if any data was sent
  if (Serial.available() > 0) { //and there's at least 1 byte to look at
    int data = Serial.read();//read the data
    //do something with it if you want
    if (data == '1') {
      digitalWrite(12, HIGH);
    }
    if (data == '0') {
      digitalWrite(12, LOW);
    }
  }
}

