#include "ParameterWindow.h"

ParameterWindow::ParameterWindow(ofSoundStream soundStream){
  this->soundStream = soundStream;
}

ParameterWindow::~ParameterWindow(){
  // destructor
}

void ParameterWindow::setup(){
  int x = 150;
  int y = 100;
  ofSetWindowPosition(0, 0);
  
  // buttons
  vSyncToggle = new ofxDatGuiToggle("VSYNC", false);
  smoothingToggle = new ofxDatGuiToggle("LINE SMOOTHING", false);
  
  // convert the hex values of those colors to strings for the menu labels //
  audioDeviceList = this->soundStream.getDeviceList();
  vector<string> options;
  for(int i = 0; i < audioDeviceList.size(); i++)
    options.push_back(audioDeviceList[i].name);
  
  // instantiate the dropdown //
  audioDropdown = new ofxDatGuiDropdown("AUDIO DEVICES", options);
  
  // folder
  f1 = new ofxDatGuiFolder("display", ofColor::fromHex(0xFFD00B));
  f1->attachItem(vSyncToggle);
  f1->attachItem(smoothingToggle);
  f1->addBreak();
  f1->addFRM();
//  f1->addBreak();
//  f1->addSlider("slider", 0, 100);
//  f1->addMatrix("matrix", 14);
//  f1->addColorPicker("color picker", ofColor::fromHex(0x2FA1D6));
//  f1->addWaveMonitor("wave monitor", 3, .5);
  f1->setOrigin(x, y);
  f1->expand();
  
  f2 = new ofxDatGuiFolder("audio", ofColor::fromHex(0x1ED36F));
  f2->attachItem(audioDropdown);
//  f2->addButton("button");
//  f2->addTextInput("text input", "enter a message");
//  f2->addBreak();
//  f2->addMatrix("matrix", 21, true);
//  f2->addBreak();
//  f2->add2dPad("2d pad");
//  f2->addSlider("slider", 0, 100);
  f2->setOrigin(x + f1->getWidth() + 40, y);
  f2->expand();
  
  // button handlers
  vSyncToggle->onButtonEvent(this, &ParameterWindow::onButtonEvent);
  smoothingToggle->onButtonEvent(this, &ParameterWindow::onButtonEvent);
  
  // dropdown handler
  audioDropdown->onDropdownEvent(this, &ParameterWindow::onDropdownEvent);
  
  // folder handlers
  f1->onButtonEvent(this, &ParameterWindow::onButtonEvent);
  f1->onSliderEvent(this, &ParameterWindow::onSliderEvent);
  f1->onMatrixEvent(this, &ParameterWindow::onMatrixEvent);
  f1->onColorPickerEvent(this, &ParameterWindow::onColorPickerEvent);

  // folder handlers
//  f2->onButtonEvent(this, &ParameterWindow::onButtonEvent);
//  f2->onMatrixEvent(this, &ParameterWindow::onMatrixEvent);
//  f2->on2dPadEvent(this, &ParameterWindow::on2dPadEvent);
//  f2->onTextInputEvent(this, &ParameterWindow::onTextInputEvent);
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
  soundStream.setDevice(audioDeviceList[e.child]);
}