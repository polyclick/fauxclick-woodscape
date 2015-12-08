#pragma once
#include <vector>
#include "SketchBase.h"

using namespace std;

class ofApp;

class SketchManager {

private:
  ofApp *app;

public:
  SketchManager(ofApp* app);
  ~SketchManager();

  void setup();
  void update();
  void draw();

  void activateSketch(const char* sketchName);

  int activeSketchIndex;
  vector<SketchBase*> sketches;
};