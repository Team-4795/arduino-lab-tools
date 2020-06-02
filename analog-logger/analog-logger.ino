/* -*- mode: C++ -*-

/*
 * simple analog data logger.  Reads analog input 0 and 1.
 */

// time between data reports.  in milliseconds.  Adjust to suit your needs.
#define SAMPLE_DELAY		1000


/////////////////////////////////////////////////////////////////////////////
unsigned long t_previous;

void setup()
{
	pinMode(13, OUTPUT);     // LED
	Serial.begin(57600);
	Serial.print("#eastbots analog-logger 1\r\n");
	Serial.print("#time(ms)	AD0	AD1	time_error\r\n");

	t_previous = millis();
}

void loop()
{
	uint16_t ad0;
	uint16_t ad1;

        unsigned long t_current = millis();
 	unsigned long t_delta = (unsigned long)(t_current - t_previous);

	if (t_delta >= (SAMPLE_DELAY) ) {
		digitalWrite(13, HIGH);
		ad0 = analogRead(0); 
		ad1 = analogRead(1);
		digitalWrite(13, LOW);    // set the LED off

		Serial.print(t_current);
		Serial.print("\t");
		Serial.print(ad0);
		Serial.print("\t");
		Serial.print(ad1);
		Serial.print("\t");

	 	long t_sample_error = (long)t_delta - SAMPLE_DELAY;
		Serial.print(t_sample_error);
		Serial.print("\r\n");

		t_previous = t_current;
	}	
}

