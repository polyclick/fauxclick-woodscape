#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class PointCloudSketch : public SketchBase {

  protected:
    const char* name;
    ofApp* app;

  public:
    PointCloudSketch(ofApp* app, const char* name);
    ~PointCloudSketch();

    void setup();
    void update();
    void draw();

    const char* getName();
    void logName();
};