#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  // window
  ofSetWindowTitle("fauxclick-woodscape");
  ofBackground(0, 0, 0);
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofSetFrameRate(0);  // unlimited
  ofSetVerticalSync(true);
  ofDisableSmoothing();

  // libraries and stuff
  this->setupGui();
  this->setupMidi();
  this->setupAudio();
  this->setupSyphon();

  // our sketches
  this->setupSketches();
}

//--------------------------------------------------------------
void ofApp::setupMidi() {
  midiManager = new MidiManager(this);
  midiManager->setup();
}

//--------------------------------------------------------------
void ofApp::setupAudio() {
  audioManager = new AudioManager(this);
  audioManager->setup();
}

//--------------------------------------------------------------
void ofApp::setupSyphon() {
  mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void ofApp::setupGui() {

  // parameter window
  parameterWindow = new ParameterWindow(this);
  parameterWindow->setup();
  
  // add label for the resolution
  resolutionLabel = new ofxDatGuiLabel("");
  
  // create group
  summaryFolder = new ofxDatGuiFolder("summary", ofColor::fromHex(0xFFD00B));
  summaryFolder->attachItem(resolutionLabel);
  
  // add to parameter window
  this->parameterWindow->addFolder(summaryFolder, 0, 0);
  
  // call once for initial resolution
  this->updateResolutionLabel();
  
  // debug grid
  debugGridImage.load("images/grid.png");
}

//--------------------------------------------------------------
void ofApp::setupSketches() {
  sketchManager = new SketchManager(this);
  sketchManager->setup();
}

//--------------------------------------------------------------
void ofApp::update() {
  audioManager->update();
  parameterWindow->update();
  sketchManager->update();
}

//--------------------------------------------------------------
void ofApp::draw() {

  // draw sketch
  sketchManager->draw();

  // publish screen to syphon
  mainOutputSyphonServer.publishScreen();

  // everything AFTER this line will not get send over syphon
  // use it to draw the gui, logs, ...

  // show the triangle debug grid
  if(showDebugGrid) {
    ofSetColor(255, 255, 255, 50);
    debugGridImage.draw(0, 0);
  }

  // draw gui if needed
  if(showGui) {
    parameterWindow->draw();
  }
}

//--------------------------------------------------------------
void ofApp::exit() {
  delete parameterWindow;
  delete audioManager;
  delete sketchManager;
  delete midiManager;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  switch(key) {
    case 'h':
      showGui = !showGui;
      break;

    case 'g':
      showDebugGrid = !showDebugGrid;
      break;

    case '1':
      this->sketchManager->activateSketch("WaveSketch");
      break;

    case '2':
      this->sketchManager->activateSketch("PulseSketch");
      break;

    case '3':
      this->sketchManager->activateSketch("TriangleSketch");
      break;

    case '4':
      this->sketchManager->activateSketch("TrippyLinesSketch");
      break;

    case '5':
      this->sketchManager->activateSketch("SoundwaveSketch");
      break;

    case '6':
      this->sketchManager->activateSketch("FlashSketch");
      break;

    case '7':
      this->sketchManager->activateSketch("VolumeHistorySketch");
      break;
      
    case '8':
      this->sketchManager->activateSketch("CubeSketch");
      break;
      
    case '9':
      this->sketchManager->activateSketch("BoidSketch");
      break;

    case '0':
      this->sketchManager->activateSketch("EinsteinSketch");
      break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
  this->updateResolutionLabel();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::updateResolutionLabel() {
  resolutionLabel->setLabel(ofToString(ofGetWidth()) + "x" + ofToString(ofGetHeight()));
}
