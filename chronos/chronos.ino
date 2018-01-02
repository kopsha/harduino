#include <LiquidCrystal.h>
const byte rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
	// lcd setup
	char lineBuffer[17];
	sprintf( lineBuffer, "%16s", "Go with the flow" );
	lcd.begin( 16, 2 );
	lcd.print( lineBuffer );

	lcd.setCursor( 0, 1 );
	sprintf( lineBuffer, "loading..." );
	lcd.print( lineBuffer );

	// pin setup
	pinMode(LED_BUILTIN, OUTPUT);

}


unsigned long frameCounter;

void loop()
{
	lcd.setCursor(0, 1);
	lcd.print( "<ready>        " );
	delay(20);		// 20 ms for computing
	delay(13);		// 13 ms for a frame update
	frameCounter++;
}
