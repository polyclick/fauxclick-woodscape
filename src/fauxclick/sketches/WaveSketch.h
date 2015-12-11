#pragma once

#include "ofApp.h"
#include "SketchBase.h"
#include "Grid.h"
#include "ofxMidi.h"

class WaveSketch : public SketchBase, public ofxMidiListener {

protected:

  const char* name;
  ofApp* app;
  Grid grid;

  // Set unit width
  const int unitWidth = 101;

  // Set unit height
  const int unitHeight = 118;

  // Rows and columns are zero-indexed
  const int rows = 10;
  const int cols = 15;
  
  float rowMidiValue = -1.0;

public:
  WaveSketch(ofApp* app, const char* name);
  ~WaveSketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();
  
  void newMidiMessage(ofxMidiMessage &msg);

  const char* getName();
  void logName();

};