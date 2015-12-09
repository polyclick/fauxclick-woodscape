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
  midiIn.listPorts();
  midiIn.openPort("Ableton Push User Port");
  midiIn.ignoreTypes(false, false, false);  // sysex, timing, active sense
  midiIn.addListener(this);
  midiIn.setVerbose(true);
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

  summary.setName("summary");
  summary.add(screenSize.set("resolution", ""));

  midi.setName("midi");
  midi.add(midiStatus.set("status", ""));
  midi.add(midiChannel.set("channel", ""));
  midi.add(midiPitch.set("pitch", 0, 0, 127));
  midi.add(midiVelocity.set("velocity", 0, 0, 127));
  midi.add(midiControl.set("control", 0, 0, 127));
  midi.add(midiValue.set("value (normalized)", 0, 0, 100));
  midi.add(midiDelta.set("delta", ""));

  debug.add(summary);
  debug.add(midi);

  gui.setup(debug);

  // parameter window
  parameterWindow = new ParameterWindow(this);
  parameterWindow->setup();

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
    ofSetColor(255);
    gui.draw();

    parameterWindow->draw();
  }
}

//--------------------------------------------------------------
void ofApp::exit() {

  // clean up
  midiIn.closePort();
  midiIn.removeListener(this);

  // release memory
  delete parameterWindow;
  delete audioManager;
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

  // make a copy of the latest message
  midiMessage = msg;

  // show in debug
  midiStatus = ofxMidiMessage::getStatusString(midiMessage.status);
  midiChannel = ofToString(midiMessage.channel);
  midiPitch = midiMessage.pitch;
  midiVelocity = midiMessage.velocity;
  midiControl = midiMessage.control;

  if(midiMessage.status == MIDI_PITCH_BEND) {
    midiValue = ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, 100);
  } else {
    midiValue = ofMap(midiMessage.value, 0, 127, 0, 100);
  }

  midiDelta = ofToString(midiMessage.deltatime);
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
  screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
