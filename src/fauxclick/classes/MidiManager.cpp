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
  midiIn.ignoreTypes(true, true, true);  // sysex, timing, active sense
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

//--------------------------------------------------------------
void MidiManager::newMidiMessage(ofxMidiMessage& msg) {

//  // make a copy of the latest message
//  midiMessage = msg;
//
//  // show in debug
//  statusLabel->setLabel(ofxMidiMessage::getStatusString(midiMessage.status));
//  channelLabel->setLabel(ofToString(midiMessage.channel));
//  pitchSlider->setValue(midiMessage.pitch);
//  velocitySlider->setValue(midiMessage.velocity);
//  controlSlider->setValue(midiMessage.control);
//
//  if(midiMessage.status == MIDI_PITCH_BEND) {
//    valueSlider->setLabel(ofToString(ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, 100)));
//  } else {
//    valueSlider->setLabel(ofToString(ofMap(midiMessage.value, 0, 127, 0, 100)));
//  }
//
//  deltaLabel->setLabel(ofToString(midiMessage.deltatime));
}