#include <Arduino.h>
/**SPOTIFY libs**/
#include <WiFi.h>

//#define DBG_SERIAL
/*
#define DISABLE_ALBUM
#define DISABLE_ARTIST
#define DISABLE_AUDIOBOOKS
#define DISABLE_CATEGORIES
#define DISABLE_CHAPTERS
#define DISABLE_EPISODES
#define DISABLE_GENRES
#define DISABLE_MARKETS
#define DISABLE_PLAYLISTS
#define DISABLE_SEARCH
#define DISABLE_SHOWS
#define DISABLE_TRACKS

#define DISABLE_WEB_SERVER
*/
#include <SpotifyEsp32.h>
#include "settings.h"
/**END Spotify libs****/

/**OLED Libs**/
#include <Wire.h>
#include <U8g2lib.h>

/*END oled libs*/

/*touch buttons libs*/
#include "touchbutton.h"
/*END touch buttons libs*/


/**OLED vars**/
U8G2_SSD1306_128X64_NONAME_F_SW_I2C 
u8g2(U8G2_R0,22,21,U8X8_PIN_NONE);/*22CLOCK/21 DATA*/
/**ENDS***/

Spotify sp(CLIENT_ID, CLIENT_SECRET, REFRESH_TOKEN);

struct Button button1 = {BUTTON1, 0, 0,0,0};
struct Button button2 = {BUTTON2, 0, 0,0,0};
struct Button button3 = {BUTTON3, 0, 0,0,0};
struct Button button4 = {BUTTON4, 0, 0,0,0};

void setup() {
#ifdef DBG_SERIAL  
    Serial.begin(115200);
#endif    
    connect_to_wifi();
    
    sp.begin();
    while(!sp.is_auth()){
        sp.handle_client();
    }
#ifdef DBG_SERIAL      
    Serial.println("Authenticated");
#endif
    sp.pause_playback();
    u8g2.begin();
    setup_buttons();
}

void drawLines(String song,String artis)
{
  String temp =  "volumen";
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_9x15_tr);
  u8g2.drawStr(0,10,"Song playing");
  u8g2.drawStr(0,21,(song.c_str()));
  u8g2.drawStr(0,32,"Artist");

  u8g2.drawStr(0,43,(artis.c_str()));
  u8g2.drawStr(0,54,temp.c_str());
  u8g2.sendBuffer();
  
}
void loop() {
    static String lastArtist;
    static String lastTrackname;
    
    String currentArtist = sp.current_artist_names();
    String currentTrackname = sp.current_track_name();
    
   
   
    
    if (lastArtist != currentArtist && currentArtist != "Something went wrong" && !currentArtist.isEmpty()) {
        lastArtist = currentArtist;
#ifdef DBG_SERIAL  
        Serial.println("Artist: " + lastArtist);
#endif
        drawLines(currentTrackname,currentArtist);
    }
    
    if (lastTrackname != currentTrackname && currentTrackname != "Something went wrong" && currentTrackname != "null") {
        lastTrackname = currentTrackname;
#ifdef DBG_SERIAL  
        Serial.println("Track: " + lastTrackname);
        drawLines(currentTrackname,currentArtist);
#endif    
    }
    
  checkPressed(&button1);
  checkPressed(&button2);
  checkPressed(&button3);
  checkPressed(&button4);
}

void connect_to_wifi(){
    WiFi.begin(SSID, PASSWORD);
#ifdef DBG_SERIAL  
    Serial.print("Connecting to WiFi...");
#endif 
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
#ifdef DBG_SERIAL          
        Serial.print(".");
#endif
    }
#ifdef DBG_SERIAL      
    Serial.printf("\nConnected to WiFi\n");
#endif
}
