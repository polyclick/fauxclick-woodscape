#pragma once

class fcSketchBase {

  public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void logName() = 0;
    virtual const char* name() = 0;
};