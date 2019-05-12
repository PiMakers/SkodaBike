#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("DMX Receiver");
	ofSetFrameRate(60); // run at 60 fps
	ofSetVerticalSync(true);

	// listen on the given port
	ofLog() << "listening for DMX messages on port " << PORT;
	receiver.setup(PORT);

    dmx.connect(0); // or use a number
    dmx.clear();
    dmx.update(true); // black on startUp
}

//--------------------------------------------------------------
void ofApp::update(){

	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msgStrings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){

		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);

		// check for dmx level
		if(m.getAddress() == "/dmx1/level"){
			dmx1 = m.getArgAsInt(0);
///			cout << "dmx1 level: " << dmx1 << endl;
			if (dmx1 < 300 ) {
				dmx.setLevel(2, 0);
				dmx.setLevel(4, dmx1);
			}
			else {
				dmx.setLevel(4, 0);
				dmx.setLevel(2, 255);
			}
		}

		else if (m.getAddress() == "/dmx2/level"){
			dmx2 = m.getArgAsInt(0);
//			cout << "dmx2 level: " << dmx2 << endl;
			if (dmx2 < 300 ) {
				dmx.setLevel(6, 0);
				dmx.setLevel(8, dmx2);
			}
			else {
				dmx.setLevel(8, 0);
				dmx.setLevel(6, 255);
			}
            if (dmx2 == 300 ) dmx.setLevel(6, dmx2);
		}
        dmx.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackgroundGradient(100, 0);

	// draw recent unrecognized messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapStringHighlight(msgStrings[i], 10, 40 + 15 * i);
	}

	string buf = "listening on port " + ofToString(PORT);
	ofDrawBitmapStringHighlight(buf, 10, 20);

	// draw mouse state
	ofDrawBitmapStringHighlight("dmx1: " + ofToString(dmx1) + "     dmx2: " + ofToString(dmx2), ofGetWidth()/3, ofGetHeight()/2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f' || key == 'F')
        ofToggleFullscreen();
	
	if (key == 't' || key == 'T')
        {
			for ( float i = 0; i < 255; i += 10)
			{
				dmx1 = i;
				cout << "dmx1 level: " << dmx1 << endl;
            	dmx.setLevel(1, dmx1);
				dmx.update();
				sleep (3);
			}
			
		}		
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::exit() {
	    dmx.clear();
    	dmx.update(true);
		cout << "EXITING!!!" << endl;

}