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

#endif /* defined(__GitDive_Cinder__GitDataTypes__) */

using namespace std;

struct Commit {
    string commitHash;
    string author;
    string date;
    string message;
    vector<Diff> diffList;
};

struct Diff {
    string fileNameA = "";
    string fileNameB = "";
    string diffType = "text";
    string fileMode = "updated";
    string hunkList = []
};

struct DiffHunk {
    
}

