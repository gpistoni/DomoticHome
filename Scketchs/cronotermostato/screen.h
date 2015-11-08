// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).


// Assign human-readable names to some common 16-bit color values:
#define BLACK    0xFFFF
#define GRAY     0x7BEF
#define YELLOW   0x001F
#define CYAN     0xF800
#define MAGENTA  0x07E0
#define RED      0x07FF
#define GREEN    0xF81F
#define BLUE     0xFFE0
#define WHITE    0x0000

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define TS_MINX  150
#define TS_MINY  120
#define TS_MAXX  920
#define TS_MAXY  940

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

class CScreen
{
  public:
    void setup(void) {

      Serial.println(F("TFT LCD"));
      Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

      tft.reset();

      uint16_t identifier = 0x9341;    //Need hardcode here (IC)
      tft.begin(identifier);

      tft.fillScreen(BLACK);
      pinMode(13, OUTPUT);
    }

    unsigned long testFillScreen()
    {
      Serial.println(F("testFillScreen"));
      unsigned long start = micros();
      tft.fillScreen(BLACK);
      tft.fillScreen(RED);
      tft.fillScreen(GREEN);
      tft.fillScreen(BLUE);
      tft.fillScreen(BLACK);
      return micros() - start;
    }


    unsigned long testText() {
      tft.fillScreen(BLACK);
      unsigned long start = micros();
      tft.setCursor(0, 0);
      tft.setTextColor(WHITE);  tft.setTextSize(1);
      tft.println("Hello World!");
      tft.setTextColor(YELLOW); tft.setTextSize(2);
      tft.println(1234.56);
      tft.setTextColor(RED);    tft.setTextSize(3);
      tft.println(0xDEADBEEF, HEX);
      tft.println();
      tft.setTextColor(GREEN);
      tft.setTextSize(5);
      tft.println("Groop");
      tft.setTextSize(2);
      tft.println("I implore thee,");
      tft.setTextSize(1);
      tft.println("my foonting turlingdromes.");
      tft.println("And hooptiously drangle me");
      tft.println("with crinkly bindlewurdles,");
      tft.println("Or I will rend thee");
      tft.println("in the gobberwarts");
      tft.println("with my blurglecruncheon,");
      tft.println("see if I don't!");
      return micros() - start;
    }

    TSPoint getTouchPoint()
    {
      digitalWrite(13, HIGH);
      TSPoint p = ts.getPoint();
      digitalWrite(13, LOW);

      // if sharing pins, you'll need to fix the directions of the touchscreen pins
      //pinMode(XP, OUTPUT);
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      //pinMode(YM, OUTPUT);

      TSPoint screenp;
      if (p.z > 0)
      {
        // scale from 0->1023 to tft.width
        screenp.z = p.z;
        screenp.x = map(p.y, TS_MINX, TS_MAXX, 0, tft.width() );
        screenp.y = map(p.x, TS_MINY, TS_MAXY, 0, tft.height() );

        Serial.print("\tX = "); Serial.print(screenp.x);
        Serial.print("\tY = "); Serial.print(screenp.y);
        Serial.print("\tPressure = "); Serial.println(screenp.z);
      }
      return screenp;
    }
};

class ButtonLabel
{
    short x0, y0;
    short w, h;
    int m_color;
    String m_label;

  public:
    ButtonLabel()
    {
    }

    void setup( short _x0, short _y0, short _w, short _h, String str, int color)
    {
      x0 = _x0;
      y0 = _y0;
      w = _w;
      h = _h;
      m_color = color;
      label( str );
      draw(true);
    }

    void label( String str)
    {
      m_label = str;
      draw(false);
    }

    void label( int v)
    {
      // utility function for digital clock display: prints preceding colon and leading 0
      String s;
      if (v < 10)
        s += "0";
      s += String(v);
      label(s);
    }

      void label( float v)
    {
      // utility function for digital clock display: prints preceding colon and leading 0
      String s;
      if (v < 10)
        s += "0";
      s += String(v);
      label(s);
    }

    
    void bkgCol( int col)
    {
       m_color = col;
    }
    
    void draw(bool shadow)
    {
      if (shadow) tft.fillRect(x0 + 2, y0 + 2, w, h, GRAY);
      tft.fillRect(x0, y0, w, h, m_color );

      tft.setCursor(x0 + 8, y0 + 8);
      tft.setTextColor(BLACK);
      tft.setTextSize(4);
      tft.println(m_label);
    }

    bool pressed( TSPoint p)
    {
      if ( p.z > 0 && p.x >= x0 && p.x < x0 + w && p.y >= y0 && p.y < y0 + h)
        return true;
      return false;
    }

};

