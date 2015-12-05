#include "ofApp.h"

#include "fcTriangleSketch.h"
#include "fcBarSketch.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  // window
  ofSetWindowTitle("fauxclick-woodscape");
  
  // gui
  gui.setup();
  gui.add(screenSize.setup("screen size", ofToString(ofGetWidth()) + "x" + ofToString(ofGetHeight())));
  gui.add(sketchLabel.setup("sketch", "none"));
  
  // show or hide gui
  bHideGui = false;
  
  // sketches
  sketches.push_back(new fcTriangleSketch());
  sketches.push_back(new fcBarSketch());
  
  // active sketch
  activeSketchIndex = 0;
  sketchLabel = sketches[activeSketchIndex]->name();
  
  // syphon
  mainOutputSyphonServer.setName("Screen Output");
  
  // cap framerate if we want
  //// ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
  sketches[activeSketchIndex]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  
  // draw current sketch
  sketches[activeSketchIndex]->draw();
  
  // publish screen to syphon
  mainOutputSyphonServer.publishScreen();
  
  // everything AFTER this line will not get send over syphon
  // use it to draw the gui, logs, ...
  
  // draw gui if needed
  if(!bHideGui){
    gui.draw();
  }
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
