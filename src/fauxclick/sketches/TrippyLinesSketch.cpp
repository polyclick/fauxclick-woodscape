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

void TrippyLinesSketch::activate() {

}

void TrippyLinesSketch::update(){
}

void TrippyLinesSketch::draw() {
  ofPushStyle();
  ofNoFill();

  if(this->app->audioManager->beatReceived) {
    ofSetHexColor(0x20FF9C);
    ofSetLineWidth(10);
    ofSetPolyMode(OF_POLY_WINDING_ODD);
    ofFill();
    ofBeginShape();
    for (int i = 0; i < 5; i++){
      ofVertex(ofRandom(-250, ofGetWidth() + 250), ofRandom(-250, ofGetHeight() + 250));
    }
    ofEndShape();
  }

  if(this->app->audioManager->onsetReceived) {
    ofSetHexColor(0xffffff);
      ofNoFill();
    ofSetLineWidth(10);
    ofSetPolyMode(OF_POLY_WINDING_ODD);
    ofBeginShape();
    for (int i = 0; i < 5; i++){
      ofVertex(ofRandom(-250, ofGetWidth() + 250), ofRandom(-250, ofGetHeight() + 250));
    }
    ofEndShape();
  }

  ofPopStyle();
}

void TrippyLinesSketch::deactivate() {

}

const char* TrippyLinesSketch::getName() {
  return this->name;
}

void TrippyLinesSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}