#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxBeat.h"
#include "ofLog.h"

class SketchBase {

  public:
    virtual const char* name() = 0;

    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw(ofxBeat beat, ofxMidiMessage midi) = 0;

    virtual void logName() = 0;
};