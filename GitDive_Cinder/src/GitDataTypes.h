//
//  GitDataTypes.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#ifndef __GitDive_Cinder__GitDataTypes__
#define __GitDive_Cinder__GitDataTypes__

#include <iostream>
#include <vector>

#endif /* defined(__GitDive_Cinder__GitDataTypes__) */

using namespace std;

struct Diff {
    string fileNameA = "";
    string fileNameB = "";
    string diffType = "text";
    string fileMode = "updated";
    string hunkList;
};

struct Commit {
    string commitHash;
    string author;
    string date;
    string message;
    vector<Diff> diffList;
};



struct DiffHunk {
    
};

