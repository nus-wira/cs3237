void setup() {
  Serial.begin(9600);
  while(!Serial) { }
  Serial.println("Start device in normal mode!");
  delay(5000);
  Serial.println("I'm going into deep sleep mode for 20 seconds");
  ESP.deepSleep(20e6); // Time in *microseconds*
}

void loop() {
}