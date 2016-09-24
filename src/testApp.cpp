#include "testApp.h"

//--------------------------------------------------------------

void testApp::setup()
{
	ofBackground(0);
	ofSetLogLevel( OF_LOG_VERBOSE );
	ofSetVerticalSync( true );
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //ofEnableAlphaBlending();
    //ofEnableSmoothing();
    //ofSetFullscreen(true);
    receiver.setup(8000);
    //lights.enable();

    
    numberOfImages = dir.listDir("images6");
    
    
    for ( int i = 0 ; i< numberOfImages ; i++ )
    {
        
        string filepath = dir.getPath(i);
        ofImage tempImage ;
        tempImage.loadImage(filepath);
        
        //EXIFInfo tempExif;
        //tempExif = getEXIF(filepath);
        //cout<<tempExif.ExposureTime<<endl;

        //exif.push_back(tempExif);
        image.push_back(tempImage);
        imagePath.push_back(filepath);
    }
    
    
    
    
    // creating grid
    gridMesh.setMode(OF_PRIMITIVE_POINTS);
    
    int sideNumber =  5  ;//2x the number
    int gridGap = 1000;
    
    for ( int i = -sideNumber ; i< sideNumber ; i++ )
    {
        for ( int j = -sideNumber; j < sideNumber ; j++ )
        {
            for ( int k =-sideNumber ; k< sideNumber ; k++ )
            {
                ofVec3f vPoint;
                
                vPoint.x = i * gridGap;
                vPoint.y = j * gridGap;
                vPoint.z = k * gridGap;
                ofColor c;
                //c.set( ofMap(i, -10, 10, 0, 255) , ofMap( j, -10, 10, 0, 255), ofMap( k , -10, 10, 0, 255) );
                //c.set(0, 255 ,0 );
                c.set( ofMap(i, -sideNumber, sideNumber, 0, 255) , ofMap( j, 0, sideNumber, 0, 255), ofMap( k , -sideNumber, 0, 0, 255) );
                gridMesh.addColor(c);
                gridMesh.addVertex(vPoint);
                
            }
        }
    }
    
    //ofToggleFullscreen();
	showOverlay = false;
	predictive = false;
	
	ofHideCursor();
	
	oculusRift.baseCamera = &cam;
	oculusRift.setup();
    
    
  	//enable mouse;
	cam.begin();
    cam.setPosition(0, 0,0);
	cam.end();
    
    
    // adding video playback
    //video.loadMovie("kolor-fighter-aircraft-4k.mp4" );
    video.loadMovie("aviciiHiRes_1.mp4" );
    
    
    videoWidth =  video.getWidth();
    videoHeight = video.getHeight();
    videoPixels 	= new unsigned char[videoWidth*videoHeight *3];
    videoTexture.allocate(videoWidth,videoHeight, GL_RGB);
    
    vRadius = 500;
    //video.play();
    music.loadSound("WaitingForLove.mp3");
    
    video.setLoopState(OF_LOOP_NORMAL);
    music.setLoop(true);
    
    
    
}


//--------------------------------------------------------------
void testApp::update()
{
    checkOscMessages();
    cam.setPosition(xPos, yPos, zPos);
    cout<<"camera positon"<< xPos<<" " << yPos<<" " <<zPos <<endl;
    
    
    //play in parallel for now
    ofSoundUpdate();
    
    video.update();
    if ( video.isFrameNew())
    {
        videoPixels = video.getPixels();
        videoTexture.loadData(videoPixels, videoWidth, videoHeight, GL_RGB);
        
    }
    
    
    
    
    }


