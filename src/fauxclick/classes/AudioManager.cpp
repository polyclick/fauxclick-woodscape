#include "AudioManager.h"

#include "ofApp.h"

AudioManager::AudioManager(ofApp* app){
  this->app = app;
}

AudioManager::~AudioManager(){
  // destructor
}

void AudioManager::setup(){
  
  // sound settings
  sampleRate = 44100;
  bufferSize = 256;
  nBuffers = 4;
  
  
  
  // setup beat object
  beat.setup();
  
  // setup onset object
  onset.setup();
  
  // setup pitch object
  pitch.setup();
  
  // setup mel bands object
  bands.setup();
  
  
  
  // init left and right channel vectors
  left.assign(bufferSize, 0.0);
  right.assign(bufferSize, 0.0);
  
  // vector to keep the volume changes
  volumeHistory.assign(volumeHistorySize, 0.0);
  
  // smoothed and scaled volume
  smoothedVolume = 0.0;
  normalizedVolume = 0.0;
  
  
  
  // log a list of all available devices
  soundStream.printDeviceList();
  
  // cache list
  deviceList = soundStream.getDeviceList();

  // try to setup audio a10 as default
  // else fallback to first device in list
  bool hasSetupA10 = this->setupAudioDeviceByName("Native Instruments: Traktor Audio 10");
  if(!hasSetupA10) {
    bool hasSetupAkai = this->setupAudioDeviceByName("Akai Professional, LP: EIE pro (Core Audio)");
    if(!hasSetupAkai) {
      cout << "Falling back to device 0" << endl;
      this->setupAudioDeviceByID(0);
    }
  }
  
  
  
  // setup the parameter gui
  this->setupGui();
}

//--------------------------------------------------------------
bool AudioManager::setupAudioDeviceByName(string name) {
  vector<ofSoundDevice> matches = soundStream.getMatchingDevices(name);
  if(matches.size() == 1) {
    this->setupAudioDeviceByID(matches[0].deviceID);
    return true;
  }
  
  cout << "No matching audio device with name: " << name << endl;
  return false;
}

//--------------------------------------------------------------
void AudioManager::setupAudioDeviceByID(unsigned int id) {
  soundStream.stop();
  soundStream.close();
  soundStream.setDeviceID(id);
  soundStream.setInput(this);
  soundStream.setup(0, 2, sampleRate, bufferSize, nBuffers);
}

//--------------------------------------------------------------
void AudioManager::setupGui() {
  
  // list of audio device options for dropdown
  vector<string> options;
  for(int i = 0; i < deviceList.size(); i++) {
    options.push_back(deviceList[i].name);
    cout << deviceList[i].name << endl;
  }
  
  // audio devices dropdown
  audioDropdown = new ofxDatGuiDropdown("AUDIO DEVICES", options);
  audioDropdown->onDropdownEvent(this, &AudioManager::onDropdownEvent);
  
  // beat, onset plotters
  kickValuePlotter = new ofxDatGuiValuePlotter("KICK", 0, 100);
  kickValuePlotter->setSpeed(2.0);
  onsetValuePlotter = new ofxDatGuiValuePlotter("ONSET", 0, 100);
  onsetValuePlotter->setSpeed(2.0);
  
  // audio folder
  audioFolder = new ofxDatGuiFolder("audio", ofColor::fromHex(0x1ED36F));
  audioFolder->attachItem(kickValuePlotter);
  audioFolder->attachItem(onsetValuePlotter);
  audioFolder->attachItem(audioDropdown);
  
  // add to parameter window
  this->app->parameterWindow->addFolder(audioFolder, 0, 200);
}

//--------------------------------------------------------------
void AudioManager::update(){
  
  // lets scale the vol up to a 0-1 range
  normalizedVolume = ofMap(smoothedVolume, 0.0, 0.17, 0.0, 1.0, true);
  
  // lets record the volume into an array
  volumeHistory.push_back(normalizedVolume);
  
  // if we are bigger the the size we want to record - lets drop the oldest value
  if(volumeHistory.size() >= volumeHistorySize){
    volumeHistory.erase(volumeHistory.begin(), volumeHistory.begin() + 1);
  }
  
  // cache beat/onset received yes/no
  beatReceived = beat.received();
  onsetReceived = onset.received();
  
  // update parameter screen
  kickValuePlotter->setValue(beatReceived ? 100.0 : 0.0);
  onsetValuePlotter->setValue(onsetReceived ? 100.0 : 0.0);
}

//--------------------------------------------------------------
void AudioManager::audioReceived(float* input, int bufferSize, int nChannels) {
  
  // compute beat location
  beat.audioIn(input, bufferSize, nChannels);
  
  // compute onset detection
  onset.audioIn(input, bufferSize, nChannels);
  
  // compute pitch detection
  pitch.audioIn(input, bufferSize, nChannels);

  // compute bands
  bands.audioIn(input, bufferSize, nChannels);
  
  // do our own analysis
  float currentVolume = 0.0;
  
  // samples are "interleaved"
  int numCounted = 0;
  
  //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
  for (int i = 0; i < bufferSize; i++) {
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
  
  // smoothed volume
  smoothedVolume *= 0.93;
  smoothedVolume += 0.07 * currentVolume;
}

//--------------------------------------------------------------
void AudioManager::onDropdownEvent(ofxDatGuiDropdownEvent e) {
  this->setupAudioDeviceByName(deviceList[e.child].name);
}
