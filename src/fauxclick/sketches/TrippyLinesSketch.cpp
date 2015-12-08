#include "TrippyLinesSketch.h"

TrippyLinesSketch::TrippyLinesSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

TrippyLinesSketch::~TrippyLinesSketch(){
  // destructor
}

void TrippyLinesSketch::setup(){

}

void TrippyLinesSketch::update(){
}

void TrippyLinesSketch::draw() {
  ofPushStyle();

  ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
  ofNoFill();

  ofSetHexColor(0xffffff);
  ofSetLineWidth(1);
  ofSetPolyMode(OF_POLY_WINDING_ODD);
  ofBeginShape();
  int kickPoints = this->app->audioManager->beatReceived ? 10 : 3;
  for (int i = 0; i < kickPoints; i++){
    ofVertex(ofRandom(-250, ofGetWidth() + 250), ofRandom(-250, ofGetHeight() + 250));
  }
  ofEndShape();

  if(this->app->audioManager->onsetReceived) {
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

  ofPopStyle();
}

const char* TrippyLinesSketch::getName() {
  return this->name;
}

void TrippyLinesSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}