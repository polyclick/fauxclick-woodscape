#pragma once

#include "ofApp.h"
#include "ofxMidi.h"
#include "SketchBase.h"
#include "Grid.h"

class GraterSketch : public SketchBase, public ofxMidiListener {

protected:

  const char* name;
  ofApp* app;
  
  Grid grid;
  
  ofMesh mesh;
  
  // midi value
  float midiValue = -1.0;
  
public:
  GraterSketch(ofApp* app, const char* name);
  ~GraterSketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();
  
  void newMidiMessage(ofxMidiMessage &msg);

  const char* getName();
  void logName();

};