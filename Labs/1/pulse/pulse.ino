#define LED D4
#define MAX_BRIGHT 255
#define MIN_BRIGHT 0

int Brightness = 20;
int increment = 1;

void setup() {
    pinMode(LED, OUTPUT);
    analogWrite(LED, Brightness);
}
void loop() {
    if (Brightness >= MAX_BRIGHT)
        increment = -1;
    else if (Brightness <= MIN_BRIGHT)
        increment = 1;
    Brightness += increment;
    analogWrite(LED, Brightness);
}