#include "TriangleSketch.h"

TriangleSketch::TriangleSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

TriangleSketch::~TriangleSketch(){
  // destructor
}

void TriangleSketch::setup() {

}

void TriangleSketch::update() {

}

void TriangleSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
  ofSetColor(0,255,255);
  float radius = 100;
  ofFill();   // draw "filled shapes"
  ofDrawCircle(100,400,radius);
}

const char* TriangleSketch::getName() {
  return this->name;
}

void TriangleSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name);
}