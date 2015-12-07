#pragma once
#include "SketchBase.h"
#include "ofApp.h"

class ofApp;

class VolumeHistorySketch : public SketchBase {

protected:
  const char* name;
  ofApp* app;

public:
  VolumeHistorySketch(ofApp* app, const char* name);
  ~VolumeHistorySketch();

  void setup();
  void update();
  void draw();

  
  const char* getName();
  void logName();
  
  vector<float> volumeHistory;
  
  int volumeHistorySize = 500;
};