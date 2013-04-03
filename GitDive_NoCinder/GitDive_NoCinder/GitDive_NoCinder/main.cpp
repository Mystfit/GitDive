//
//  main.cpp
//  GitDive_NoCinder
//
//  Created by Byron Mallett on 3/04/13.
//  Copyright (c) 2013 Byron Mallett. All rights reserved.
//

#include <iostream>
#include "Utils.h"
#include "GitLogParser.h"
#include "GitFileManager.h"

#include <fstream>
#include <stdio.h>

int main(int argc, const char * argv[])
{
    string repoPath;
    string gitCmd;
    GitFileManager fManager;
    vector<Commit> commitList;
    
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
    ofstream fileOutput;
    
    diffOutput.open("/Users/mystfit/desktop/cinderDiffOut.log");
    fileOutput.open("/Users/mystfit/desktop/cinderFileOut.log");
    
    for(int i = 0; i < commitList.size(); i++) {
        diffOutput << GitLogParser::serializeCommit(commitList[i]);
    }
    
    fileOutput << fManager.serializeAllFiles();
    
    //Close the file
    diffOutput.close();
    fileOutput.close();

    return 0;
}

