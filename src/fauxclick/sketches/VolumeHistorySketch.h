#pragma once
#include "SketchBase.h"
#include "ofApp.h"
#include "ofxPostGlitch.h"
#include "ofxMidi.h"

class ofApp;

class VolumeHistorySketch : public SketchBase, public ofxMidiListener {

protected:
  const char* name;
  ofApp* app;

public:
  VolumeHistorySketch(ofApp* app, const char* name);
  ~VolumeHistorySketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();
  
  void newMidiMessage(ofxMidiMessage &msg);

  const char* getName();
  void logName();

  vector<float> volumeHistory;
  vector<ofImage> images;

  int volumeHistorySize = 16;
  int beatCounter = 0;
  int onsetCounter = 0;

  uint64_t elaspedSinceLastBeatOnset;

  ofImage currentImage;
  ofFbo myFbo;

  ofxPostGlitch myGlitch;

};