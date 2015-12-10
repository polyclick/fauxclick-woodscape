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
  vector <int> lineFrom;
  vector <int> lineTo;
  int numParticles;
  int numLines;
  float treshold;

  float bandValue;

  void setLines();

public:
  BoidSketch(ofApp* app, const char* name);
  ~BoidSketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();

  const char* getName();
  void logName();

};