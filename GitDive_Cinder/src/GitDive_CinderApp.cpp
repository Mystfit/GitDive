#include "GitDive_CinderApp.h"

void GitDive_CinderApp::setup()
{
    string repoPath = "/Users/mystfit/Code/Python/Gitdive_Prototypes";
    string gitCmd = "git log -p --reverse --pretty=format:\"GD_commit&%H^GD_commitAuthor&%cn^GD_date&%cd^GD_message&%B\"";
    string combinedCmd = "cd " + repoPath + " && " + gitCmd;
    
    //Get the output of the git command from stdout as a giant string
    string cmdOutput = Utils::getCmdOutput(combinedCmd.c_str());
    
    //Split string into lines
    vector<string> outputStrings;
    boost::split(outputStrings, cmdOutput, boost::is_any_of("\n"));
    
    //Send lines through the log parser to make commit objects
    commitList = GitLogParser::parseLog(outputStrings);
    
    for(int commitIndex = 0; commitIndex < commitList.size(); commitIndex++){
        fManager.updateFilesFromCommit(commitList[commitIndex]);
    }
        
    //Test of the commit serializer
    ofstream diffOutput;
    ofstream fileoutput;

    diffOutput.open("/Users/mystfit/desktop/cinderDiffOut.log");
    fileOutput.open("/Users/mystfit/desktop/cinderFileOut.log");
    
    for(int i = 0; i < commitList.size(); i++) {
        diffOutput << GitLogParser::serializeCommit(commitList[i]);
    }
    
    fileOutput << fManager.serializeAllFiles();
    
    //Close the file
    diffOutput.close();
    fileOutput.close();

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
