#include "GitDive_CinderApp.h"



void GitDive_CinderApp::setup()
{
    string repoPath = "/Users/mystfit/Code/Python/Gitdive_Prototypes";
    string gitCmd = "git log --reverse --pretty=format:\"GD_commit|-%H||GD_commitAuthor|-%cn||GD_date|-%cd||GD_message|-%B\"";
    string combinedCmd = "cd " + repoPath + " && " + gitCmd;
    
    vector<string> outputStrings;
    string 
    
    console() << Utils::getCmdOutput(combinedCmd.c_str()) << endl;
    console() << GitLogParser::serializeCommit(Commit("asdasdsa", "asdsadsad")) << endl;
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
