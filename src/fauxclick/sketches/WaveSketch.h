#pragma once

#include "ofApp.h"
#include "SketchBase.h"
#include "Grid.h"

class WaveSketch : public SketchBase {

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

public:
  WaveSketch(ofApp* app, const char* name);
  ~WaveSketch();

  void setup();
  void activate();
  void update();
  void draw();
  void deactivate();

  const char* getName();
  void logName();

};