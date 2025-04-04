
const int SENSOR_1_OUT = 2;
const int SENSOR_1_IN = 3;
const int out23 = 10;
int prev = 0;

const int threshold1 = 200; //default 100 R

void setup()
{
  pinMode(SENSOR_1_OUT, OUTPUT);
  pinMode(SENSOR_1_IN, INPUT);
  pinMode(out23, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  int counter = 0;
  int counter2 = 0;
  digitalWrite(SENSOR_1_OUT, HIGH);
  while (digitalRead(SENSOR_1_IN) != HIGH) counter++;
  digitalWrite(SENSOR_1_OUT, LOW);
  Serial.println(counter);
  delay(1);

//  // low-pass filter
  counter = 0.8 * prev + 0.2 * counter; //default 0.3 : 0.7
  prev = counter;

  Serial.println(counter);
  
  if (counter > threshold1) {
    digitalWrite(out23, HIGH);
    delay(5);
  } else {
    digitalWrite(out23, LOW);
  }


  
}
