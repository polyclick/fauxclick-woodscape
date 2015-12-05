#include "SoundwaveSketch.h"

SoundwaveSketch::SoundwaveSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

SoundwaveSketch::~SoundwaveSketch(){
  // destructor
}

void SoundwaveSketch::setup(){
  left.assign(this->app->bufferSize, 0.0);
}

void SoundwaveSketch::update(){

}

void SoundwaveSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
//  ofPushStyle();
//		ofPushMatrix();
//		ofTranslate(32, 170, 0);
//  
//		ofSetColor(225);
//		ofDrawBitmapString("Left Channel", 4, 18);
//		
//		ofSetLineWidth(1);
//		ofDrawRectangle(0, 0, 512, 200);
//  
//		ofSetColor(245, 58, 135);
//		ofSetLineWidth(3);
//  
//  ofBeginShape();
//  for (unsigned int i = 0; i < left.size(); i++){
//				ofVertex(i*2, 100 -left[i]*180.0f);
//  }
//  ofEndShape(false);
//  
//		ofPopMatrix();
//  ofPopStyle();
}

const char* SoundwaveSketch::getName() {
  return this->name;
}

void SoundwaveSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name);
}