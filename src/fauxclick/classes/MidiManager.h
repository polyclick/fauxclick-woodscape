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
  void newMidiMessage(ofxMidiMessage& eventArgs);

  ofxMidiIn midiIn;
  ofxMidiMessage midiMessage;

  ofxDatGuiLabel* statusLabel;
  ofxDatGuiLabel* channelLabel;
  ofxDatGuiSlider* pitchSlider;
  ofxDatGuiSlider* velocitySlider;
  ofxDatGuiSlider* controlSlider;
  ofxDatGuiSlider* valueSlider;
  ofxDatGuiLabel* deltaLabel;
  ofxDatGuiFolder* midiFolder;
};