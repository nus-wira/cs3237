void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  int value = analogRead(A0);
  Serial.print("Value : ");
  Serial.println(value);
  delay(1000);
}