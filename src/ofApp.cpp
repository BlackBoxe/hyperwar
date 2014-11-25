#include "ofApp.h"


/*

 Image Sequence Example:
 In this example we are going to load a sequence of images from a folder.
 We know that the images are in order and the we saved them out at 24fps.
 the goal is to play them back at 24fps independent of the fps of the app.
 You can toggle the sequence to be independent of the app fps.

 Topics:
 - ofDirectory
 - ofImage
 - timing

 gif from: http://probertson.livejournal.com/32350.html

 */


void ofApp::setup() {

    ofBackground(0);
    ofSetWindowTitle("H.Y.P.E.R.W.A.R");

	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableDepthTest();

    ofSetFullscreen(true);

printf("Start\n");

    //backgroundImage.loadImage("hyperwar_big.png");
    //backgroundImage.setImageType(OF_IMAGE_GRAYSCALE);

    // plan 3d...
    ofEnableAlphaBlending();
    //plan.loadImage("hp_plan.png");
    //plan.setImageType(OF_IMAGE_GRAYSCALE);

    // Background images
    ofDirectory dir;

    int nFiles = dir.listDir("background");
    dir.sort();

    if(nFiles) {
        for(int i=0; i<dir.numFiles(); i++) {
            string filePath = dir.getPath(i);
            backgroundImages.push_back(ofImage());
            backgroundImages.back().loadImage(filePath);
            backgroundImages.back().setImageType(OF_IMAGE_GRAYSCALE);
            cout<<filePath;
            printf("\n");
        }

    }
    else printf("Could not find folder for sequences\n");

    // Decoupes
    nFiles = dir.listDir("decoupes");
    dir.sort();

    if(nFiles) {
        for(int i=0; i<dir.numFiles(); i++) {
            string filePath = dir.getPath(i);
            decoupesImages.push_back(ofImage());
            decoupesImages.back().loadImage(filePath);
            //decoupesVec.push_back( ofVec3f( ofRandom(4000)+100, ofRandom(4000)+100,ofRandom(100)+10 ) );
            decoupesImages.back().setImageType(OF_IMAGE_COLOR_ALPHA);
    cout << "loaded" << filePath << '\n';
        }
    }
    else printf("Could not find folder for decoupes\n");
    NB_DECOUPES = dir.numFiles();

    int zDecoupe = 150;

    decoupesVec.reserve( NB_DECOUPES );
     //decoupesVec[0] = ofVec3f( 100, 100, zDecoupe );
     decoupesVec[0] = ofVec3f( 3371, 3660, zDecoupe );
     decoupesVec[1] = ofVec3f( 4279, 3696, zDecoupe );
     decoupesVec[2] = ofVec3f( 4000, 3184, zDecoupe );
     decoupesVec[3] = ofVec3f( 3657, 2722, zDecoupe );
     decoupesVec[4] = ofVec3f( 44, 2992, zDecoupe );
     decoupesVec[5] = ofVec3f( 621, 3547, zDecoupe );
     decoupesVec[6] = ofVec3f( 544, 3366, zDecoupe );
     decoupesVec[7] = ofVec3f( 4790, 2708, zDecoupe );
     decoupesVec[8] = ofVec3f( 253, 1667, zDecoupe );
     decoupesVec[9] = ofVec3f( 253, 1667, zDecoupe );

     calibX.reserve( NB_DECOUPES );
     calibY.reserve( NB_DECOUPES );

    // Sequences
    nFiles = dir.listDir("fuck");
    dir.sort();
    if(nFiles) {

        for(int i=0; i<dir.numFiles(); i++) {

            // add the image to the vector
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().loadImage(filePath);
            images.back().setImageType(OF_IMAGE_COLOR_ALPHA);
            cout<<filePath;
            printf("\n");
        }

    }
    else printf("Could not find folder for sequences\n");

    // this toggle will tell the sequence
    // be be indepent of the app fps
    bFrameIndependent = true;

    // this will set the speed to play
    // the animatio n back we set the
    // default to 24fps
    sequenceFPS = 24;

    // set the app fps
    appFPS = 60;
    ofSetFrameRate(appFPS);

    // plein de plans 3D
    /*
    for(int i=0; i<10; i++) {
        ofVec3f d = ofVec3f( 5000. * ofRandom(1) + 500 , 3000. * ofRandom(1) + 500, 50. * ofRandom(1) );
        planVec.push_back( d );
    }
    */

   // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    pointLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));

    // specular color, the highlight/shininess color //
	pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
	pointLight.setPointLight();

    // radius of the sphere //
	radius		= 180.f;
	center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);

}

//--------------------------------------------------------------
void ofApp::update() {
    //pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
	//					   sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
	//					   -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);

    //spotLight.setOrientation( ofVec3f( 0, cos(ofGetElapsedTimef()) * RAD_TO_DEG, 0) );
	spotLight.setOrientation( ofVec3f( 0, 90, 0) );
	spotLight.setPosition( mouseX, mouseY, 500);

    pointLight.enable();
    spotLight.enable();
    directionalLight.enable();
}