//--------------------------------------------------------------
void testApp::draw()
{
    
	if(oculusRift.isSetup())
      {
		
		if(showOverlay){
			
			oculusRift.beginOverlay(-240, HUDWidth ,HUDHeight);
			ofRectangle overlayRect = oculusRift.getOverlayRectangle();
			ofPushStyle();
			ofEnableAlphaBlending();
			ofFill();
			ofSetColor(0, 40, 100, 100);
			
			ofRect(overlayRect);
			
            ofSetColor(ofColor::brown);
            ofFill();
            
            //ofSetColor(ofColor(0,100,200));
			//ofDrawBitmapString("Spatial Images by\nMohit Hingorani \nFPS:"+ofToString(ofGetFrameRate())+"\nPosition: "+ofToString(xPos)+" "+ ofToString(yPos)+" " +ofToString(zPos)+ "\nPredictive Tracking " + (oculusRift.getUsePredictiveOrientation() ? "YES" : "NO")  , 40, 40);
            
            ofDrawBitmapString("Spatial Images", HUDMargin,HUDMargin);
            
            ofDrawBitmapString("Position: "+ofToString(xPos)+" "+ ofToString(yPos)+" " +ofToString(zPos),HUDWidth- HUDMargin- 120,HUDMargin );
            ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()) , HUDWidth- HUDMargin- 100, 2*HUDMargin);
            /*
     
            for ( int i = 0 ; i< numberOfImages ; i++ )
                {
                
                 if ( iGazeOver[i] == true )
                 {
                     ofDrawBitmapString( "Shutter speed: " + ofToString(exif[i].ExposureTime) , HUDMargin, HUDMargin*4);
                     ofDrawBitmapString(  "ISO: "+ ofToString( exif[i].ISOSpeedRatings ) , HUDMargin, HUDMargin* 5);
                     ofDrawBitmapString(  "Aperture: " + ofToString(exif[i].FNumber) , HUDMargin,HUDMargin * 6);
                     ofDrawBitmapString(  "focal length: " + ofToString(exif[i].FocalLength) , HUDMargin, HUDMargin* 7);
                     cout<<"overlay";
                     
                     
                 }
                    
   
                }
             
     */
            
            
            //ofDrawBitmapString("Rotation: " + ofToString(c ) , HUDWidth- HUDMargin- 80, 3*HUDMargin);
            
            ofSetColor(240);
            ofNoFill();
            ofCircle(overlayRect.getCenter(), 20);
			
			ofPopStyle();
			oculusRift.endOverlay();
		}
        
        ofSetColor(255);
		glEnable(GL_DEPTH_TEST);


		oculusRift.beginLeftEye();
		drawScene();
		oculusRift.endLeftEye();
		
		oculusRift.beginRightEye();
		drawScene();
		oculusRift.endRightEye();
		
		oculusRift.draw();
		
		glDisable(GL_DEPTH_TEST);
    }
	else

    {
		cam.begin();
		drawScene();
		cam.end();
	}
	
}

//--------------------------------------------------------------
void testApp::drawScene()
{
    // draw images
    //drawMesh();
        //drawImageWall();
    //drawImageCylinder();
    //drawImageRandomPlaces();
    
    if (drawAVSphere)
        drawVideoSphere();
    else
    {
        //drawImageSpatialCylinder();
       // drawImageCylinder();
        drawAlloCylinder();
        //drawAllosphere();

    }
    
	//billboard and draw the mouse
	if(oculusRift.isSetup()){
		ofPushMatrix();
		oculusRift.multBillboardMatrix();
		ofSetColor(255, 0, 0);
		ofCircle(0,0,.5);
		ofPopMatrix();

        
	}
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    int move =100;
    
	if( key == 'f' )
	{
		//gotta toggle full screen for it to be right
		ofToggleFullscreen();
	}
	
	if(key == 's'){
		oculusRift.reloadShader();
	}
	
	if(key == 'v'){
		oculusRift.lockView = !oculusRift.lockView;
	}
	
	if(key == 'o'){
		showOverlay = !showOverlay;
	}
	if(key == 'r'){
		oculusRift.reset();
		
	}
	if(key == 'h'){
		ofHideCursor();
	}
	if(key == 'H'){
		ofShowCursor();
	}
	
	if(key == 'p'){
		predictive = !predictive;
		oculusRift.setUsePredictedOrientation(predictive);
	}
    
    
    if( key == 'i')
        yPos+=move;
    if( key == 'j')
        xPos-=move;
    if ( key == 'k')
        yPos-=move;
    if(key == 'l')
        xPos+=move;
    
    if(key == 'q')
        zPos+=move;
    if(key == 'a')
        zPos-=move;
    
    if(key == 'y')
        pointSize++;
    if( key == 't')
        pointSize--;
    
    if( key == 'e')
        angle ++ ;
    
    if( key == 'r')
        imageRotation+=0.1;
    
    

  
    if ( key == 'b')
    {
        drawAVSphere = !drawAVSphere;
    }
    
    if ( key == 'n')
    {
        startPlayingAV();
    }
    
    
    if ( key == 'm')
    {
        pausePlayingAV();
    }
    
    
    if(key == 'v')
    {
        cam.setPosition(0, 0, 0);
        
    }
}


