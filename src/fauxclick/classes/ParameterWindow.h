#pragma once

#include "ofxDatGui.h"

class ofApp;

class ParameterWindow {

private:
  ofApp *app;
  
public:
  ParameterWindow(ofApp* app);
  ~ParameterWindow();
  
  void setup();
  void update();
  void draw();
  
  void addFolder(ofxDatGuiFolder *folder, int x = 0, int y = 0);
  
  void onButtonEvent(ofxDatGuiButtonEvent e);
  
  vector<ofxDatGuiFolder*> folders;

  ofxDatGuiFolder* settingsFolder;
  ofxDatGuiButton* vSyncToggle;
  ofxDatGuiButton* smoothingToggle;
};