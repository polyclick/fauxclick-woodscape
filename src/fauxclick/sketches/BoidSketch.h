#pragma once

#include "ofApp.h"
#include "ofxMidi.h"
#include "SketchBase.h"
#include "Particle.h"

class BoidSketch : public SketchBase, public ofxMidiListener {

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
  float faderMidiValue = -1.0;
  

  void setLines();

public:
  BoidSketch(ofApp* app, const char* name);
  ~BoidSketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();
  
  void newMidiMessage(ofxMidiMessage &msg);

  const char* getName();
  void logName();

};