void testApp::drawImageWall()
{
    ofPushStyle();
    ofPushMatrix();
    ofSetColor(255);

    
    for ( int  i = 0 ; i< numberOfImages ; i++)
    {
        ofPushMatrix();
        ofScale(-1,-1,1);

        //ofRotateY( ofRadToDeg(PI/10*10)* 100 );
        image[i].resize(imageSize , imageSize);
        int centralize = grossImageNumber/2;
        int xCoord = (i- (grossImageNumber-1)/2) * imageSize;
        int yCoord = -imageSize/2;
        int zCoord = 1000;
        
        if( iGazeOver[i])
        {
            ofSetColor(0, 0, 255);
            
            image[i].draw(xCoord,yCoord,zCoord);
        }
        else
            image[i].draw(xCoord,yCoord,zCoord);

        /*
        ofSetColor(255);
        ofScale(1,1,1);
        ofDrawBitmapString( ofToString(exif[i].ExposureTime ) , xCoord, yCoord, zCoord- 1);
        //exif[i].ExposureTime;
        */
        
        ofPopMatrix();

    }
    ofPopMatrix();
    
    ofPopStyle();
    
}

void testApp::drawImageCylinder()
{
    ofPushStyle();
    ofPushMatrix();
    //ofScale(-1,1,1);
    ofScale(1, -1,1);

    
    ofSetColor(255);
    
    
    for ( int  i = 0 ; i< numberOfImages ; i++)
    {
        
        ofPushMatrix();
        //ofRotateY( ofRadToDeg(PI/10*10)* 100 );
        image[i].resize(imageSize , imageSize);
        
        
        float imageAngle = i * angle;
        float imagePositionAngle = i * imageRotation ;
        float imageZposition;
        
        //ofRotate(angle, 1, 0, 0);

        int radius = 1024;
        int centralize = grossImageNumber/2;
        int xCoord = radius * sin(imageAngle);
       // int yCoord = -imageSize/2 +  ( i / inlineCount ) * imageSize ;
        int yCoord = 0 ;
        int zCoord = radius* cos(imageAngle);
        ofTranslate(xCoord, yCoord, zCoord);
        ofRotateY(imagePositionAngle);
        
        //ofImage tempImage = image[i].getPixelsRef();
        
        image[i].draw(0,0,0);
        //cout<<endl <<"draw"<< i;
        
       //image[i].draw(xCoord,yCoord,zCoord);
        ofPopMatrix();
        
        
    }
    
    ofPopMatrix();
    ofPopStyle();
    
}

void testApp::drawAlloCylinder()
{
    
    ofPushStyle();
    ofPushMatrix();
    //ofScale(-1,1,1);
    ofScale(1, -1,1);
    
    
    ofSetColor(255,255);
    
    
    for ( int  i = 0 ; i< numberOfImages ; i++)
    {
        
        ofPushMatrix();
        //ofRotateY( ofRadToDeg(PI/10*10)* 100 );
        //image[i].resize(imageSize , imageSize);
        image[i].resize(96 , 96 );
        
        /*
        
        float imageAngle = i * angle;
        float imagePositionAngle = i * imageRotation ;
        float imageZposition;
        
        //ofRotate(angle, 1, 0, 0);
        
        int radius = 1024;
        int centralize = grossImageNumber/2;
        int xCoord = radius * sin(imageAngle) + 1000* ofNoise(ofGetFrameNum() *10 )  ;
        int yCoord = 1000* ofNoise(ofGetFrameNum() *10 ) ;
        int zCoord = radius* cos(imageAngle) ;
        ofTranslate(xCoord, yCoord, zCoord);
        //ofRotateY(imagePositionAngle);
    
        image[i].draw(0,0,0);
         */
        
        int radius = 256+128;
        float tier = i / 100;    // 250 photos in a ring
        float level = i % 5;     // 6 possible levels
        float level2 = i % 7;
        float level3 = i % 4;

        int yCoord =   level * 100 + level2 * 50 + ( 4- level3 ) * 50;
        int xCoord =   ( radius + tier * 200  - yCoord/10 ) * sin ( i * 10 );
        
        int zCoord =   ( radius + tier * 200 + yCoord/10  ) * cos ( i *10 );
        
        ofTranslate(xCoord, yCoord, zCoord);
        ofRotate( -sin (i*10)  , 1, 0, 0);
        image[i].draw(0,0,0);
        ofPopMatrix();
        
        
    }
    
    ofPopMatrix();
    ofPopStyle();

    
}



