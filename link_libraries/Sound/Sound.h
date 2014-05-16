#ifndef SOUND_H
#define SOUND_H

class Sound {

  int speakerPin;

public:

  Sound(int);
  ~Sound();

  void beep();
  void beep(int);
//  void sweep(int,int);
//  void sweep(int,int,int);

  void setPin(int);

private:

  int sinWave(int*,int);
  int sawWave(int*,int);
  int squWave(int*,int);

};

#endif