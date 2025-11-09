const int EB = 12; // East Boundary (Limit Switch)
const int WB = 11; // West Boundary (Limit Switch)
#define ENABLE_PIN 10
#define MS1_PIN 9
#define MS2_PIN 8
#define MS3_PIN 7
#define RST_PIN 6
#define SLP_PIN 5
#define STEP_PIN 4
#define DIR_PIN 3

const int LDR1_PIN = A0;   // First LDR on A0
const int LDR2_PIN = A1;   // Second LDR on A1
const int THRESHOLD = 50;  // Tolerance for considering the LDRs equal
int stepDelay = 1000;      // Delay in microseconds, controls motor speed

void setup() {
    pinMode(EB, INPUT_PULLUP);
    pinMode(WB, INPUT_PULLUP);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);
    pinMode(MS1_PIN, OUTPUT);
    pinMode(MS2_PIN, OUTPUT);
    pinMode(MS3_PIN, OUTPUT);
    pinMode(LDR1_PIN, INPUT);
    pinMode(LDR2_PIN, INPUT);

    pinMode(SLP_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
    digitalWrite(ENABLE_PIN, HIGH); // Disable the driver initially
    digitalWrite(RST_PIN, HIGH);
    digitalWrite(SLP_PIN, HIGH);

    // Set default microstepping mode to Full Step
    set2Step();

    Serial.begin(9600); // Start Serial Monitor
}

void loop() {
    // Read limit switches
    bool wbPressed = digitalRead(WB) == LOW; // West Boundary switch pressed
    bool ebPressed = digitalRead(EB) == LOW; // East Boundary switch pressed

    // Read LDR values
    int ldr1Value = analogRead(LDR1_PIN); // Read LDR1
    int ldr2Value = analogRead(LDR2_PIN); // Read LDR2

    // Print LDR values to Serial Monitor
    Serial.print("LDR1 Value: ");
    Serial.print(ldr1Value);
    Serial.print(" | LDR2 Value: ");
    Serial.println(ldr2Value);

    // Check if a limit switch is pressed
    if (wbPressed) {
        Serial.println("West Limit Switch Pressed. Motor Stopped.");
        digitalWrite(ENABLE_PIN, HIGH); // Disable the driver
        delay(500); // Wait before next check
        return; // Exit loop to stop processing
    }

    if (ebPressed) {
        Serial.println("East Limit Switch Pressed. Motor Stopped.");
        digitalWrite(ENABLE_PIN, HIGH); // Disable the driver
        delay(500); // Wait before next check
        return; // Exit loop to stop processing
    }

    // Calculate the difference between LDR values
    int difference = ldr1Value - ldr2Value;

    if (abs(difference) <= THRESHOLD) {
        // If both values are relatively equal, stop the motor
        Serial.println("Motor Stopped (LDRs are equal)");
        digitalWrite(ENABLE_PIN, HIGH); // Disable the driver to reduce heat
        delay(500); // Wait before the next reading
        return;
    } else {
        digitalWrite(ENABLE_PIN, LOW); // Enable the driver
        if (difference > THRESHOLD && !ebPressed) {
            // If LDR1 value is higher, move eastward (forward direction)
            Serial.println("Motor Moving Forward (East)");
            digitalWrite(DIR_PIN, HIGH);
        } else if (difference < -THRESHOLD && !wbPressed) {
            // If LDR2 value is higher, move westward (backward direction)
            Serial.println("Motor Moving Backward (West)");
            digitalWrite(DIR_PIN, LOW);
        } else {
            // Stop motor if a limit switch blocks movement in the desired direction
            Serial.println("Movement Blocked by Limit Switch");
            digitalWrite(ENABLE_PIN, HIGH);
            delay(500); // Wait before next action
            return;
        }

        // Rotate the motor
        for (int i = 0; i < 200; i++) { // Adjust for motor's steps per revolution
            digitalWrite(STEP_PIN, HIGH);
            delayMicroseconds(stepDelay); // Control speed
            digitalWrite(STEP_PIN, LOW);
            delayMicroseconds(stepDelay);
        }
    }

    delay(500); // Wait before the next action
}

// Microstepping Functions
void set1Step() {
    digitalWrite(MS1_PIN, LOW);
    digitalWrite(MS2_PIN, LOW);
    digitalWrite(MS3_PIN, LOW);
    Serial.println("Microstepping: Full Step");
}

void set2Step() {
    digitalWrite(MS1_PIN, HIGH);
    digitalWrite(MS2_PIN, LOW);
    digitalWrite(MS3_PIN, LOW);
    Serial.println("Microstepping: Half Step");
}

void set4Step() {
    digitalWrite(MS1_PIN, LOW);
    digitalWrite(MS2_PIN, HIGH);
    digitalWrite(MS3_PIN, LOW);
    Serial.println("Microstepping: Quarter Step");
}

void set8Step() {
    digitalWrite(MS1_PIN, HIGH);
    digitalWrite(MS2_PIN, HIGH);
    digitalWrite(MS3_PIN, LOW);
    Serial.println("Microstepping: Eighth Step");
}

void set16Step() {
    digitalWrite(MS1_PIN, HIGH);
    digitalWrite(MS2_PIN, HIGH);
    digitalWrite(MS3_PIN, HIGH);
    Serial.println("Microstepping: Sixteenth Step");
}

void set32Step() {
    // For drivers like DRV8825 supporting 1/32 step
    digitalWrite(MS1_PIN, HIGH);
    digitalWrite(MS2_PIN, HIGH);
    digitalWrite(MS3_PIN, HIGH);
    Serial.println("Microstepping: Thirty-second Step");
}
