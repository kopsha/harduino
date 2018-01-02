#include <LiquidCrystal.h>

const byte rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int bpm = 90;
const int beatsPerMeasure = 8;
const int subDivisions = 4;
const int oneTickInterval = 60000 / (bpm*subDivisions); // ms

unsigned long lastTime = 0;
char displayBufferRow0[17];
char displayBufferRow1[17];

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);

	lastTime = millis();
	lcd.begin( 16, 2 );

	sprintf( displayBufferRow0, "         %3d bpm", bpm );
	lcd.print( displayBufferRow0 );

	lcd.setCursor( 0, 1 );
	sprintf( displayBufferRow1, "%16s", "(c) 1979" );
	lcd.print( displayBufferRow1 );
}


void oneTick( const byte tickId )
{
	if ((tickId % 2) == 0)
	{
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else
	{
		digitalWrite(LED_BUILTIN, LOW);
	}

	static const char transl[5] = "/-`|";
	char c = transl[tickId % 4];
	lcd.setCursor( 0, 1 );
	lcd.write( c );
}

void refreshDisplay()
{
	lcd.home();
	lcd.print( displayBufferRow0 );
	//lcd.setCursor(0, 1);
	//lcd.print( displayBufferRow1 );
}

void oneBeat( const byte beatId )
{
	static byte i;

	for (i = 0; i<beatsPerMeasure; i++)
		displayBufferRow0[i] =  (i == beatId)? 'I' : '\xA5';
	displayBufferRow0[i] = '\0';

	refreshDisplay();
}

void loop() {
	static unsigned long currentTime;
	static long currentInterval;

	static byte tickId = 0;
	static byte beatId = 0;

	currentTime = millis();
	currentInterval = currentTime - lastTime;

	if (currentInterval >= oneTickInterval)
	{

		lastTime = currentTime;
		oneTick( tickId );
		if (tickId == 0)
		{
			oneBeat( beatId );
			beatId = (beatId+1) % beatsPerMeasure;
		}
		tickId = (tickId+1) % subDivisions;
	}
}

