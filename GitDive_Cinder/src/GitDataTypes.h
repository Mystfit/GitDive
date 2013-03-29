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
    DiffHunk();
    string m_startRemoveLines;
    string m_numRemoveLines;
    string m_startAddLines;
    string m_numAddLines;
    vector<string> m_hunkData;
};

class Diff {
public:
    Diff();
private:
    string m_fileNameA;
    string m_fileNameB;
    string m_diffType; //  "default: text";
    string m_fileMode; // "default: updated";
    vector<DiffHunk> m_hunkList;
};

class Commit {
public:
    Commit(string commit, string date, string author = "", string message = "");
    string m_commitHash;
    string m_author;
    string m_date;
    string m_message;
    vector<Diff> diffList;
};



#endif /* defined(__GitDive_Cinder__GitDataTypes__) */




