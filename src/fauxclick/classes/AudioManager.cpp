#include "AudioManager.h"

#include "ofApp.h"

AudioManager::AudioManager(ofApp* app){
  this->app = app;
}

AudioManager::~AudioManager(){
  // destructor
}

void AudioManager::setup(){
  soundStream.printDeviceList();
  
  // first try to get akai device
  vector<ofSoundDevice> matches = soundStream.getMatchingDevices("Akai Professional, LP: EIE pro (Core Audio)");
  
  // else try traktor a10
  if(!matches.size())
    matches = soundStream.getMatchingDevices("Akai Professional, LP: EIE pro (Core Audio)");
  
  // if akai or traktor found, set as main
  // this will automatically fallback to microphone audio if none of both was found
  if(matches.size())
    soundStream.setDevice(matches[0]);
  
  // buffer size
  //bufferSize = beat.getBufferSize();
  bufferSize = 512;
  
  // init left and right channel vectors
  left.assign(bufferSize, 0.0);
  right.assign(bufferSize, 0.0);
  
  // vector to keep the volume changes
  volumeHistory.assign(volumeHistorySize, 0.0);
  
  // smoothed and scaled volume
  smoothedVolume = 0.0;
  normalizedVolume = 0.0;
  
  // setup the soundstream
  soundStream.setup(0, 2, 44100, bufferSize, 4);
  soundStream.setInput(this);
}

void AudioManager::update(){
  
  // update beat detector
  beat.update(ofGetElapsedTimeMillis());
  
  // lets scale the vol up to a 0-1 range
  normalizedVolume = ofMap(smoothedVolume, 0.0, 0.17, 0.0, 1.0, true);
  
  // lets record the volume into an array
  volumeHistory.push_back(normalizedVolume);
  
  // if we are bigger the the size we want to record - lets drop the oldest value
  if(volumeHistory.size() >= volumeHistorySize){
    volumeHistory.erase(volumeHistory.begin(), volumeHistory.begin() + 1);
  }
  
  // update parameter screen
  this->app->parameterWindow->kickValuePlotter->setValue(beat.kick() * 100.0);
  this->app->parameterWindow->snareValuePlotter->setValue(beat.snare() * 100.0);
  this->app->parameterWindow->hihatValuePlotter->setValue(beat.hihat() * 100.0);
}

//--------------------------------------------------------------
void AudioManager::audioReceived(float* input, int bufferSize, int nChannels) {
  
  // feed audio to beat detector
  beat.audioReceived(input, bufferSize, nChannels);
  
  // do our own analysis
  float currentVolume = 0.0;
  
  // samples are "interleaved"
  int numCounted = 0;
  
  //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
  for (int i = 0; i < bufferSize; i++){
    left[i] = input[i * 2] * 0.5;
    right[i] = input[i * 2 + 1] * 0.5;
    
    currentVolume += left[i] * left[i];
    currentVolume += right[i] * right[i];
    numCounted += 2;
  }
  
  //this is how we get the mean of rms :)
  currentVolume /= (float)numCounted;
  
  // this is how we get the root of rms :)
  currentVolume = sqrt(currentVolume);
  
  smoothedVolume *= 0.93;
  smoothedVolume += 0.07 * currentVolume;
}