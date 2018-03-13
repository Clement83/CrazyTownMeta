/*******
* 2014
* By clement http://quintard.me
* thx to Quirby64 for taxi graphic 
*********/

#include <Gamebuino-Meta.h>

#define LCDHEIGHT 80
#define LCDWIDTH 64


extern const byte font3x3[];
extern const byte font3x5[];
extern const byte font5x7[];

void displayText(String s, byte x, byte y, byte t);
void displayText(String s, byte x, byte y);
void displayInt(long l, byte Tx, byte Ty, byte fig);
void displayInt(long l, byte fig);
void initTime(int tempMax);
void drawBitmapAngle(int8_t x, int8_t y, const uint8_t *bitmap,float angle);

typedef struct {
  float x, y, v, vx, vy, angle;
  byte radius;
} Ufo;

Ufo player;

//destination du client
int xDest;
int yDest;
int numClient = -1;
unsigned int time = 0;
unsigned int timeleft = 0;
unsigned int leScoreTotal = 0;
unsigned int nbClient = 0;
float distTotal = 0;//total du run
float distNext = 0;//distance a vol d'oiseau du prochain client
float distClient = 0;//distance reelement parcouru pour aller au client
boolean countingTime = false;

//global variables
int camera_x, camera_y;

void setup()
{
  gb.begin();
  gb.display.setFont(font5x7);
  initHighscore();
  //drawTitleScreen();
  xDest = 1000;
  yDest = 1000;
 
}

const uint16_t GrandTaxiData1[] = {19,9,1, 1, 0, 0, 0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xffff,0x0,0xd8e4,0x0,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x0,0xf720,0xd8e4,0x0,0xffff,0xffff,0x0,0x0,0xffff,0x0,0x0,0xffff,0x0,0x0,0xffff,0x7ddf,0xffff,0x0,0x0,0xf720,0xf720,0x0,0xffff,0xffff,0x0,0x7ddf,0x7ddf,0x0,0xffff,0xffff,0xfd42,0xffff,0xffff,0x7ddf,0x7ddf,0x0,0xffff,0xffff,0x0,0x0,0x0,0xffff,0xffff,0x0,0x7ddf,0x7ddf,0x0,0xffff,0xffff,0xfd42,0xffff,0xffff,0x7ddf,0x7ddf,0x0,0xffff,0xffff,0x0,0xffff,0x0,0xffff,0xffff,0x0,0x7ddf,0x7ddf,0x0,0xffff,0xffff,0xfd42,0xffff,0xffff,0x7ddf,0x7ddf,0x0,0xffff,0xffff,0x0,0x0,0xd8e4,0x0,0xffff,0xffff,0x0,0x0,0xffff,0x0,0x0,0xffff,0x0,0x0,0xffff,0x7ddf,0xffff,0x0,0x0,0xf720,0xf720,0xd8e4,0x0,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x0,0xf720,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xffff,0x0};
Image GrandTaxi1 = Image(GrandTaxiData1);

void loop(){
  drawMenu();
}

void initGame(int tempMax){
  initPlayer();
  distTotal = 0;
  distNext = 0;
  distClient = 0;
  nbClient = 0;
  leScoreTotal = 0;
  initTime(tempMax);
  gb.display.setFont(font3x5);
}

void play(){
  while(true) {
    if(gb.update()){
      gb.display.clear();
      //pause the game if C is pressed
      if(gb.buttons.pressed(BUTTON_C)){
        gb.display.setFont(font5x7);
        break;
      }
      
      if(timeleft == 0)
      {
        GameOverScreen();
        return;
      }

      updatePlayer();
      updateTime();
      updateClient();
      
      //drawWorld();
      drawPlayer();
      //DrawClient();
      //drawHud();
    }
  }
}


//101 starship function
void displayText(String s, byte x, byte y){
  gb.display.cursorX = x;
  gb.display.cursorY = y;  
  gb.display.print(s);
}

void displayInt(long l, byte Tx, byte Ty, byte fig){
  gb.display.fontSize = 1;
  String sl = String(l);
  while(sl.length() < fig){
    sl = "0" + sl;  
  }
  gb.display.cursorX = Tx;
  gb.display.cursorY = Ty;  
  gb.display.print(sl);
}

void displayInt(long l, byte fig){
  gb.display.fontSize = 1;
  String sl = String(l);
  while(sl.length() < fig){
    sl = "0" + sl;  
  } 
  gb.display.print(sl);
}
