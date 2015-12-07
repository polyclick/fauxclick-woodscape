#pragma once

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxDatGui.h"

class ofApp;

class AudioManager : public ofBaseSoundInput, public ofBaseSoundOutput {

private:
  ofApp *app;

public:
  AudioManager(ofApp* app);
  ~AudioManager();
  
  void setup();
  bool setupAudioDeviceByName(string name);
  void setupAudioDeviceByID(unsigned int id);
  void setupGui();
  void update();

  void audioReceived(float* input, int bufferSize, int nChannels);
  void onDropdownEvent(ofxDatGuiDropdownEvent e);
  
  vector<ofSoundDevice> deviceList;
  
	vector<float> left;               // left channel frequencies
	vector<float> right;              // right channel frequencies
  vector<float> volumeHistory;      // volume history
  
  bool beatReceived = false;
  bool onsetReceived = false;
  
  int sampleRate = 44100;
  int bufferSize = 256;
  int nBuffers = 4;
  int volumeHistorySize = 400;      // amount of volume measurements to keep in our history vector
  
  float smoothedVolume;             // volume with some smoothing applied between measurements
  float normalizedVolume;           // volume normalized (0 - 1)
  
  ofSoundStream soundStream;
  
  ofxAubioOnset onset;
  ofxAubioPitch pitch;
  ofxAubioBeat beat;
  ofxAubioMelBands bands;
  
  ofxDatGuiFolder* audioFolder;
  ofxDatGuiDropdown* audioDropdown;
  ofxDatGuiValuePlotter* kickValuePlotter;
  ofxDatGuiValuePlotter* onsetValuePlotter;
};