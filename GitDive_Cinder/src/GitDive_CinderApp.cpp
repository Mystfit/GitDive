#include "GitDive_CinderApp.h"



void GitDive_CinderApp::setup()
{
    string repoPath = 
    console() << Utils::getCmdOutput("echo 'hello\nline test\nanotherline' >> test.txt; cat test.txt") << endl;
}

void GitDive_CinderApp::mouseDown( MouseEvent event )
{
}

void GitDive_CinderApp::update()
{
}

void GitDive_CinderApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( GitDive_CinderApp, RendererGl )
