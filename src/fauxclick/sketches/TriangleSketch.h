#pragma once

#include "SketchBase.h"

class TriangleSketch : public SketchBase {

  public:
    const char* name();

    void setup();
    void update();
    void draw(ofxBeat beat, ofxMidiMessage midi);

    void logName();
};