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
//  paths.push_back("images/landscape-01.jpg");
//  paths.push_back("images/landscape-02.jpg");
//  paths.push_back("images/landscape-03.jpg");
//  paths.push_back("images/landscape-04.jpg");
//  paths.push_back("images/landscape-05.jpg");
//  paths.push_back("images/tits.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwabqkSxpo1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwb3bgJt5Q1tuy5mao1_1280.png");
  paths.push_back("images/rs-day-two/tumblr_nwbm7gAVRI1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwefj0YD1v1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwf2fsa1UA1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwfx2w5Vbv1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwh3qy5XdJ1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwksqhB5kU1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwku4kGV8R1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwnp3cQo3D1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwohxrdPRs1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwowe1F3WW1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwp22r4L1X1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nws9fyQmds1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwsye7B9d51tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwyta3nhBL1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytaj9hlm1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytapjXw61tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytb06MlP1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytb9lTRn1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytbqfrDH1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytbqGIGM1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytbsPwKk1tuy5mao1_1280.png");
  paths.push_back("images/rs-day-two/tumblr_nwytcgghnv1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytcyDCna1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytd1tl7o1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytdkcsVP1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytdqw98X1tuy5mao1_1280.jpg");
  paths.push_back("images/rs-day-two/tumblr_nwytdwgfxt1tuy5mao1_1280.jpg");
  
  // load images
  for(int i = 0 ; i < paths.size() ; i++) {
    ofImage image;
    image.load(paths[i]);
    images.push_back(image);
  }

  // set first image
  currentImage = images[0];
}

void VolumeHistorySketch::activate() {
  volumeMidiValue = -1.0;
  this->app->midiManager->midiIn.addListener(this);
}

void VolumeHistorySketch::update(){
  
  // scaling multiplier
  float multiplier = volumeMidiValue < 0.0 ? 1.5 : volumeMidiValue * 3.0;

  // disable glitch effect after the cooldown
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

    float volume = volumeHistory[i] * ofGetHeight() * multiplier;
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

    float volume = volumeHistory[i] * ofGetHeight() * multiplier;
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

void VolumeHistorySketch::deactivate() {
  this->app->midiManager->midiIn.removeListener(this);
}

void VolumeHistorySketch::newMidiMessage(ofxMidiMessage &msg) {
  if(msg.control == 57 && msg.value != volumeMidiValue) {
    volumeMidiValue = ofMap(msg.value, 0, 127, 0, 1);
  }
}

const char* VolumeHistorySketch::getName() {
  return this->name;
}

void VolumeHistorySketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}