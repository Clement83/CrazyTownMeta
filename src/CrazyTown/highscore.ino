#define NUM_HIGHSCORE 5
int highscore[NUM_HIGHSCORE];
#define NAMELENGTH 10
char name[NUM_HIGHSCORE][NAMELENGTH+1];

const uint16_t highscore_sound[] PROGMEM = {
  0x0005,0x140,0x150,0x15C,0x170,0x180,0x16C,0x154,0x160,0x174,0x184,0x14C,0x15C,0x168,0x17C,0x18C,0x0000};

void initHighscore(){
  for(byte thisScore = 0; thisScore < NUM_HIGHSCORE; thisScore++){
    for(byte i=0; i<NAMELENGTH; i++){
      //name[thisScore][i] = EEPROM.read(i + thisScore*(NAMELENGTH+2));
    }
    //highscore[thisScore] = EEPROM.read(NAMELENGTH + thisScore*(NAMELENGTH+2)) & 0x00FF; //LSB
    //highscore[thisScore] += (EEPROM.read(NAMELENGTH+1 + thisScore*(NAMELENGTH+2)) << 8) & 0xFF00; //MSB
    highscore[thisScore] = /*(highscore[thisScore]==9999) ? 0 : */ highscore[thisScore];
  }
}

bool haveNewHightScore()
{
  return leScoreTotal > highscore[NUM_HIGHSCORE-1];
}

void saveHighscore(unsigned int score){
  if(haveNewHightScore()){//if it's a highscore
      gb.getDefaultName(name[NUM_HIGHSCORE-1]);
      gb.keyboard(name[NUM_HIGHSCORE-1], NAMELENGTH+1);
      highscore[NUM_HIGHSCORE-1] = score;
      for(byte i=NUM_HIGHSCORE-1; i>0; i--){ //bubble sorting FTW
        if(highscore[i-1] < highscore[i]){
          char tempName[NAMELENGTH];
          strcpy(tempName, name[i-1]);
          strcpy(name[i-1], name[i]);
          strcpy(name[i], tempName);
          unsigned int tempScore;
          tempScore = highscore[i-1];
          highscore[i-1] = highscore[i];
          highscore[i] = tempScore;
        }
        else{
          break;
        }
      }
      for(byte thisScore = 0; thisScore < NUM_HIGHSCORE; thisScore++){
        for(byte i=0; i<NAMELENGTH; i++){
          //EEPROM.write(i + thisScore*(NAMELENGTH+2), name[thisScore][i]);
        }
        //EEPROM.write(NAMELENGTH + thisScore*(NAMELENGTH+2), highscore[thisScore] & 0x00FF); //LSB
        //EEPROM.write(NAMELENGTH+1 + thisScore*(NAMELENGTH+2), (highscore[thisScore] >> 8) & 0x00FF); //MSB
      }
      drawHighScores();
  }
}

void drawHighScores(){
  while(true){
    if(gb.update()){
      gb.display.cursorX = 9+random(0,2);
      gb.display.cursorY = 0+random(0,2);
      gb.display.println(F("BEST SCORE"));
      gb.display.textWrap = false;
      gb.display.cursorX = 0;
      gb.display.cursorY = gb.display.fontHeight;
      for(byte thisScore=0; thisScore<NUM_HIGHSCORE; thisScore++){
        if(highscore[thisScore]==0)
          gb.display.print('-');
        else
          gb.display.print(name[thisScore]);
        gb.display.cursorX = LCDWIDTH-4*gb.display.fontWidth;
        gb.display.cursorY = gb.display.fontHeight+gb.display.fontHeight*thisScore;
        gb.display.println(highscore[thisScore]);
      }
      if(gb.buttons.pressed(BUTTON_A) || gb.buttons.pressed(BUTTON_B) || gb.buttons.pressed(BUTTON_C)){
        gb.sound.playOK();
        break;
      }
    }
  }
}