void testApp::drawImageSpatialCylinder()
{
    ofPushStyle();
    ofPushMatrix();
    ofScale(1, -1,1);
    //ofScale(-1,1,1);
    ofSetColor(255);
    int radius = 512+256 ;
    int alternate = 0;
    
    for ( int  i = 0 ; i< numberOfImages ; i++)
    {
        
        
        //ofRotateY( ofRadToDeg(PI/10*10)* 100 );
        
        
        int circumference = 2 * PI * radius;
        int spaceFactor = 2;
        int imagesThatFitInCircle = circumference / imageSize ;
    
        
        int startImage  = i;
        int endImage = startImage  + imagesThatFitInCircle ;
        radius += 200;
        alternate++;
        
        for ( int j = startImage ; j < endImage ; j++ )
            {
            ofPushMatrix();
            
                
            int angle = ofMap(j  , startImage, endImage, 0, 300 );
            int xCoord = radius * cos( angle );
            int yCoord = radius * cos(angle) * sin(angle)* 2 ;
            int zCoord = radius * sin ( angle );
             
            
            if(!checkRotation)
                {
                if ( alternate%2 ==0 )
                    ofRotate(ofGetFrameNum() * .01 * i/20, 0, 1, 0);//rotate from centre
                else
                    ofRotate(ofGetFrameNum() * .01 * i/20 , 0 , -1, 0);//rotate from centre
                    
                ofTranslate(xCoord, yCoord, zCoord);
                
                    if ( alternate%2 ==0 )
                    ofRotate(ofGetFrameNum() * .1, 0, 1, 0);//rotate from centre
                else
                    ofRotate(ofGetFrameNum() * .1, 0 , -1, 0);//rotate from centre
                }
            else
                ofTranslate(xCoord, yCoord, zCoord);
                
            //ofRotate(ofGetFrameNum() * .01, 0, 0, 1);//rotate from centre
          
            //ofTranslate(xCoord, yCoord, zCoord);
                
                
            //int rotationAngle
            
            //image[j].resize(imageSize , imageSize);
                
            image[j].draw(0,0,0);
                
            if(oculusRift.isSetup())
                {
                    ofRectangle viewport = oculusRift.getOculusViewport();
                    ofVec3f sp;
                    sp.x = xCoord+ imageSize/2;
                    sp.y = yCoord ;
                    sp.z = zCoord+ imageSize/2;
                    
                    ofVec3f screenPos = oculusRift.worldToScreen( sp , true);
                    float gazeDist = ofDist(screenPos.x, screenPos.y,viewport.getCenter().x, viewport.getCenter().y);
                    iGazeOver[j] = (gazeDist < 50);
                    //if(iGazeOver[i] ==true)
                      //  cout<<"gaze"<<endl;
                    
                }
                
                    
            ofPopMatrix();
                
            }
        
        i = endImage;
        
    }
    
    ofPopMatrix();
    ofPopStyle();

}




