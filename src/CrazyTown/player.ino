#define DEMI_PI 0.157


//const byte GrandTaxi[] PROGMEM = {24,9,0xFF,0xFF,0xA0,0xC0,0x0,0x60,0xCD,0xB5,0xE0,0x96,0xC,0x60,0x96,0x4C,0x40,0x96,0xC,0x60,0xCD,0xB5,0xE0,0xC0,0x0,0x60,0xFF,0xFF,0xA0,};

const uint8_t GrandTaxiData[] = {19, 9, 1, 0, 1, 0xFF, 1, 0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x09, 0x08,0x0b, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0x0a, 0x80,0xbb, 0x00,0xb0, 0x0b,0x00, 0xbc,0xb0, 0x0a,0xa0, 0xbb,0x0c, 0xc0,0xbb, 0x9b,0xbc, 0xc0,0xbb, 0x00,0x0b, 0xb0,0xcc, 0x0b,0xb9, 0xbb,0xcc, 0x0b,0xb0, 0x70,0xbb, 0x0c,0xc0, 0xbb,0x9b, 0xbc,0xc0, 0xbb,0x00, 0x80,0xbb, 0x00,0xb0, 0x0b,0x00, 0xbc,0xb0, 0x0a,0xa8, 0x0b,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0x0a,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x0009};
Image GrandTaxi = Image(GrandTaxiData);



void initPlayer(){
  player.radius = 4;
  player.x = 20;
  player.y = 20;
  player.v = 0;
  player.vx = 0;
  player.vy = 0;
  player.angle = 0;
  numClient=-1;
}

void updatePlayer(){

  if(gb.buttons.repeat(BUTTON_RIGHT, 1)){
    player.angle += DEMI_PI;
  }
  if(gb.buttons.repeat(BUTTON_LEFT, 1)){
    player.angle -= DEMI_PI;
  }
  if(gb.buttons.repeat(BUTTON_A, 1)){
    player.v += 0.02;
  }
  if(gb.buttons.repeat(BUTTON_B, 1)){
    player.v *= 0.8;
    player.vx *= 0.8;
    player.vy *= 0.8;
  }

  byte currentTile = getTile(player.x/16, player.y/16);

  //friction
  switch(currentTile){
  case 0: //road
    player.v *= 0.95;
    player.vx *= 0.9;
    player.vy *= 0.9;
    break;
  }


  //speed update
  player.vx += cos(player.angle)*player.v;
  player.vy += sin(player.angle)*player.v;

  //collisions
  player.x += player.vx;
  currentTile = getTile(player.x/16, player.y/16);
  if(currentTile == 1){
    player.x -= player.vx;

      player.vx *= -0.5;
      gb.sound.playTick();
    player.v *= 0.5;
  }

  player.y += player.vy;
  currentTile = getTile(player.x/16, player.y/16);
  if(currentTile == 1){
    player.y -= player.vy;
      player.vy *= -0.5;
      gb.sound.playTick();
    player.v *= 0.5;
  }
  
  distTotal += 8 * abs(player.v<0)  ;
  if(numClient>-1)
  {
    //le compteur tourne !
    distClient += 8 * abs(player.v<0) ;
  }

  //target position of the camera for the cursor to be centered
  int camera_x_target = player.x + cos(player.angle)*player.v*64 - LCDWIDTH/2;
  int camera_y_target = player.y + sin(player.angle)*player.v*64- LCDHEIGHT/2;
  //apply the target coordinate to the current coordinates with some smoothing
  camera_x = (camera_x*3 + camera_x_target)/4;
  camera_y = (camera_y*3 + camera_y_target)/4;
}

void drawPlayer(){
  int x_screen = (int)player.x - camera_x;
  int y_screen = (int)player.y - camera_y;
  if(!(x_screen < -16 || x_screen > LCDWIDTH || y_screen < -16 || y_screen > LCDHEIGHT)){
      drawBitmapAngleColor(x_screen, y_screen, GrandTaxi, player.angle);
  }
}



