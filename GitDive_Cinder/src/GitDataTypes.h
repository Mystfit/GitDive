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
        
    void setPreChangedLines(int linePos, int numLines){
        m_startAddLines = linePos;
        m_numAddLines = numLines;
    };
    
    void setPostChangedLines(int linePos, int numLines){
        m_startRemoveLines = linePos;
        m_numRemoveLines = numLines;
    }
    
private:
    string m_startRemoveLines;
    string m_numRemoveLines;
    string m_startAddLines;
    string m_numAddLines;

    vector<string> m_hunkData;
};

class Diff {
public:
    Diff();
    string diffType; //  "default: text";
    string fileMode; // "default: updated";
private:
    string m_fileNameA;
    string m_fileNameB;
private:
    vector<DiffHunk> m_hunkList;
};

class Commit {
public:
    Commit(string _commit, string _date, string _author = "", string _message = "");
    string commitHash;
    string author;
    string date;
    string message;
private:
    vector<Diff> m_diffList;
};



#endif /* defined(__GitDive_Cinder__GitDataTypes__) */




