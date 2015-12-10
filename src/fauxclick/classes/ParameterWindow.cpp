#include "ParameterWindow.h"

#include "ofApp.h"

ParameterWindow::ParameterWindow(ofApp* app){
  this->app = app;
}

ParameterWindow::~ParameterWindow(){
  // destructor
}

void ParameterWindow::setup(){
  int x = 150;
  int y = 100;
  ofSetWindowPosition(0, 0);
  
  // vsync button
  vSyncToggle = new ofxDatGuiToggle("VSYNC", true);
  vSyncToggle->onButtonEvent(this, &ParameterWindow::onButtonEvent);
  
  // smoothing toggle
  smoothingToggle = new ofxDatGuiToggle("LINE SMOOTHING", false);
  smoothingToggle->onButtonEvent(this, &ParameterWindow::onButtonEvent);
  
  // display folder
  settingsFolder = new ofxDatGuiFolder("display", ofColor::fromHex(0xFFD00B));
  settingsFolder->attachItem(vSyncToggle);
  settingsFolder->attachItem(smoothingToggle);
  settingsFolder->addBreak();
  settingsFolder->addFRM();
  
  // folder handlers
  settingsFolder->onButtonEvent(this, &ParameterWindow::onButtonEvent);
  
  // add folder
  this->addFolder(settingsFolder, 0, 80);
}

void ParameterWindow::update(){
  for (auto &folder : this->folders) {
    folder->update();
  }
}

void ParameterWindow::draw() {
  for (auto &folder : this->folders) {
    folder->draw();
  }
}

void ParameterWindow::addFolder(ofxDatGuiFolder* folder, int x, int y) {
  folder->setOrigin(x, y);
  folder->expand();
  
  this->folders.push_back(folder);
}

void ParameterWindow::onButtonEvent(ofxDatGuiButtonEvent e) {
  
  // vsync
  if(e.target == vSyncToggle) {
    
    cout << "vsync: " << vSyncToggle->getEnabled() << endl;
    ofSetVerticalSync(vSyncToggle->getEnabled());
    
  // smoothing
  } else if(e.target == smoothingToggle) {
    
    cout << "smoothing: " << smoothingToggle->getEnabled() << endl;
    if(smoothingToggle->getEnabled()) {
      ofEnableSmoothing();
    } else {
      ofDisableSmoothing();
    }
    
  }
}
