#define NB_FRAME 40
void GameOverScreen()
{
  uint8_t cptFrame = NB_FRAME;
  float scoreCpt = 0;
  while(true)
  {
    if(gb.update()){
      gb.display.setFont(font5x7);
      gb.display.println("Game Over");
      gb.display.setFont(font3x5);
      gb.display.print("Clients:");
      displayInt(nbClient,4);gb.display.println("");
      gb.display.print("Dist:");
      displayInt(distTotal,6);
      gb.display.println("");
      gb.display.print("Score:");
      displayInt(scoreCpt,8);

      if(cptFrame>0)
      {
        cptFrame--;
        scoreCpt += leScoreTotal/NB_FRAME;
      }
      else
      {
        scoreCpt = leScoreTotal;
        if(haveNewHightScore())
        {
          gb.display.cursorX = 20+random(0,2);
          gb.display.cursorY = 30+random(0,2);
          gb.display.println(F("New records!"));
        }
        
        if(gb.buttons.pressed(BUTTON_A) || gb.buttons.pressed(BUTTON_B) || gb.buttons.pressed(BUTTON_C)){
          gb.sound.playOK();
          break;
        }
      }
    }
  }
  saveHighscore(leScoreTotal);
}

void upgradeScore()
{
  int diff =  (distClient * 100 / distNext)-100;
  leScoreTotal += distNext/max(2,diff);  
  distNext = 0;
  distClient = 0;
}