void testApp::drawVideoSphere()
{
    ofPushMatrix();
    ofSpherePrimitive p = ofSpherePrimitive(1500.0,25);
    mesh = p.getMesh();
    
    for(int i = 0; i < mesh.getNumVertices(); i++){
        ofVec2f texCoord = mesh.getTexCoord(i);
        texCoord.x *= videoTexture.getWidth();
        texCoord.y  = (1.0 - texCoord.y) * videoTexture.getHeight();
        mesh.setTexCoord(i, texCoord);
    }
    ofSetColor(255);
    //ofNoFill();
    videoTexture.bind();
    mesh.draw();
    videoTexture.unbind();
    ofPopMatrix();

}


void testApp::drawAllosphere()
{
    
    /*
     ofPushMatrix();
     ofRotate(90, 0, 0, -1);
     ofDrawGridPlane(500.0f, 10.0f, false );
     ofPopMatrix();
     */
    //draw big sphere
    //
    
    ofPushMatrix();
    //ofRotate(ofGetElapsedTimef(), 0, 1,0);
    ofSetColor(0, 140, 200);
    ofNoFill();
    ofSphere(8000);

    //ofSpherePrimitive(500, 100);
    ofPopMatrix();
    ofPushStyle();
    

}

void testApp::drawMesh()
{
    //draw grids
    ofPushMatrix();
    glPointSize(pointSize);
    gridMesh.draw();
    ofPopMatrix();

}


void testApp::loadDatafromText()
{
 
    ofFile file("loadInfo.txt");
    if(file.isFile())
    {
        
        file>>imageFolderName>>imageHead>>grossImageNumber;
        cout<<endl<<"image folder name: "<<imageFolderName<<" the image sequence name is:"<<imageHead <<" number of images: "<< grossImageNumber;
        
    }
    
    
    
}


void testApp::checkOscMessages()
{
    while(receiver.hasWaitingMessages())
    {
        ofxOscMessage message;
        receiver.getNextMessage(&message);
        
        auto addr = message.getAddress();
        cout<<"OSC: "<< addr <<endl;
        
        if ( addr == "/1/showOverlay")
        {
            showOverlay = !showOverlay;
        }
        else if ( addr == "/1/zf")
        {
            zPos+=zSensitivity;
        }
        else if ( addr == "/1/zb")
        {
            zPos-=zSensitivity;
        }
        else if ( addr == "/1/xl")
        {
            xPos+=xSensitivity;
        }
        else if ( addr == "/1/xr")
        {
            xPos-=xSensitivity;
        }
        else if ( addr == "/1/yu")
        {
            yPos+=ySensitivity;
        }
        else if ( addr == "/1/yd")
        {
            yPos-=ySensitivity;
        }
        
        
        else if ( addr == "/2/rs")
        {
            oculusRift.reloadShader();
        }
        else if ( addr == "/2/fs")
        {
            ofToggleFullscreen();

        }
        else if ( addr == "/2/reset")
        {
            oculusRift.reset();
            checkRotation = !checkRotation;
        }
        
        
        
        else if ( addr == "/2/xyz")
        {
            float xs = message.getArgAsFloat(0);
            float ys = message.getArgAsFloat(1);
            float zs = message.getArgAsFloat(2);
            
            xSensitivity = xs;
            ySensitivity = ys;
            zSensitivity = zs;
            
        }
            
        else if ( addr == "/2/ps")
        {
            float ps = message.getArgAsFloat(0);
            pointSize = ps;
            
        }
        
        else if ( addr == "/2/is")
        {
            float is = message.getArgAsFloat(0);
            imageSize= is;
            
        }
        
        else if ( addr == "/2/b")
        {
            drawAVSphere = !drawAVSphere;
            
            
        }
        
        else if ( addr == "/2/n")
        {
            startPlayingAV();
            
        }
        
        else if ( addr == "/2/m")
        {
            pausePlayingAV();
            
            
        }

            
            
                        
    }
}



void testApp::startPlayingAV()
{
    if(video.isLoaded())
        video.play();
    
    if (music.isLoaded())
    {
        music.play();
        music.setPaused(false);
    }
    
}


void testApp::pausePlayingAV()
{
   
    if ( video.isPlaying())
        video.stop();
    
    music.setPaused(true);
    
    
    
}







//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
    

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
 //   cursor2D.set(x, y, cursor2D.z);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
//    cursor2D.set(x, y, cursor2D.z);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
