#define SWITCH D5

volatile byte pressed = LOW;
byte state = LOW;

unsigned long debounceDelay = 200;
unsigned long lastDebounceTime = 0;

IRAM_ATTR void toggle() {
    pressed = HIGH;
}

void setup() {
    Serial.begin(9600);
    pinMode(SWITCH, INPUT_PULLUP);
    attachInterrupt(
        digitalPinToInterrupt(SWITCH),
        toggle, RISING);
}

void loop() {
    Serial.print("Working hard...");
    delay(1000);
    Serial.print("done. State: ");

    if (pressed == HIGH) {
        pressed = LOW;
        if (millis() - lastDebounceTime > debounceDelay) {
            state = !state;
            lastDebounceTime = millis();
        }
    }

    if (state) {
        Serial.println("Toggle On");
    } else {
        Serial.println("Toggle Off");
    }
}