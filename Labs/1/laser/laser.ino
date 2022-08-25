#define LASER D5
#define SW D6
#define X_PIN A0

void setup ()
{
   pinMode (LASER, OUTPUT); // define the digital output interface 13 feet
   pinMode(SW, INPUT);
   digitalWrite(SW, HIGH);
   Serial.begin(115200);
}
void loop () {

    Serial.print("Switch:  ");
    Serial.print(digitalRead(SW));
    Serial.print("\n");
    Serial.print("X-axis: ");
    int x = analogRead(X_PIN);
    Serial.print(x);
    Serial.print("\n\n");
    if (x < 128)
        digitalWrite(LASER, HIGH);
    else
        digitalWrite(LASER, LOW);
}
