//
//  GitDive_CinderApp.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 28/03/13.
//
//

#ifndef GitDive_Cinder_GitDive_CinderApp_h
#define GitDive_Cinder_GitDive_CinderApp_h

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Utils.h"

#include <stdio.h>


using namespace ci;
using namespace ci::app;
using namespace std;

class GitDive_CinderApp : public AppBasic {
public:
	void setup();
	void mouseDown( MouseEvent event );
	void update();
	void draw();
    
    string repoPath;
    string gitCmd;
};

#endif
