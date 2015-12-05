#include "SoundwaveSketch.h"

SoundwaveSketch::SoundwaveSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

SoundwaveSketch::~SoundwaveSketch(){
  // destructor
}

void SoundwaveSketch::setup(){
  audio.assign(this->app->bufferSize, 0.0);
}

void SoundwaveSketch::update(ofxBeat beat){
  
}

void SoundwaveSketch::draw() {
  if(!audio.size()) return;
  ofNoFill();

  ofPushStyle();
		ofPushMatrix();

      // set color
      ofSetColor(245, 58, 135);
      ofSetLineWidth(3);
  
      // y offset
      ofTranslate(0, ofGetHeight() / 2.0, 0);
  
      // start drawing the line
      ofBeginShape();
  
      // draw over the full width of the screen
      float pointSize = (float)ofGetWidth() / (float)audio.size();
      for (unsigned int i = 0; i < audio.size(); i++){
        ofVertex(i * pointSize, audio[i] * ofGetHeight() / 4.0);
      }
  
      // end drawing the line
      ofEndShape(false);
		ofPopMatrix();
  ofPopStyle();
}

void SoundwaveSketch::audioReceived(float* input, int bufferSize, int nChannels) {
  for (int i = 0; i < bufferSize; i++){
    audio[i] = input[i];
  }
}

const char* SoundwaveSketch::getName() {
  return this->name;
}

void SoundwaveSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name);
}