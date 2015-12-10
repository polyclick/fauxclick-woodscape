#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class FlashSketch : public SketchBase {

protected:
  const char* name;
  ofApp* app;

public:
  FlashSketch(ofApp* app, const char* name);
  ~FlashSketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();

  const char* getName();
  void logName();

};