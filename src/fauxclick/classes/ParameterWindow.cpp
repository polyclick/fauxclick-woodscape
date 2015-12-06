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
  
  // audio devices dropdown
  // convert the hex values of those colors to strings for the menu labels //
  audioDeviceList = this->app->audioManager->soundStream.getDeviceList();
  vector<string> options;
  for(int i = 0; i < audioDeviceList.size(); i++) options.push_back(audioDeviceList[i].name);
  audioDropdown = new ofxDatGuiDropdown("AUDIO DEVICES", options);
  audioDropdown->onDropdownEvent(this, &ParameterWindow::onDropdownEvent);
  
  // kick, snare, hihat plotters
  kickValuePlotter = new ofxDatGuiValuePlotter("KICK", 0, 100);
  kickValuePlotter->setSpeed(2.0);
  snareValuePlotter = new ofxDatGuiValuePlotter("SNARE", 0, 100);
  snareValuePlotter->setSpeed(2.0);
  hihatValuePlotter = new ofxDatGuiValuePlotter("HIHAT", 0, 100);
  hihatValuePlotter->setSpeed(2.0);
  
  // display folder
  f1 = new ofxDatGuiFolder("display", ofColor::fromHex(0xFFD00B));
  f1->attachItem(vSyncToggle);
  f1->attachItem(smoothingToggle);
  f1->addBreak();
  f1->addFRM();
  f1->setOrigin(x, y);
  f1->expand();
  
  // audio folder
  f2 = new ofxDatGuiFolder("audio", ofColor::fromHex(0x1ED36F));
  f2->attachItem(audioDropdown);
  f2->attachItem(kickValuePlotter);
  f2->attachItem(snareValuePlotter);
  f2->attachItem(hihatValuePlotter);
  f2->setOrigin(x + f1->getWidth() + 40, y);
  f2->expand();
  
  // folder handlers
  f1->onButtonEvent(this, &ParameterWindow::onButtonEvent);
  f1->onSliderEvent(this, &ParameterWindow::onSliderEvent);
  f1->onMatrixEvent(this, &ParameterWindow::onMatrixEvent);
  f1->onColorPickerEvent(this, &ParameterWindow::onColorPickerEvent);

  // folder handlers
  f2->onButtonEvent(this, &ParameterWindow::onButtonEvent);
  f2->onMatrixEvent(this, &ParameterWindow::onMatrixEvent);
  f2->on2dPadEvent(this, &ParameterWindow::on2dPadEvent);
  f2->onTextInputEvent(this, &ParameterWindow::onTextInputEvent);
}

void ParameterWindow::update(){
  f1->update();
  f2->update();
}

void ParameterWindow::draw() {
  f1->draw();
  f2->draw();
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

void ParameterWindow::onSliderEvent(ofxDatGuiSliderEvent e)
{
  cout << "onSliderEvent" << endl;
}

void ParameterWindow::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
  cout << "onTextInputEvent" << endl;
}

void ParameterWindow::on2dPadEvent(ofxDatGui2dPadEvent e)
{
  cout << "on2dPadEvent" << endl;
}

void ParameterWindow::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
  cout << "onColorPickerEvent" << endl;
}

void ParameterWindow::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
  cout << "onMatrixEvent" << endl;
}

void ParameterWindow::onDropdownEvent(ofxDatGuiDropdownEvent e) {
  this->app->audioManager->soundStream.setDevice(audioDeviceList[e.child]);
}