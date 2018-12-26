#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    Serial.println("Begin...");
}

#define BUFFER_SIZE 20
void loop() {
    static char buffer[20];
    static int buffer_index;

    for (int i=Serial.available(); i > 0; i--) {
        char c = Serial.read();
        Serial.write(c);
        if (buffer_index == (BUFFER_SIZE - 1)) {
            Serial.println("Error: Buffer overflow.  Ignoring data");
            buffer_index++;
        }
        else {
            buffer[buffer_index] = c;
            if (c == '\n') {
                buffer[buffer_index] = '\0';
                if (buffer_index > 0) {
                    buffer_index = 0;
                    int i = atoi(buffer);
                    Serial.println(i);
                }
            }
            else if (c == '\r') {
                ;
            }
            else if ((c >= '0') && (c <= '9')) {
                buffer[buffer_index] = c;
                buffer_index++;
            }
            else {
                Serial.println("Ignoring unknown character: ");
                Serial.println((int)c);
            }
        }
    }
    delay(10);
}