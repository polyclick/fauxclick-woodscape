#pragma once

#include "ofApp.h"

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