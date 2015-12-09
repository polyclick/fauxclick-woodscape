#pragma once

#include "ofApp.h"
#include "SketchBase.h"
#include "Particle.h"

class BoidSketch : public SketchBase {
  
protected:
  
  const char* name;
  ofApp* app;
  
  vector <Particle*> particles;
  vector <int> particleBands;
  
  float bandValue;
public:
  BoidSketch(ofApp* app, const char* name);
  ~BoidSketch();
  
  void setup();
  void update();
  void draw();
  
  const char* getName();
  void logName();
};