//--------------------------------------------------------------
void ofApp::draw() {

    ofClear(0, 0, 0, 0);
	ofEnableAlphaBlending();

    // enable lighting //
    ofEnableLighting();

    float cx = ofGetWidth() / 2.0;
    float cy = ofGetHeight() / 2.0;
    
    float diffX = _mouseX - mouseX;
    float diffY = _mouseY - mouseY;
    
    vitX = vitX + 10 * diffX;
    vitY = vitY + 10 * diffY;
    
    float damping = .4f;
    
    vitX *= damping;
    vitY *= damping;
    
    //float mx = mouseX - cx;
    //float my = mouseY - cy;
    
    virtualX = virtualX + vitX;
    virtualY = virtualY + vitY;
    
    if( virtualX > 1.5*backgroundWidth) virtualX = 1.5*backgroundWidth;
    if( virtualX < -1.5*backgroundWidth )              virtualX = -1.5*backgroundWidth;
    if( virtualY > 1.5*backgroundHeight) virtualY = 1.5*backgroundHeight;
    if( virtualY < -1.5*backgroundHeight )               virtualY = -1.5*backgroundHeight;
    
    float mx = virtualX;
    float my = virtualY;

    // this is the total time of the animation based on fps
    //float totalTime = images.size() / sequenceFPS;

    // Draw Background
    const int X_TILES_NB = 3;
    const int Y_TILES_NB = 2;
    const int TILE_WIDTH = 1832;
    const int TILE_HEIGHT = 1947;

    ofSetColor(255, 255);

    ofPushMatrix();
    ofTranslate( -3*TILE_WIDTH/2 + mx, -2*TILE_HEIGHT/2 + my);
    //ofScale(mx, my);
    for(int j=0; j < Y_TILES_NB; j++) {
        for(int i=0; i < X_TILES_NB; i++) {
            int x = TILE_WIDTH  * i;
            int y = TILE_HEIGHT * j;

            backgroundImages[ i + j * (X_TILES_NB ) ].draw( x, y);//, x + ZOOM_X * TILE_WIDTH, y + ZOOM_Y * TILE_HEIGHT );
        }
    }
    ofPopMatrix();

    // Draw Decoupes
    ofPushMatrix();
    ofTranslate( -3*TILE_WIDTH/2 + mx, -2*TILE_HEIGHT/2 + my);
    //ofScale(mx, my);
    for(int j=0; j < NB_DECOUPES; j++) {
        if( j==selected ) ofSetColor(255, 128, 128, 255);
        else ofSetColor(128, 255, 255, 255);
        
        decoupesImages[ j ].draw( decoupesVec[j].x + calibX[j], decoupesVec[j].y + calibY[j], decoupesVec[j].z + j );
    }


    // Draw Sequences
    int frameIndex = 0;

    if(bFrameIndependent) {
        // calculate the frame index based on the app time
        // and the desired sequence fps. then mod to wrap
        frameIndex = (int)(ofGetElapsedTimef() * sequenceFPS) % images.size();
    }
    else {
        // set the frame index based on the app frame
        // count. then mod to wrap.
        frameIndex = ofGetFrameNum() % images.size();
    }


    // draw where we are in the sequence
    float x = 0;
    for(int offset = 0; offset < 5; offset++) {
        int i = (frameIndex + offset) % images.size();
        ofSetColor(255, 0, 0);
        images[i].draw(400+x, ofGetHeight()-40, 200, 200, 1);
        x += 40;
    }
    ofPopMatrix();

    // how fast is the app running and some other info
    ofSetColor(50);
    ofRect(0, 0, 200, 200);
    ofSetColor(200);
    string info;
    info += ofToString(frameIndex)+" sequence index\n";
    info += ofToString(appFPS)+"/"+ofToString(ofGetFrameRate(), 0)+" fps\n";
    info += ofToString(sequenceFPS)+" Sequence fps\n\n";
    info += "Keys:\nup & down arrows to\nchange app fps\n\n";
    info += "left & right arrows to\nchange sequence fps";
    info += "\n\n't' to toggle\nframe independent("+ofToString(bFrameIndependent)+")";

    ofDrawBitmapString(info, 15, 20);
    
    _mouseX = mouseX;
    _mouseY = mouseY;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if(key == 'f')            ofToggleFullscreen();
    if(key == OF_KEY_UP)      calibY[selected] -= 5;
    if(key == OF_KEY_DOWN)    calibY[selected] += 5;
    if(key == OF_KEY_LEFT)    calibX[selected] -= 5;
    if(key == OF_KEY_RIGHT)   calibX[selected] += 5;
    if(key == 't')            bFrameIndependent = !bFrameIndependent;
    if(key == ' ')            { selected++; if( selected > NB_DECOUPES-1) selected = 0; }

    // check for less than zero...
    sequenceFPS = MAX(sequenceFPS, 1);
    appFPS      = MAX(appFPS, 1);

    ofSetFrameRate(appFPS);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
