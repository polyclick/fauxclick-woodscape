#pragma once

#include "ofApp.h"
#include "SketchBase.h"
#include "ofxPostGlitch.h"
#include "ofxMidi.h"

class SoundwaveSketch : public SketchBase, public ofxMidiListener {

private:
  bool showKick = false;
  int randomSide = 0;
  float volumeMidiValue = -1.0;

protected:
  const char* name;
  ofApp* app;

public:
  SoundwaveSketch(ofApp* app, const char* name);
  ~SoundwaveSketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();
  
  void newMidiMessage(ofxMidiMessage &msg);

  const char* getName();
  void logName();
};