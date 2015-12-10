#include "FlashSketch.h"

FlashSketch::FlashSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

FlashSketch::~FlashSketch(){
  // destructor
}

void FlashSketch::setup(){

}

void FlashSketch::activate() {

}

void FlashSketch::update(){

}

void FlashSketch::draw() {
  float width = ofGetWidth() / 3.0;
  float height = ofGetHeight();

  ofFill();
  ofSetColor(255, 255, 255);

  if(this->app->audioManager->beatReceived) {
    ofDrawRectangle(0, 0, width, height);
    ofDrawRectangle(width * 2.0, 0, width, height);
  }

  if(this->app->audioManager->onsetReceived) {
    ofDrawRectangle(width, 0, width, height);
  }
}

void FlashSketch::deactivate() {

}

const char* FlashSketch::getName() {
  return this->name;
}

void FlashSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}