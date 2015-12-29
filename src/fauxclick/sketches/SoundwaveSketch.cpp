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

void SoundwaveSketch::activate() {
  volumeMidiValue = -1.0;
  this->app->midiManager->midiIn.addListener(this);
}

void SoundwaveSketch::update(){
  this->showKick = false;
  if(this->app->audioManager->beatReceived) {
    this->showKick = true;
    this->randomSide = ofRandom(1) < 0.5 ? 0 : 1;
  }
}

void SoundwaveSketch::draw() {

  // shortcut
  vector<float>left = this->app->audioManager->left;
  vector<float>right = this->app->audioManager->right;

  // scaling in width of screen
  float widthRatio = (float)ofGetWidth() / ((float)left.size() - 1);

  // vars
  int lineColor = 255;
  float multiplier = volumeMidiValue < 0.0 ? 2.5 : volumeMidiValue * 5.0;

  // -------------------------------------- left channel
  ofPushStyle();
  ofPushMatrix();

  // draw bg
  if(showKick && randomSide == 0) {
    ofFill();
    ofSetColor(255);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight() / 2.0);
  }

  // vars
  lineColor = showKick && randomSide == 0 ? 0 : 255;

  // set color
  ofNoFill();
  ofSetColor(lineColor);
  ofSetLineWidth(10);

  // y offset
  ofTranslate(0, ofGetHeight() * 1.25 / 4.0, 0);

  // start drawing the line
  ofBeginShape();

  // draw over the full width of the screen
  for (unsigned int i = 0; i < left.size(); i++){
    ofVertex(i * widthRatio, left[i] * ofGetHeight() * multiplier);
  }

  // end drawing the line
  ofEndShape(false);

  ofPopMatrix();
  ofPopStyle();



  // -------------------------------------- right channel
  ofPushStyle();
  ofPushMatrix();

  // draw bg
  if(showKick && randomSide == 1) {
    ofFill();
    ofSetColor(255);
    ofDrawRectangle(0, ofGetHeight() / 2.0, ofGetWidth(), ofGetHeight() / 2.0);
  }

  // vars
  lineColor = showKick && randomSide == 1 ? 0 : 255;

  // set color
  ofNoFill();
  ofSetColor(lineColor);
  ofSetLineWidth(10);

  // y offset
  ofTranslate(0, ofGetHeight() * 2.75 / 4.0, 0);

  // start drawing the line
  ofBeginShape();

  // draw over the full width of the screen
  for (unsigned int i = 0; i < right.size(); i++){
    ofVertex(i * widthRatio, right[i] * ofGetHeight() * multiplier);
  }

  // end drawing the line
  ofEndShape(false);

  ofPopMatrix();
  ofPopStyle();
}

void SoundwaveSketch::deactivate() {
  this->app->midiManager->midiIn.removeListener(this);
}

void SoundwaveSketch::newMidiMessage(ofxMidiMessage &msg) {
//  if(msg.control == 54 && msg.value != volumeMidiValue) {
//    volumeMidiValue = ofMap(msg.value, 0, 127, 0, 1);
//  }
}

const char* SoundwaveSketch::getName() {
  return this->name;
}

void SoundwaveSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}