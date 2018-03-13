

void initTime(int tempMax){
   ResetTime();
  timeleft = tempMax*20*60;
}
void ResetTime(){
  time = 0;
  StopTime();
}
void StopTime(){
  countingTime = false;
}

void updateTime(){
  if(countingTime){
    time++;
  }
  timeleft--;
}



