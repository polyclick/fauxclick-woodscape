#pragma once

#include "ofxDatGui.h"

class ofApp;

class ParameterWindow {

private:
  ofApp *app;
  
public:
  ParameterWindow(ofApp* app);
  ~ParameterWindow();
  
  vector<ofSoundDevice> audioDeviceList;
  
  ofSoundStream soundStream;
  
  ofxDatGuiButton* vSyncToggle;
  ofxDatGuiButton* smoothingToggle;
  ofxDatGuiDropdown* audioDropdown;
  ofxDatGuiValuePlotter* kickValuePlotter;
  ofxDatGuiValuePlotter* snareValuePlotter;
  ofxDatGuiValuePlotter* hihatValuePlotter;
  
  ofxDatGuiFolder* f1;
  ofxDatGuiFolder* f2;
  
  void setup();
  void update();
  void draw();
  
  void onButtonEvent(ofxDatGuiButtonEvent e);
  void onSliderEvent(ofxDatGuiSliderEvent e);
  void onMatrixEvent(ofxDatGuiMatrixEvent e);
  void on2dPadEvent(ofxDatGui2dPadEvent e);
  void onTextInputEvent(ofxDatGuiTextInputEvent e);
  void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
  void onDropdownEvent(ofxDatGuiDropdownEvent e);
};