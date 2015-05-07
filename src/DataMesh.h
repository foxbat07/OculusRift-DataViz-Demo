//
//  DataMesh.h
//  OculusRiftDataVizDemo
//
//  Created by Mohit Hingorani on 1/25/15.
//
//

#ifndef __OculusRiftDataVizDemo__DataMesh__
#define __OculusRiftDataVizDemo__DataMesh__

#include <iostream>
#include "ofMesh.h"
#include "ofPolyline.h"
#include "ofGraphics.h"


#endif /* defined(__OculusRiftDataVizDemo__DataMesh__) */


class DataMesh {
                 public:
                 ofMesh Mesh;
                 ofPolyline dataLine;
                 //ofPath dataLine;
    
                 int daysCheckedOut;
                 float deweyClass;
    
                 int coutYear;
                 int coutMonth;
                 int coutDay;
                 int coutHour;
                 int coutMinute;
    
    
                int cinYear;
                int cinMonth;
                int cinDay;
                int cinHour;
                int cinMinute;
    
                string title;
    
                int dayAdjust  = 15 ;
                int timeAdjust = 12;
                int deweyAdjust = 500;
    
    
                float frontPoly =0;
                float backPoly = 0;
                float polyIndexSize = 100;
                ofVec3f coutPosition;
                ofVec3f cinPosition;
    
    
                void getCoutData( int coutMonth, int coutDay,int coutHour, int coutMinute );

    
                void getCinData( int cinMonth, int cinDay,int cinHour, int cinMinute );
    
                void getTitle( string title);
    
                void getCommonData ( int daysCheckedOut,float deweyClass);
    
    
                bool mouseOver;
                bool gazeOver;
    
    
                void createMesh();
                void drawMesh();
    
                void createCoutPosition();
                void createCinPosition();
                void createPolyline();
    
                void animatePolyline();
    
    
    
    
    
    
   
    
};
