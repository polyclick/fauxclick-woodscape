#pragma once

#include "ofApp.h"

class ofApp;

class ClassName {

private:
  ofApp *app;

public:
  ClassName(ofApp* app);
  ~ClassName();

  void setup();
  void update();
  void draw();

};