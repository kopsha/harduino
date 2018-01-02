#include <LiquidCrystal.h>



const byte rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long frameCounter;
unsigned long timeCounter;
bool isFirstRun = true;

void setup()
{
	timeCounter = micros();
	// lcd setup
	char lineBuffer[17];
	sprintf( lineBuffer, "%-16s", "booting..." );
	lcd.begin( 16, 2 );
	lcd.print( lineBuffer );

	// pin setup
	pinMode(LED_BUILTIN, OUTPUT);

}



void loop()
{
	unsigned long loadingTime = micros();

	// mimic bullshit
	digitalWrite(LED_BUILTIN, HIGH);
	delay(20);		// 20 ms for computing
	digitalWrite(LED_BUILTIN, LOW);
	delay(13);		// 13 ms for a frame update

	static char lineBuffer[17];

	if (isFirstRun)
	{
		loadingTime -= timeCounter;
		sprintf( lineBuffer, "took %7d us", loadingTime );

		lcd.setCursor(0, 1);
		lcd.print( lineBuffer );

		isFirstRun = false;
	}
	frameCounter++;
}
