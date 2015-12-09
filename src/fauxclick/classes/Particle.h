#pragma once
#include "ofMain.h"

class Particle {

protected:
  ofPoint position;
  float power;
  float size;
  float decaySize;
  float smoothedSize;
  
//  for motion
  float f;
  float v;
  float dx;
  float dy;
  float ddx;
  float ddy;
  
public:
  double energy; // FFT Band val
  
  Particle( int v, int f );
  ~Particle();
  
  void reset();
  void move();
  void draw();
  ofPoint getPosition();
};