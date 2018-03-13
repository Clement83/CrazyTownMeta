#define PAUSEMENULENGTH 7
const char strContinue[] PROGMEM = "Continue";
const char strPlay3[] PROGMEM = "3 min play";
const char strPlay5[] PROGMEM = "5 min play";
const char strPlay10[] PROGMEM = "10 min play";
const char strHighScores[] PROGMEM = "High scores";
const char strMaps[] PROGMEM = "Map";
//const char strSystemInfo[] PROGMEM = "System Info";
const char strMainMenu[] PROGMEM = "Main Menu";


const char* const pauseMenu[PAUSEMENULENGTH] PROGMEM = {
  strContinue,
  strPlay3,
  strPlay5,
  strPlay10,
  strMaps,
  strHighScores,
  strMainMenu
};

void drawMenu(){
  switch(gb.menu(pauseMenu, PAUSEMENULENGTH)){
  case 1: //play
    initGame(3);
    play();
    break;
  case 2: //play
    initGame(5);
    play();
    break;
  case 3: //play
    initGame(10);
    play();
    break;
  case 0: //continue
    if(timeleft>0)
    {
      play();
    }
    break;
  case 4 : 
      drawMiniMap();
    break;
  case 5: //Hight score
    drawHighScores();
    break;
  default: //title screen
    drawTitleScreen();
    break;
  }
}



