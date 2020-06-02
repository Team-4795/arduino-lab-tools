/* -*- mode: C++ -*-

/*
 * Steve's variation on the basic arduino blink-the-LED program
 *	distinctive startup slow-flash
 *	distinctive continuous double-flash 
 */

void setup() {                
	pinMode(13, OUTPUT);     // Pin 13 has an LED connected on most Arduino boards:
  
	digitalWrite(13, HIGH);   // set the LED on
	delay(1000);              // wait for a second
	digitalWrite(13, LOW);    // set the LED off
	delay(1000);
	digitalWrite(13, HIGH);   // on
	delay(1000);
	digitalWrite(13, LOW);    // off
	delay(1000);
}

void loop() {
	digitalWrite(13, HIGH);
	delay(150);
	digitalWrite(13, LOW);
	delay(200);
	digitalWrite(13, HIGH);
	delay(150);
	digitalWrite(13, LOW);
	delay(500);
}
