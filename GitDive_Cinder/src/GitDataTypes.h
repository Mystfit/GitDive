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


using namespace std;

class DiffHunk {
public:
    DIffHunk();
    string startRemoveLines;
    string numRemoveLines;
    string startAddLines;
    string numAddLines;
    vector<string> hunkData;
};

class Diff {
public:
    Diff();
    string fileNameA;
    string fileNameB;
    string diffType; //  "default: text";
    string fileMode; // "default: updated";
    vector<DiffHunk> hunkList;
};

class Commit {
public:
    Commit(string commit, string date, string author = "", string message = "");
    string commitHash;
    string author;
    string date;
    string message;
    vector<Diff> diffList;
};



#endif /* defined(__GitDive_Cinder__GitDataTypes__) */




