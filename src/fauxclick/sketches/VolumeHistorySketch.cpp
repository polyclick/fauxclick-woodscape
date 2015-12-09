#include "VolumeHistorySketch.h"

#include "ofApp.h"

VolumeHistorySketch::VolumeHistorySketch(ofApp* app, const char* name) {
  this->app = app;
  this->name = name;
}

VolumeHistorySketch::~VolumeHistorySketch(){
  // destructor
}

void VolumeHistorySketch::setup(){
  
  // glitch
  myFbo.allocate(ofGetWidth(), ofGetHeight());
  myGlitch.setup(&myFbo);

  // vector to keep the volume changes
  volumeHistory.assign(volumeHistorySize, 0.0);
  
  // image paths
  vector<const char*> paths;
  paths.push_back("images/landscape-01.jpg");
  paths.push_back("images/landscape-02.jpg");
  paths.push_back("images/landscape-03.jpg");
  paths.push_back("images/landscape-04.jpg");
  paths.push_back("images/landscape-05.jpg");
  //paths.push_back("images/tits.jpg");
  
  // load images
  for(int i = 0 ; i < paths.size() ; i++) {
    ofImage image;
    image.load(paths[i]);
    images.push_back(image);
  }
  
  // set first image
  currentImage = images[0];
}

void VolumeHistorySketch::update(){
  if(ofGetElapsedTimeMillis() - elaspedSinceLastBeatOnset > 50) {
    myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
    myGlitch.setFx(OFXPOSTGLITCH_INVERT, false);
  }

  // lets record the volume into an array
  volumeHistory.push_back(this->app->audioManager->normalizedVolume);

  // if we are bigger the the size we want to record - lets drop the oldest value
  if(volumeHistory.size() >= volumeHistorySize){
    volumeHistory.erase(volumeHistory.begin(), volumeHistory.begin() + 1);
  }

  // onset detected, pick random image
  if(this->app->audioManager->onsetReceived) {
    onsetCounter++;
    if(onsetCounter == 3) {
      onsetCounter = 0;
      cout << "change" << endl;
      int randomIndex = rand() % images.size();
      currentImage = images[randomIndex];
    }
  }
  
  // kick detected
  if(this->app->audioManager->beatReceived) {
    beatCounter++;
    if(beatCounter == 1) {
      beatCounter = 0;
      myGlitch.setFx(ofRandom(1.0) > 0.5 ? OFXPOSTGLITCH_CUTSLIDER : OFXPOSTGLITCH_INVERT, true);
      elaspedSinceLastBeatOnset = ofGetElapsedTimeMillis();
    }
  }
  
  // draw to fbo
  myFbo.begin();
  ofClear(0, 0, 0, 255);
  
  // push
  ofPushStyle();
  ofPushMatrix();
  
  // draw bg image
  int imgWidth = ofGetWidth();
  int imgHeight = currentImage.getHeight() * ofGetWidth() / currentImage.getWidth();
  currentImage.draw((ofGetWidth() - imgWidth) / 2.0, (ofGetHeight() - imgHeight) / 2.0, imgWidth, imgHeight);
  
  // scaling in width of screen
  float widthRatio = (float)ofGetWidth() / ((float)volumeHistory.size() - 1);
  
  // set color
  ofFill();
  ofSetColor(0);
  
  // top graph
  ofBeginShape();
  for (unsigned int i = 0; i < volumeHistory.size(); i++) {
    if(i == 0)
      ofVertex(0, 0);
    
    float volume = volumeHistory[i] * ofGetHeight() * 1.5;
    ofVertex(i * widthRatio, volume);
    
    if(i == volumeHistory.size() - 1)
      ofVertex(i * widthRatio, 0);
  }
  ofEndShape(true);
  
  // bottom graph
  ofBeginShape();
  for (unsigned int i = 0; i < volumeHistory.size(); i++) {
    if(i == 0)
      ofVertex(0, ofGetHeight());
    
    float volume = volumeHistory[i] * ofGetHeight() * 1.5;
    ofVertex(i * widthRatio, ofGetHeight() - volume);
    
    if(i == volumeHistory.size() - 1)
      ofVertex(i * widthRatio, ofGetHeight());
  }
  ofEndShape(true);
  
  // pop em
  ofPopMatrix();
  ofPopStyle();
  
  // end drawing to fbo
  myFbo.end();
}

void VolumeHistorySketch::draw() {
  myGlitch.generateFx();
  myFbo.draw(0, 0);
}

const char* VolumeHistorySketch::getName() {
  return this->name;
}

void VolumeHistorySketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}