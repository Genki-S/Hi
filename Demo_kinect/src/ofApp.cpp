#include "getUDP.h"
#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //start
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    //likemark
    myImage.loadImage("/Users/user/Desktop/likemark.png");
    
    //joinmark
    joinImage.loadImage("/Users/user/Desktop/joinmark.png");
    
    //load_font
    font.loadFont("ヒラギノ角ゴ Pro W6.otf", 40);
    
    //image
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    
    //threshold
    nearThreshold = 181;
    farThreshold = 48;
    bThreshWithOpenCV = true;
    
    //frameRate
    ofSetFrameRate(50);
    
    //tile
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
    //start from the front
    bDrawPointCloud = false;
    
    //initialization-いらないかも
    
    MovImage.x=0;
    MovImage.y=/*ofGetHeight()/2;*/0;
    //Movjoin.x=ofGetWidth()/2;
    //Movjoin.y=ofGetHeight()/2;
    topic.x=-50;
    //like = 1;
    //recv udp
    LeapThreadInit();
    //test
    //kinect_data.message="testtest";
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    ofBackground(200, 200, 200);
    
    kinect.update();
    
    //new_frame
    if(kinect.isFrameNew()) {
        
        //binarization_&_get_border
        grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        } else {
            
            unsigned char * pix = grayImage.getPixels();
            
            int numPixels = grayImage.getWidth() * grayImage.getHeight();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
        }
        
        //update_cv_images
        grayImage.flagImageChanged();
        
        //find_contours
        contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 200, false);
    }
    
    //likemark_Position
    like=kinect_data.pushlike;
    if(like==1){
        MovImage.x = rand() % ofGetWidth();
        MovImage.y=ofGetHeight()/2;
        //MovImage.y -= 9.0;
        like=0;
    }
    MovImage.y -= 9.0;
    
    joinjoin=kinect_data.pushjoin;
    //joinmark_position_&_size
    if(joinjoin==1){
        Sizejoin.x = 794;
        Sizejoin.y = 256;
        joinjoin=0;
    }
    Sizejoin.x -= 9.0;;
    Sizejoin.y -= 2.0;
    Movjoin.x=ofGetWidth()/2-Sizejoin.x/2;
    Movjoin.y=ofGetHeight()/2-Sizejoin.y/2;
    
    //text
    if((kinect_data.message=="")){
        std::cout << "pass"<<std::endl;
    }
    else if(hello.x>-9);
    else{
        hello.text = kinect_data.message;
        hello.x = ofGetWidth();
        hello.y = rand()%(ofGetHeight()+10);
        hello.rect = font.getStringBoundingBox(kinect_data.message, 0, 0);
        kinect_data.message="";
    }
    hello.x = hello.x -9;
    
    if(topic.x<-40){
        topic.text = "TOPIC : hackathon";
        topic.x = ofGetWidth();
        topic.y = 50;
        topic.rect = font.getStringBoundingBox(kinect_data.message, 0, 0);
    }
    topic.x = topic.x -4;

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255, 255, 255);
    
    if(bDrawPointCloud) {
        easyCam.begin();
        easyCam.end();
    } else {
        //draw_kinect
        kinect.draw(0, 0, ofGetWidth(), ofGetHeight());
        contourFinder.draw(0, 0, ofGetWidth(), ofGetHeight());
        
    }
    
    //draw_instructions
    ofSetColor(255, 255, 255);
    stringstream reportStream;
    
    //display_data
    if(kinect.hasAccelControl()) {
        /*reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
        << ofToString(kinect.getMksAccel().y, 2) << " / "
        << ofToString(kinect.getMksAccel().z, 2) << endl;*/
    } else {
        reportStream << "Note: this is a newer Xbox Kinect or Kinect For Windows device," << endl
        << "motor / led / accel controls are not currently supported" << endl << endl;
    }
    
    reportStream <</* "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
    <<*/ "set near threshold " << nearThreshold << " (press: + -)" << endl
    << "set far threshold " << farThreshold << " (press: < >)" << endl
    /*<< "press c to close the connection and o to open it again, connection is: " << kinect.isConnected()*/ << endl;
    /*
    if(kinect.hasCamTiltControl()) {
        reportStream << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
        << "press 1-5 & 0 to change the led mode" << endl;
    }
    */
    ofDrawBitmapString(reportStream.str(), 20, 652);
    
    //draw_topic
    ofSetColor(255, 25, 25);
    font.drawString(topic.text, topic.x, topic.y);
    
    
    //draw_message
    ofSetColor(0, 0, 0);
    font.drawString(hello.text, hello.x, hello.y);
    
    //draw_likemark
    if(MovImage.y>20){
        ofSetColor(255, 255, 255);
        myImage.draw(MovImage.x, MovImage.y, 200, 200);
    }
    
    //draw_joinmark
    if(Sizejoin.x>50){
        ofSetColor(255, 255, 255);
        joinImage.draw(Movjoin.x, Movjoin.y, Sizejoin.x, Sizejoin.y);
    }
    
}

//--------------------------------------------------------------
void ofApp::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed (int key) {
    switch (key) {
        case ' ':
            bThreshWithOpenCV = !bThreshWithOpenCV;
            break;
            
        case'p':
            bDrawPointCloud = !bDrawPointCloud;
            break;
            
        case '>':
        case '.':
            farThreshold ++;
            if (farThreshold > 255) farThreshold = 255;
            break;
            
        case '<':
        case ',':
            farThreshold --;
            if (farThreshold < 0) farThreshold = 0;
            break;
            
        case '+':
        case '=':
            nearThreshold ++;
            if (nearThreshold > 255) nearThreshold = 255;
            break;
            
        case '-':
            nearThreshold --;
            if (nearThreshold < 0) nearThreshold = 0;
            break;
            
        case 'w':
            kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
            break;
            
        case 'o':
            kinect.setCameraTiltAngle(angle); // go back to prev tilt
            kinect.open();
            break;
            
        case 'c':
            kinect.setCameraTiltAngle(0); // zero the tilt
            kinect.close();
            break;
            
        case '1':
            kinect.setLed(ofxKinect::LED_GREEN);
            break;
            
        case '2':
            kinect.setLed(ofxKinect::LED_YELLOW);
            break;
            
        case '3':
            kinect.setLed(ofxKinect::LED_RED);
            break;
            
        case '4':
            kinect.setLed(ofxKinect::LED_BLINK_GREEN);
            break;
            
        case '5':
            kinect.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
            break;
            
        case '0':
            kinect.setLed(ofxKinect::LED_OFF);
            break;
            
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{}
