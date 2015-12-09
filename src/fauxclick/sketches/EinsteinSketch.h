#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class EinsteinSketch : public SketchBase {

protected:
  const char* name;
  ofApp* app;

public:
  EinsteinSketch(ofApp* app, const char* name);
  ~EinsteinSketch();

  void setup();
  void update();
  void draw();

  const char* getName();
  void logName();
  
  int count = 0;
  int symbol = 0;
};