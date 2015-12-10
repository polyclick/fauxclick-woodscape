#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class TrippyLinesSketch : public SketchBase {

protected:
  const char* name;
  ofApp* app;

public:
  TrippyLinesSketch(ofApp* app, const char* name);
  ~TrippyLinesSketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();

  const char* getName();
  void logName();
};