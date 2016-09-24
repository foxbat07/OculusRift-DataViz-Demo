#pragma once

#include "ofMain.h"
#include "/Users/mohithingorani/Documents/OpenFrameworks/of_v0.8.4_osx_release/addons/ofxOculusDK2/src/ofxOculusDK2.h"
#include "ofxCsv.h"
#include "DataMesh.h"
#include "ofMesh.h"
#include "ofPolyline.h"
#include "ofxExif.h"
#include "ofxOsc.h"


using namespace wng;


typedef struct{
	ofColor color;
	ofVec3f pos;
	ofVec3f floatPos;
	float radius;
    bool bMouseOver;
    bool bGazeOver;
} DemoSphere;




class testApp : public ofBaseApp
{
  public:
	
	void setup();
	void update();
	void draw();
	
	void drawScene();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
    void drawAllosphere();
    void drawMesh();
    void loadDatafromText();
    void drawImageWall();
    void drawImageCylinder();
    void drawImageTunnel();
    void drawImageRandomPlaces();
    void drawImageSpatialCylinder();
    void drawAlloCylinder();
    
    
    void startPlayingAV();
    void drawVideoSphere();
    void pausePlayingAV();
    bool drawAVSphere = false;
    
    
    
    void checkOscMessages();
    
    

	ofxOculusDK2		oculusRift;
    ofxCsv mycsv;
    
	ofLight				light;
	ofEasyCam			cam;
	bool showOverlay;
	bool predictive;
	vector<DemoSphere> demos;
    
    vector< DataMesh> dataPoints;

    ofVec3f cursor2D;
    ofVec3f cursor3D;
    
    ofVec3f cursorRift;
    ofVec3f demoRift;
    
    ofVec3f cursorGaze;
    int balls = 1500;
    int farEdge = 1000;
    
    int xPos = 0 ;
    int yPos = 0 ;
    int zPos = 0 ;
    int spheresVisualized;
    int numRows;
    int numColumns;
    
    int timeTravel = 0;
    
    ofMesh gridMesh;
    ofMesh mesh;
    
    
    int pointSize = 3;
    ofImage image1;
    ofImage image2;
    ofImage image3;

    
    //ofImage image[10];
    //EXIFInfo exif[10];
    bool iGazeOver[1500];
    
    string imageHead;
    int grossImageNumber;
    string imageFolderName;
    
    int imageSize = 256;
    int angle = 1;
    float imageRotation = 0;
    int inlineCount = 5;
    
    ofLight lights;
    
    
    
    ofColor cHUDBackground;
    ofColor cHUDTextOne;
    
    int HUDMargin = 20;
    int HUDWidth = 320;
    int HUDHeight = 240;
    
    
    ofxOscReceiver receiver;
    
    float xSensitivity = 100;
    float ySensitivity = 100;
    float zSensitivity = 100;
    
    
    int numberOfImages;
    
    vector<ofImage> image;
    vector<string> imagePath;
    vector<EXIFInfo> exif;
    
    ofDirectory dir;
    
    bool checkRotation = false;
    
    
    //make video as well
    
    
    ofVideoPlayer video;
    unsigned char * 	videoPixels;
    ofTexture			videoTexture;
    int 				videoWidth;
    int 				videoHeight;
    int                 vRadius;

    ofSoundPlayer music;
    
    

    
    
    
    
  
};

