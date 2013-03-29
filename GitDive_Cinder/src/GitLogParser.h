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
#include "GitDataTypes.h"

class GitLogParser {
public:
    //Parses entire git log into commit objects
    static vector<Commit> parseLog(vector<string> diffLog);
    
    //Parses individual commit datablock into diffs
    vector<Diff> parseCommit(vector<string> diffBlock);
    
    string serializeCommit(Commit commit);
};

#endif /* defined(__GitDive_Cinder__GitLogParser__) */
