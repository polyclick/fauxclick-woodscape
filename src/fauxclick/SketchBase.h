#pragma once

class SketchBase {

  public:
    virtual void setup() = 0;
    virtual void activate() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void deactivate() = 0;

    virtual const char* getName() = 0;
    virtual void logName() = 0;

};