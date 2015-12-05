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

void TriangleSketch::update(ofxBeat beat) {

}

void TriangleSketch::draw() {
  ofSetColor(0,255,255);
  float radius = 100;
  ofFill();   // draw "filled shapes"
  ofDrawCircle(100,400,radius);
}

void TriangleSketch::audioReceived(float* input, int bufferSize, int nChannels) {
  // audio received, do something with input
}

const char* TriangleSketch::getName() {
  return this->name;
}

void TriangleSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name);
}