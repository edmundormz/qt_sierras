int ledPin = 13;
String readString;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char DatoSerial = Serial.read();
    readString += DatoSerial;
    readString.trim();

    if (readString == "a") {
      int LecturaADC_A = analogRead(A0);
      Serial.write(LecturaADC_A >> 8);
      Serial.write(LecturaADC_A);
      /*
        int LecturaADC_B = analogRead(A1);
        Serial.write(LecturaADC_B>>8);
        Serial.write(LecturaADC_B);
      */
    }
    else if (readString == "A1111") {
      //Serial.println("switching on");
      digitalWrite(ledPin, HIGH);
    }
    else if (readString == "A0000") {
      //Serial.println("switching off");
      digitalWrite(ledPin, LOW);
    }
    readString = "";
  }
}
