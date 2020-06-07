/*  -*- mode: C++ -*-
 * measure high and low period, and calculate duty cycle and frequency.
 *
 * inspired by
 * https://create.arduino.cc/projecthub/ambhatt/frequency-and-duty-cycle-measurement-using-arduino-1e4896
 */

#define PULSE_INPUT 7

#include <Arduino.h>

unsigned long ontime,offtime,duty,period;
float freq;
   
void setup()
{
	pinMode(PULSE_INPUT, INPUT);
	Serial.begin(57600);
	Serial.print("#eastbots period+frequency measurement v1\r\n");
	Serial.print("#t_low t_high period duty% frequency\r\n");
}

void loop()
{
	ontime = pulseIn(PULSE_INPUT, HIGH);
	offtime = pulseIn(PULSE_INPUT, LOW);
	period = ontime + offtime;
	freq = 1000000.0/period;
	duty = (ontime*100.0/period);

	Serial.print(offtime);
	Serial.print("us\t");
	Serial.print(ontime);
	Serial.print("us\t");
	Serial.print(period);
	Serial.print("us\t");
	Serial.print(duty);
	Serial.print("%\t");
	Serial.print(freq);
	Serial.print("Hz\r\n");
	delay(1000);
}
