#include "EinsteinSketch.h"

EinsteinSketch::EinsteinSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

EinsteinSketch::~EinsteinSketch(){
  // destructor
}

void EinsteinSketch::setup(){

}

void EinsteinSketch::update(){
  if(this->app->audioManager->beatReceived) {
    count++;
    if(count > 16) {
      count = 0;
      symbol++;
      if(symbol > 2)
        symbol = 0;
    }
  }
}

void EinsteinSketch::draw() {
  float width = ofGetWidth() / 3.0;
  float height = ofGetHeight();

  ofFill();
  ofTranslate(15, 15);

  int size = 75;
  int wrapper = ofGetWidth() / 16;
  
  for(int j = 0 ; j < 7 ; j++) {
    for(int i = 0 ; i < 16 ; i++) {
      int centerX = (i * wrapper) + (size / 2.0);
      int centerY = (j * wrapper) + (size / 2.0);
      
      if(i == count) {
        ofSetColor(255, 86, 97, 255);
        if(symbol == 0) {
          ofDrawRectangle(centerX - (size / 2.0), centerY - (size / 2.0), size, size);
        } else if(symbol == 1) {
          ofDrawCircle(centerX, centerY, size / 2.0);
        } else if(symbol == 2) {
          ofDrawTriangle(centerX, centerY - (size / 2.0), centerX - (size / 2.0), centerY + (size / 2.0), centerX + (size / 2.0), centerY + (size / 2.0));
        }
      } else {
        ofSetColor(255, 255, 255, this->app->audioManager->beatReceived ? 100 : 35);
        ofDrawTriangle(centerX, centerY - (size / 2.0), centerX - (size / 2.0), centerY + (size / 2.0), centerX + (size / 2.0), centerY + (size / 2.0));
      }
    }
  }
}

const char* EinsteinSketch::getName() {
  return this->name;
}

void EinsteinSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}