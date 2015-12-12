#pragma once

#include "ofApp.h"
#include "ofxMidi.h"
#include "SketchBase.h"
#include "Grid.h"

class RandomSketch : public SketchBase, public ofxMidiListener {

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
  
  // midi value
  float midiValue = -1.0;
  
public:
  RandomSketch(ofApp* app, const char* name);
  ~RandomSketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();
  
  void newMidiMessage(ofxMidiMessage &msg);

  const char* getName();
  void logName();

};