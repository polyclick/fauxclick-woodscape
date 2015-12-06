#pragma once

#include "ofMain.h"
#include "ofxBeat.h"

class ofApp;

class AudioManager : public ofBaseSoundInput, public ofBaseSoundOutput {

private:
  ofApp *app;

public:
  AudioManager(ofApp* app);
  ~AudioManager();
  
  void setup();
  void update();

  void audioReceived(float* input, int bufferSize, int nChannels);
  
	vector <float> left;            // left channel frequencies
	vector <float> right;           // right channel frequencies
  vector <float> volumeHistory;   // volume history
  
  int bufferSize;
  int volumeHistorySize = 400;    // amount of volume measurements to keep in our history vector
  
  float smoothedVolume;           // volume with some smoothing applied between measurements
  float normalizedVolume;         // volume normalized (0 - 1)
  
  ofSoundStream soundStream;
  ofxBeat beat;
};