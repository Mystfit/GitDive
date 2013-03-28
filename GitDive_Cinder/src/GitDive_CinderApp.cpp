#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GitDive_CinderApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void GitDive_CinderApp::setup()
{
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
