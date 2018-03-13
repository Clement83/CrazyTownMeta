

void drawHud()
{
  gb.display.setColor(WHITE);
  gb.display.fillCircle(4, 43, 4);
  gb.display.setColor(BLACK);
  gb.display.drawCircle(4, 43, 4);

  gb.display.setColor(BLACK, WHITE);
  gb.display.setFont(font3x3);
  displayInt(timeleft,0,0,5);
  displayInt(time,65,0,5);
  displayInt(nbClient,69,45,4);

  if(numClient>-1)
  {
    int16_t AC_C = 4;
    int16_t DB = xDest - player.x;
    int16_t AD = yDest - player.y ;
    float AB = sqrt( pow( DB,2) + pow(AD,2));
    float EC = (AC_C/AB) * DB;
    float AE = (AC_C/AB) * AD;
    gb.display.drawLine(4,43,4+EC,43+AE);
    
    gb.display.setColor(BLACK);
    gb.display.fillRoundRect(27, 0, 21, 7, 3);
    gb.display.setColor(BLUE);
  }
  else
  {
    gb.display.setColor(WHITE);
    gb.display.fillRoundRect(27, 0, 21, 7, 3);
    gb.display.setColor(BLACK);
    gb.display.drawRoundRect(27, 0, 21, 7, 3);
  }
  displayText("TAXI",30,2);

  gb.display.setFont(font3x5);
  gb.display.setColor(BLACK);
}

