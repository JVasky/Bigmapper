#include <Sound.h>
#include <Arduino.h>

Sound::Sound(int speakerPin){
  Sound::speakerPin = speakerPin;
}

Sound::~Sound(){}

void Sound::setPin(int speakerPin){
  Sound::speakerPin = speakerPin;
}

void Sound::beep(){
  beep(Sound::speakerPin);
}

void Sound::beep(int pin){
  unsigned long start = millis();
  int wave = 0;
  while(millis() < start + 500){
    analogWrite(pin,sinWave(&wave,10));
  }
  analogWrite(pin,0);
}

 // Wave functions (generate an int from 0 to 255)
  
int Sound::sinWave(int *t, int freq){
  *t = (*t + 1)%freq;
  return (255/2)*(sin((2*PI/freq)*(*t))+1);
}

int Sound::squWave(int *t, int freq){
  *t = (*t + 1)%freq;
  return 255*(*t > freq/2 ? 1:0);
}

int Sound::sawWave(int *t, int freq){
  *t = (*t+1)%freq;
  boolean firstHalf = *t<(freq/2);
  return (int)(((double)*t*255*2*(firstHalf?1:-1))/freq)+(firstHalf?0:510.0);
}