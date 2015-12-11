#pragma once
#include "ofxMidi.h"
#include "ofxDatGui.h"

class ofApp;

class MidiManager : public ofxMidiListener {

private:
  ofApp *app;

public:
  MidiManager(ofApp* app);
  ~MidiManager();

  void setup();
  void update();
  void newMidiMessage(ofxMidiMessage& msg);
  
  ofxMidiIn midiIn;
  
  ofxMidiMessage midiMessage;

  ofxDatGuiLabel* statusLabel;
  ofxDatGuiLabel* channelLabel;
  ofxDatGuiLabel* controlLabel;
  ofxDatGuiLabel* pitchLabel;
  ofxDatGuiSlider* velocitySlider;
  ofxDatGuiSlider* valueSlider;
  ofxDatGuiLabel* deltaLabel;
  ofxDatGuiFolder* midiFolder;
};