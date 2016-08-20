/*
  Modified version of Arduino Blink sketch.
 */

const int PORT = 8;
int i = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin PORT as an output.
  Serial.begin(9600);
  pinMode(PORT, HIGH);

  // Find the port XD
  //for (int i = 14; i<=14; i++) {
  //  pinMode(i, OUTPUT);
  //  digitalWrite(i, LOW);
  //}
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PORT, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(PORT, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second
  
  Serial.print("Loop ");
  Serial.println(i);
  i++;
}
