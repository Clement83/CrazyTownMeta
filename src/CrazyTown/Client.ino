#define DIST_RECUP_DEPOS 16
#define NB_CLIENT 4
//x1,y1
float Clients[NB_CLIENT*2];
const byte Client1[] PROGMEM = {
  8,8,0x38,0xB9,0x92,0x7C,0x10,0x10,0x28,0x44,};
const byte Client2[] PROGMEM = {8,8,0x38,0x38,0x10,0xFC,0x92,0x11,0x28,0x44,};

void updateClient()
{
  //MAJ des clients
  for(int i =0;i<NB_CLIENT;i++)
  {
    if(numClient==i)
      continue;//Client dans le taxi on ne l'affiche pas

    int x = Clients[i*2];
    int y = Clients[i*2 + 1];
    int camXCenter = player.x; // camera_x + LCDHEIGHT/2;
    int camYCenter = player.y; //camera_y + LCDWIDTH/2;
    int dist =sqrt( pow(x-camXCenter,2) + pow(y-camYCenter,2));
    byte spriteID = 1;
    if(dist>150)
    {
      do
      {
        Clients[i*2]  = camXCenter + random(-LCDWIDTH*2,LCDWIDTH*2);
        Clients[i*2 + 1] = camYCenter  + random(-LCDHEIGHT*2,LCDHEIGHT*2);

        spriteID = getTile(Clients[i*2]/16,Clients[i*2 + 1]/16);
      }
      while(spriteID != 0);
    }
    else if(numClient==-1 && dist<DIST_RECUP_DEPOS &&  abs(player.v)<0.1)
    {
      //On monte dans le taxi
      numClient = i;
      ResetTime();
      countingTime = true;
      gb.sound.playOK();
 byte spriteID = 1;
      do
      {
        xDest  = random (100,2000);
        yDest = random (100,2000);
       spriteID = getTile(xDest/16,yDest/16);
      }
      while(spriteID != 0);

      int DB = xDest - player.x;
      int AD = yDest - player.y ;
      distNext = sqrt( pow( DB,2) + pow(AD,2));//distance du prochain point

    } else {
      if(gb.frameCount%3 == 0) {
        uint8_t maxBoucle = 4;
        float pDestX = 0;
        float pDestY = 0;
        float xx = 0;
        float yy = 0;
        do
        {
          xx = random(-1, 1) ;
          yy = random(-1, 1) ;
          pDestX = Clients[i*2] + (xx);
          pDestY = Clients[i*2 + 1] + (yy);
          spriteID = getTile(pDestX / 16, pDestY / 16);
        }while(--maxBoucle > 0 && spriteID != 0);
        if(maxBoucle>0) {
          Clients[i*2] = pDestX;
          Clients[i*2 + 1] = pDestY;
        }
        
      }
    }
  }
    if(numClient>-1)
    {
      int DB = xDest - player.x;
      int AD = yDest - player.y ;
      float AB = sqrt( pow( DB,2) + pow(AD,2));
      if(AB<DIST_RECUP_DEPOS &&  sqrt(pow(player.v,2))<0.1)
      {
        nbClient++;
        numClient = -1;
        StopTime();
        xDest  = -20;
        yDest = -20;
        gb.sound.playOK();
        upgradeScore();
      }
    }
}

void DrawClient()
{
  for(int i =0;i<NB_CLIENT;i++)
  {
    if(numClient==i)
      continue;//Client an taxi on l'affiche pas

    int x = Clients[i*2];
    int y = Clients[i*2 + 1];
    int x_screen = x - camera_x;
    int y_screen = y - camera_y;
    if(!(x_screen < -16 || x_screen > LCDWIDTH || y_screen < -16 || y_screen > LCDHEIGHT)){
      if(gb.frameCount % 10 >4) { 
        gb.display.drawBitmap(x_screen, y_screen, Client1);
      } else {
        gb.display.drawBitmap(x_screen, y_screen, Client2);
      }
    }
  }

  int x_screen = xDest - camera_x;
  int y_screen = yDest - camera_y;
  if(!(x_screen < -16 || x_screen > LCDWIDTH || y_screen < -16 || y_screen > LCDHEIGHT)){
    gb.display.drawCircle(x_screen, y_screen, 4);
    gb.display.drawCircle(x_screen, y_screen, 1);
  }
}

