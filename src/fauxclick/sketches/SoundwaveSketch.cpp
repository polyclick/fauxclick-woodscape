#include "SoundwaveSketch.h"

SoundwaveSketch::SoundwaveSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

SoundwaveSketch::~SoundwaveSketch(){
  // destructor
}

void SoundwaveSketch::setup(){
  
}

void SoundwaveSketch::update(){
  
}

void SoundwaveSketch::draw() {
  ofNoFill();
  
  vector<float>left = this->app->audioManager->left;
  vector<float>right = this->app->audioManager->right;
  
  float pointInterval = (float)ofGetWidth() / (float)left.size();
  
  ofPushStyle();
		ofPushMatrix();
  
  // set color
  ofSetColor(245, 58, 135);
  ofSetLineWidth(3);
  
  // y offset
  ofTranslate(0, ofGetHeight() * 1.0 / 4.0, 0);
  
  // start drawing the line
  ofBeginShape();
  
  // draw over the full width of the screen
  for (unsigned int i = 0; i < left.size(); i++){
    ofVertex(i * pointInterval, left[i] * ofGetHeight() / 4.0);
  }
  
  // end drawing the line
  ofEndShape(false);
		ofPopMatrix();
  ofPopStyle();
  
  ofPushStyle();
		ofPushMatrix();
  
  // set color
  ofSetColor(245, 58, 135);
  ofSetLineWidth(3);
  
  // y offset
  ofTranslate(0, ofGetHeight() * 3.0 / 4.0, 0);
  
  // start drawing the line
  ofBeginShape();
  
  // draw over the full width of the screen
  for (unsigned int i = 0; i < right.size(); i++){
    ofVertex(i * pointInterval, right[i] * ofGetHeight() / 4.0);
  }
  
  // end drawing the line
  ofEndShape(false);
		ofPopMatrix();
  ofPopStyle();
}

const char* SoundwaveSketch::getName() {
  return this->name;
}

void SoundwaveSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}