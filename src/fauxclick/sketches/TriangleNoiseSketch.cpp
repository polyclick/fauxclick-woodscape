#include "TriangleNoiseSketch.h"

TriangleNoiseSketch::TriangleNoiseSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

TriangleNoiseSketch::~TriangleNoiseSketch(){
  // destructor
}

void TriangleNoiseSketch::setup(){

}

void TriangleNoiseSketch::update(){

}

void TriangleNoiseSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
  ofSetHexColor(0xffffff);
  ofSetPolyMode(OF_POLY_WINDING_ODD);
  ofBeginShape();
  int kickPoints = beat.kick() ? 10 : 3;
  for (int i = 0; i < kickPoints; i++){
    ofVertex(ofRandom(-250, ofGetWidth() + 250), ofRandom(-250, ofGetHeight() + 250));
  }
  ofEndShape();

  ofSetHexColor(0x00ff00);
  ofSetPolyMode(OF_POLY_WINDING_ODD);
  ofBeginShape();
  int hatPoints = beat.hihat() ? 5 : 0;
  for (int i = 0; i < hatPoints; i++){
    ofVertex(ofRandom(-250, ofGetWidth() + 250), ofRandom(-250, ofGetHeight() + 250));
  }
  ofEndShape();
}

const char* TriangleNoiseSketch::getName() {
  return this->name;
}

void TriangleNoiseSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name);
}