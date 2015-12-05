#pragma once

#include "fcSketchBase.h"

class fcBlobSketch : public fcSketchBase {

  public:
    const char* name();

    void setup();
    void update();
    void draw(ofxBeat beat, ofxMidiMessage midi);

    void logName();
};