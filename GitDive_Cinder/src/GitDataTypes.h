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

#include "Utils.h"


using namespace std;


class DiffHunk {
public:
    DiffHunk();
        
    void setPreChangedLines(int linePos, int numLines){
        m_preLinePos = linePos;
        m_preBlockSize = numLines;
    };
    
    void setPostChangedLines(int linePos, int numLines){
        m_postLinePos = linePos;
        m_postBlockSize = numLines;
    }
    
    void addLine(string line){ m_hunkData.push_back(line); };
    
private:
    string m_preLinePos;
    string m_preBlockSize;
    string m_postLinePos;
    string m_postBlockSize;
    vector<string> m_hunkData;
};


class Diff {
public:
    Diff();
    string fileType;
    string fileMode;
    void addDiffHunk(boost::shared_ptr<DiffHunk> hunk){ m_hunkList.push_back(hunk); };
    void setFileNameA(string filename){ m_fileNameA = filename; };
    void setFileNameB(string filename){ m_fileNameB = filename; };

private:
    string m_fileNameA;
    string m_fileNameB;
    vector<boost::shared_ptr< DiffHunk> > m_hunkList;
};


class Commit {
public:
    Commit(string _commit, string _date, string _author = "", string _message = "");
    string commitHash;
    string author;
    string date;
    string message;
    
    void addDiff(Diff diff){ m_diffList.push_back(diff); };
    void addDiffList(vector<Diff> diffList){ for(int i = 0; i < diffList.size(); i++) m_diffList.push_back(diffList[i]); }


private:
    vector<boost::shared_ptr< Diff > > m_diffList;
};



#endif /* defined(__GitDive_Cinder__GitDataTypes__) */




