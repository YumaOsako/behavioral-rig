// Pin Definitions
const int SENSOR_TRIGGER_PIN = 2;  // Output pin to trigger sensor
const int SENSOR_READ_PIN = 3;     // Input pin to read sensor response
const int OUTPUT_PIN = 10;          // Control pin for output device
int filteredValue = 0;              // Stores filtered sensor reading

// Configuration Constants
const int ACTIVATION_THRESHOLD = 200;  // Threshold for output activation
const float FILTER_WEIGHT_PREVIOUS = 0.8;  // Weight for previous value in low-pass filter
const float FILTER_WEIGHT_CURRENT = 0.2;    // Weight for current reading in low-pass filter

void setup() {
  // Initialize pin modes
  pinMode(SENSOR_TRIGGER_PIN, OUTPUT);
  pinMode(SENSOR_READ_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  int rawReading = 0;
  
  // Trigger sensor and measure response time
  digitalWrite(SENSOR_TRIGGER_PIN, HIGH);
  while (digitalRead(SENSOR_READ_PIN) != HIGH) {
    rawReading++;
  }
  digitalWrite(SENSOR_TRIGGER_PIN, LOW);
  
  // Print raw reading for debugging
  //Serial.print("Raw: ");
  //Serial.println(rawReading);
  
  // Apply low-pass filter to stabilize readings
  filteredValue = FILTER_WEIGHT_PREVIOUS * filteredValue + FILTER_WEIGHT_CURRENT * rawReading;
  
  // Print filtered value for debugging
  //Serial.print("Filtered: ");
  //Serial.println(filteredValue);
  
  // Control output based on threshold
  if (filteredValue > ACTIVATION_THRESHOLD) {
    digitalWrite(OUTPUT_PIN, HIGH);
    delay(5);  // Output activation duration
  } else {
    digitalWrite(OUTPUT_PIN, LOW);
  }
  
  delay(1);  // Short delay between readings
}