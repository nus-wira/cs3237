#define SWITCH D5

byte state = LOW;
unsigned long debounceDelay = 200;
unsigned long lastDebounceTime = 0;

void setup() {
    Serial.begin(9600);
    pinMode(SWITCH, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(SWITCH) == LOW 
            && millis() - lastDebounceTime > debounceDelay) {
        state = !state;
        lastDebounceTime = millis();
    }
    
    if (state) {
        Serial.println("Toggle On");
    } else {
        Serial.println("Toggle Off");
    }
}