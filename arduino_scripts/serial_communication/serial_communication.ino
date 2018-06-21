int ledPin = 13;
String readString;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }
  readString.trim();
  if (readString.length() > 0) {
    if (readString == "A1111") {
      //Serial.println("switching on");
      digitalWrite(ledPin, HIGH);
    }
    if (readString == "A0000")
    {
      //Serial.println("switching off");
      digitalWrite(ledPin, LOW);
    }
    readString = "";
  }
}
