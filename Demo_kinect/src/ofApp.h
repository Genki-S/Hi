#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxTrueTypeFontUC.h"

class ofApp : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void drawPointCloud();
    
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    //いいねマーク
    ofImage myImage;
    ofVec2f MovImage;//position
    int like = 0;//ON/OFF
    
    //いーれてボタン
    ofImage joinImage;
    ofVec2f Movjoin; //position
    ofVec2f Sizejoin; //size
    int joinjoin = 0;
    
    //受信メッセージ
    ofVec2f MovMessage; //position
    int messagebox = 0; //ON/OFF
    ofxTrueTypeFontUC myFont;
    
    ofxKinect kinect;
    
    ofxCvColorImage colorImg;//RGB
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
    ofxCvContourFinder contourFinder;//輪郭抽出クラス
    
    bool bThreshWithOpenCV;
    bool bDrawPointCloud;
    
    int nearThreshold;
    int farThreshold;
    
    int angle;
    
    // used for viewing the point cloud
    ofEasyCam easyCam;
};
