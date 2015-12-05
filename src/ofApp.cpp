#include "ofApp.h"

#include "fcTriangleSketch.h"
#include "fcBarSketch.h"

//--------------------------------------------------------------
void ofApp::setup(){

  // window
  ofSetWindowTitle("fauxclick-woodscape");
  ofBackground(0, 0, 0);
  ofSetLogLevel(OF_LOG_VERBOSE);

  // we add this listener before setting up so the initial circle resolution is correct
  vSync.addListener(this, &ofApp::vSyncChanged);
  capFramerate.addListener(this, &ofApp::capFramerateChanged);
  smooth.addListener(this, &ofApp::smoothChanged);

  parameters.setName("settings");
  parameters.add(vSync.set("vSync", false));
  parameters.add(capFramerate.set("capFramerate", false));
  parameters.add(smooth.set("smooth", false));

  // gui
  gui.setup(parameters);

  // sketches
  sketches.push_back(new fcTriangleSketch());
  sketches.push_back(new fcBarSketch());

  // active sketch
  activeSketchIndex = 0;
  sketchLabel = sketches[activeSketchIndex]->name();

  // syphon
  mainOutputSyphonServer.setName("Screen Output");

  // midi
  midiIn.listPorts();
  midiIn.openPort("Ableton Push User Port");
  midiIn.ignoreTypes(false, false, false);  // sysex, timing, active sense
  midiIn.addListener(this);
  midiIn.setVerbose(true);

  // audio
  ofSoundStreamListDevices();
  ofSoundStreamSetup(
    0,                      // output channels
    1,                      // input channels
    this,                   // reference to this app
    44100,                  // sample rate
    beat.getBufferSize(),   // buffer size
    4);                     // amount of buffers, less = more responsive but less stable
}

//--------------------------------------------------------------
void ofApp::vSyncChanged(bool & vSync){
  ofSetVerticalSync(vSync);
  cout << "vSync: " << vSync << endl;
}

//--------------------------------------------------------------
void ofApp::capFramerateChanged(bool & capFramerate){

  // cap framerate to 60fps if requested
  int framerate = capFramerate ? 60 : 0;
  ofSetFrameRate(framerate);

  // log setting switch
  if(framerate) {
    cout << "Frame rate set to: " << framerate << endl;
  } else {
    cout << "Frame rate set to unlimited" << endl;
  }
}

//--------------------------------------------------------------
void ofApp::smoothChanged(bool & smooth){
  if(smooth) {
    ofEnableSmoothing();
    cout << "Smoothing: enabled" << endl;
  } else {
    ofDisableSmoothing();
    cout << "Smoothing: disabled" << endl;
  }
}

//--------------------------------------------------------------
void ofApp::update(){
  beat.update(ofGetElapsedTimeMillis());
  sketches[activeSketchIndex]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){

  // draw current sketch
  sketches[activeSketchIndex]->draw(beat, midiMessage);

  // publish screen to syphon
  mainOutputSyphonServer.publishScreen();

  // everything AFTER this line will not get send over syphon
  // use it to draw the gui, logs, ...

  // draw gui if needed
  if(!bHideGui){
    ofSetColor(255);
    gui.draw();
  }

  //cout << beat.kick() << "," << beat.snare() << "," << beat.hihat() << endl;




  // draw the last recieved message contents to the screen
  text << "Received: " << ofxMidiMessage::getStatusString(midiMessage.status);
  ofDrawBitmapString(text.str(), 20, 20);
  text.str(""); // clear

  text << "channel: " << midiMessage.channel;
  ofDrawBitmapString(text.str(), 20, 34);
  text.str(""); // clear

  text << "pitch: " << midiMessage.pitch;
  ofDrawBitmapString(text.str(), 20, 48);
  text.str(""); // clear
  ofDrawRectangle(20, 58, ofMap(midiMessage.pitch, 0, 127, 0, ofGetWidth()-40), 20);

  text << "velocity: " << midiMessage.velocity;
  ofDrawBitmapString(text.str(), 20, 96);
  text.str(""); // clear
  ofDrawRectangle(20, 105, ofMap(midiMessage.velocity, 0, 127, 0, ofGetWidth()-40), 20);

  text << "control: " << midiMessage.control;
  ofDrawBitmapString(text.str(), 20, 144);
  text.str(""); // clear
  ofDrawRectangle(20, 154, ofMap(midiMessage.control, 0, 127, 0, ofGetWidth()-40), 20);

  text << "value: " << midiMessage.value;
  ofDrawBitmapString(text.str(), 20, 192);
  text.str(""); // clear
  if(midiMessage.status == MIDI_PITCH_BEND) {
    ofDrawRectangle(20, 202, ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()-40), 20);
  }
  else {
    ofDrawRectangle(20, 202, ofMap(midiMessage.value, 0, 127, 0, ofGetWidth()-40), 20);
  }

  text << "delta: " << midiMessage.deltatime;
  ofDrawBitmapString(text.str(), 20, 240);
  text.str(""); // clear
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
}

//--------------------------------------------------------------
void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
  beat.audioReceived(input, bufferSize, nChannels);
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
  }

  sketches[activeSketchIndex]->logName();
  sketchLabel = sketches[activeSketchIndex]->name();
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
