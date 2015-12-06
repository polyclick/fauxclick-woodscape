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

void TriangleNoiseSketch::draw() {
  ofNoFill();
  
  ofSetHexColor(0xffffff);
  ofSetLineWidth(1);
  ofSetPolyMode(OF_POLY_WINDING_ODD);
  ofBeginShape();
  int kickPoints = this->app->audioManager->beat.kick() ? 10 : 3;
  for (int i = 0; i < kickPoints; i++){
    ofVertex(ofRandom(-250, ofGetWidth() + 250), ofRandom(-250, ofGetHeight() + 250));
  }
  ofEndShape();
  
  if(this->app->audioManager->beat.hihat()) {
    ofSetHexColor(0x00ff00);
    ofSetLineWidth(3);
    ofSetPolyMode(OF_POLY_WINDING_ODD);
    ofBeginShape();
    int hatPoints = 5;
    for (int i = 0; i < hatPoints; i++){
      ofVertex(ofRandom(-250, ofGetWidth() + 250), ofRandom(-250, ofGetHeight() + 250));
    }
    ofEndShape();
  }
}

const char* TriangleNoiseSketch::getName() {
  return this->name;
}

void TriangleNoiseSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}