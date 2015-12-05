#pragma once

#include "fcSketchBase.h"

class fcTriangleNoiseSketch : public fcSketchBase {

  public:
    const char* name();

    void setup();
    void update();
    void draw(ofxBeat beat, ofxMidiMessage midi);

    void logName();
};