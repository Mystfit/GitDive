//
//  GitLogParser.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#ifndef __GitDive_Cinder__GitLogParser__
#define __GitDive_Cinder__GitLogParser__

#include <iostream>
#include <fstream>
#include <sstream>
#include "GitDataTypes.h"

using namespace boost;

class GitLogParser {
public:
    //Parses entire git log into commit objects
    static boost::shared_ptr< vector<Commit> > parseLog(string logString);
    
    //Parses individual commit datablock into diffs
    static vector< boost::shared_ptr<Diff> > parseCommit(vector<string> diffBlock);
    
    //Converts commit into a pretty string for printing
    static string serializeCommit(Commit commit);
    
    //Dumps diff output to a text file
    void dumpDiffOutput(vector<Commit> commitList, string path);

};

#endif /* defined(__GitDive_Cinder__GitLogParser__) */
