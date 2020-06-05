/* -*- mode: C++ -*-
/*
 * time-constant plotter:
 * reads analog input 2, taking a sample every D milliseconds 
 * drives out a square wave on pin every P samples
 */

// Adjust these parameters to suit your needs.
#define SAMPLE_DELAY		50	// time between data reports.  in milliseconds. 
#define SAMPLES_PER_EDGE	200	// samples between changing the OUTPUT

#define OUTPUT_PIN		10	// output pin, in arduino indexing.

#define CONTINUOUS		0	// if 1, samples continuously.
					// if 0, stops after one complete cycle

/////////////////////////////////////////////////////////////////////////////
unsigned long t_previous;
unsigned long t_previous_toggle;

uint16_t samp_count;
uint8_t output_value;
uint8_t running;

void setup()
{
	pinMode(13, OUTPUT);     // LED
	digitalWrite(13, HIGH);
	
	pinMode(16, OUTPUT);  // D16 is AD2: do a fast discharge
	digitalWrite(16, 0);

	Serial.begin(57600);
	Serial.print("#eastbots timeconstant-plotter 1\r\n");
	Serial.print("#time	drive	AD2	time_error\r\n");

	t_previous = millis();
	t_previous_toggle = t_previous;

	running = 1;
	samp_count = 0;
	output_value = 1;

	delay(1000);	    // wait a bit to ensure its discharged
	pinMode(16, INPUT); // set digital pin back to input so we can use it for anlogRead()

	pinMode(OUTPUT_PIN, OUTPUT);
	digitalWrite(OUTPUT_PIN, output_value);		
}

void loop()
{
	uint16_t ad2;

        unsigned long t_current = millis();
 	unsigned long t_delta = (unsigned long)(t_current - t_previous);

	if (t_delta >= (SAMPLE_DELAY) ) {
		t_previous = t_current;

		if(running) {
			digitalWrite(13, HIGH);
			ad2 = analogRead(2); 

			Serial.print(t_current);
			Serial.print("\t");
			Serial.print(output_value);
			Serial.print("\t");
			Serial.print(ad2);
			Serial.print("\t");

		 	long t_sample_error = (long)t_delta - SAMPLE_DELAY;
			Serial.print(t_sample_error);
			Serial.print("\r\n");

			
			samp_count++;
			if(samp_count > SAMPLES_PER_EDGE) {
				samp_count = 0;
				output_value = !output_value;

				// if the output value has gone back high
				// we've done a complete high-low cycle.
				if(output_value == 1 && !CONTINUOUS) {
					running = 0;
					Serial.print("#Done.  Press any key to run again.\r\n");
					serial_flush_input();
				} else {
					digitalWrite(OUTPUT_PIN, output_value);
				}
			}
			
			digitalWrite(13, LOW);
		} else {
			if(Serial.available() > 0) {
				uint8_t byte = Serial.read();
				running = 1;
				digitalWrite(OUTPUT_PIN, output_value);
			}
		}
	}	
}

/*
 * flush the serial input buffer by reading all available characters.
 * ensures that when we say "press any key" we wait for a new one.
 */
void
serial_flush_input()
{
	while(Serial.available()) {
		Serial.read();
 	}
}
