#pragma once

#include <string>

#include "fcSketchBase.h"

class fcTriangleSketch : public fcSketchBase {

  public:
    void setup();
    void update();
    void draw();
    void logName();
  
};