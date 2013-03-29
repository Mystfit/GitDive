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

struct DiffHunk {
    string startRemoveLines;
    string numRemoveLines;
    string startAddLines;
    string numAddLines;
    vector<string> hunkData;
};

struct Diff {
    string fileNameA;
    string fileNameB;
    string diffType; //  "default: text";
    string fileMode; // "default: updated";
    string hunkList;
};

struct Commit {
    string commitHash;
    string author;
    string date;
    string message;
    vector<Diff> diffList;
};



