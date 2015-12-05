#pragma once

#include "ofMain.h"

#include "fcSketchBase.h"

class fcBarSketch : public fcSketchBase {

  public:
    void setup();
    void update();
    void draw();
    void logName();
    const char* name();
  
};