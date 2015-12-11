#include "MidiManager.h"

#include "ofApp.h"

MidiManager::MidiManager(ofApp* app){
  this->app = app;
}

MidiManager::~MidiManager(){
  midiIn.closePort();
  midiIn.removeListener(this);
}

void MidiManager::setup(){

  // setup midi
  midiIn.listPorts();
  //midiIn.openPort("Ableton Push User Port");
  midiIn.openPort("TR-8");
  //midiIn.openPort("VMPK Output");
  midiIn.ignoreTypes(false, false, false);  // sysex, timing, active sense
  midiIn.addListener(this);
  midiIn.setVerbose(true);

  // setup gui
  statusLabel = new ofxDatGuiLabel("");
  channelLabel = new ofxDatGuiLabel("");
  pitchSlider = new ofxDatGuiSlider("pitch", 0, 127, 0);
  velocitySlider = new ofxDatGuiSlider("velocity", 0, 127, 0);
  controlSlider = new ofxDatGuiSlider("control", 0, 127, 0);
  valueSlider = new ofxDatGuiSlider("value", 0, 100, 0);
  deltaLabel = new ofxDatGuiLabel("");

  // display folder
  midiFolder = new ofxDatGuiFolder("midi", ofColor::fromHex(0xFFD00B));
  midiFolder->attachItem(statusLabel);
  midiFolder->attachItem(channelLabel);
  midiFolder->attachItem(pitchSlider);
  midiFolder->attachItem(velocitySlider);
  midiFolder->attachItem(controlSlider);
  midiFolder->attachItem(valueSlider);
  midiFolder->attachItem(deltaLabel);

  // add folder
  this->app->parameterWindow->addFolder(midiFolder, 350, 0);
}

void MidiManager::update() {
//  
//  // update debug
//  statusLabel->setLabel(ofxMidiMessage::getStatusString(midiMessage.status));
//  channelLabel->setLabel(ofToString(midiMessage.channel));
//  pitchSlider->setValue(midiMessage.pitch);
//  velocitySlider->setValue(midiMessage.velocity);
//  controlSlider->setValue(midiMessage.control);
//  
//  // pitch bend
//  if(midiMessage.status == MIDI_PITCH_BEND) {
//    valueSlider->setLabel(ofToString(ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, 100)));
//  } else {
//    valueSlider->setLabel(ofToString(ofMap(midiMessage.value, 0, 127, 0, 100)));
//  }
//  
//  // delta
//  deltaLabel->setLabel(ofToString(midiMessage.deltatime));
}

//--------------------------------------------------------------
void MidiManager::newMidiMessage(ofxMidiMessage& msg) {
  
  // make a copy of the latest message
  midiMessage = msg;
  
  // show in debug
  cout << "Status: " << ofxMidiMessage::getStatusString(midiMessage.status) << endl;
  cout << "Channel: " << ofToString(midiMessage.channel) << endl;
  cout << "Pitch: " << midiMessage.pitch << endl;
  cout << "Velocity: " << midiMessage.velocity << endl;
  cout << "Control: " << midiMessage.control << endl;
  cout << "Delta:" << ofToString(midiMessage.deltatime) << endl;
  
  if(midiMessage.status == MIDI_PITCH_BEND) {
    cout << "Pitch bend: " << ofToString(ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, 100)) << endl;
  } else {
    cout << "Value: " << ofToString(ofMap(midiMessage.value, 0, 127, 0, 100)) << endl;
  }
  
  switch (midiMessage.pitch) {
    case 50:
      this->app->sketchManager->activateSketch("WaveSketch");
      break;
      
    case 51:
      this->app->sketchManager->activateSketch("PulseSketch");
      break;
      
    case 52:
      this->app->sketchManager->activateSketch("TrippyLinesSketch");
      break;
      
    case 53:
      this->app->sketchManager->activateSketch("SoundwaveSketch");
      break;
      
    case 54:
      this->app->sketchManager->activateSketch("FlashSketch");
      break;
      
    case 55:
      this->app->sketchManager->activateSketch("VolumeHistorySketch");
      break;
      
    case 56:
      this->app->sketchManager->activateSketch("CubeSketch");
      break;
      
    case 57:
      this->app->sketchManager->activateSketch("BoidSketch");
      break;
      
    case 58:
      this->app->sketchManager->activateSketch("EinsteinSketch");
      break;
  }
}