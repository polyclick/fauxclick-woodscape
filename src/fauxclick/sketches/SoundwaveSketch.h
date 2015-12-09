#pragma once

#include "ofApp.h"
#include "SketchBase.h"
#include "ofxPostGlitch.h"

class SoundwaveSketch : public SketchBase {

private:
  bool showKick = false;
  int randomSide = 0;


protected:
  const char* name;
  ofApp* app;

public:
  SoundwaveSketch(ofApp* app, const char* name);
  ~SoundwaveSketch();

  void setup();
  void update();
  void draw();

  const char* getName();
  void logName();
};