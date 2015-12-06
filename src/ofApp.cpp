#include "ofApp.h"

#include "TriangleSketch.h"
#include "FFTBarSketch.h"
#include "TriangleNoiseSketch.h"
#include "SoundwaveSketch.h"

//--------------------------------------------------------------
void ofApp::setup(){

  // window
  ofSetWindowTitle("fauxclick-woodscape");
  ofBackground(0, 0, 0);
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofSetFrameRate(0);  // unlimited
  ofSetVerticalSync(false);
  ofDisableSmoothing();
  
  // libraries and stuff
  this->setupMidi();
  this->setupAudio();
  this->setupSyphon();
  this->setupGui();
  
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
  soundStream.printDeviceList();
  
  // first try to get akai device
  vector<ofSoundDevice> matches = soundStream.getMatchingDevices("Akai Professional, LP: EIE pro (Core Audio)");
  
  // else try traktor a10
  if(!matches.size())
    matches = soundStream.getMatchingDevices("Akai Professional, LP: EIE pro (Core Audio)");
  
  // if akai or traktor found, set as main
  // this will automatically fallback to microphone audio if none of both was found
  if(matches.size())
    soundStream.setDevice(matches[0]);
  
  // setup the soundstream
  bufferSize = 256;
  soundStream.setup(this, 0, 1, 44100, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::setupSyphon() {
  mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void ofApp::setupGui() {
  
  summary.setName("summary");
  summary.add(sketchLabel.set("sketch", ""));
  summary.add(screenSize.set("resolution", ""));
  
  midi.setName("midi");
  midi.add(midiStatus.set("status", ""));
  midi.add(midiChannel.set("channel", ""));
  midi.add(midiPitch.set("pitch", 0, 0, 127));
  midi.add(midiVelocity.set("velocity", 0, 0, 127));
  midi.add(midiControl.set("control", 0, 0, 127));
  midi.add(midiValue.set("value (normalized)", 0, 0, 100));
  midi.add(midiDelta.set("delta", ""));
  
  audio.setName("audio");
  audio.add(audioKick.set("kick", 0, 0, 100));
  audio.add(audioSnare.set("snare", 0, 0, 100));
  audio.add(audioHat.set("hat", 0, 0, 100));
  
  debug.add(summary);
  debug.add(midi);
  debug.add(audio);
  
  gui.setup(debug);
  
  parameterWindow = new ParameterWindow(soundStream);
  parameterWindow->setup();
}

//--------------------------------------------------------------
void ofApp::setupSketches() {
  sketches.push_back(new TriangleSketch(this, "TriangleSketch"));
  sketches.push_back(new FFTBarSketch(this, "FFTBarSketch"));
  sketches.push_back(new TriangleNoiseSketch(this, "TriangleNoiseSketch"));
  sketches.push_back(new SoundwaveSketch(this, "SoundwaveSketch"));
  
  // call setup
  for (auto &sketch : sketches) {
    sketch->setup();
  }
  
  // active sketch
  activeSketchIndex = 0;
  sketchLabel = sketches[activeSketchIndex]->getName();
}

//--------------------------------------------------------------
void ofApp::update() {

  // update beat detector
  beat.update(ofGetElapsedTimeMillis());

  // debug
  audioKick = beat.kick() * 100.0;
  audioSnare = beat.snare() * 100.0;
  audioHat = beat.hihat() * 100.0;

  // update active sketch
  sketches[activeSketchIndex]->update(beat);
  
  // update parameter window
  parameterWindow->update();
}

//--------------------------------------------------------------
void ofApp::draw() {

  // draw current sketch
  sketches[activeSketchIndex]->draw();

  // publish screen to syphon
  mainOutputSyphonServer.publishScreen();

  // everything AFTER this line will not get send over syphon
  // use it to draw the gui, logs, ...

  // draw gui if needed
  if(!bHideGui){
    ofSetColor(255);
    gui.draw();
    
    parameterWindow->draw();
  }

  //cout << beat.kick() << "," << beat.snare() << "," << beat.hihat() << endl;
}

//--------------------------------------------------------------
void ofApp::exit() {

  // clean up
  midiIn.closePort();
  midiIn.removeListener(this);
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
void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
  
  // feed audio to beat detector
  beat.audioReceived(input, bufferSize, nChannels);
  
  // feed audio to active sketch
  if(sketches.size())
    sketches[activeSketchIndex]->audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  ofLog(OF_LOG_NOTICE, "the number is " + ofToString(key));

  switch(key) {
    case 'h':
      bHideGui = !bHideGui;

    case '1':
      activeSketchIndex = 0;
      break;

    case '2':
      activeSketchIndex = 1;
      break;

    case '3':
      activeSketchIndex = 2;
      break;
      
    case '4':
      activeSketchIndex = 3;
      break;
  }

  sketches[activeSketchIndex]->logName();
  sketchLabel = sketches[activeSketchIndex]->getName();
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
