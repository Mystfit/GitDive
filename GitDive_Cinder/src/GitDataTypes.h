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


/*
 * A single line
 */
class Line {
public:
    
    Line(string lineStr);
    
    string getLineStr(){return m_lineStr;};
    
    enum lineState{LINE_NORMAL = 0, LINE_ADDED, LINE_DELETED};
    void setLineState(int lineState){ m_lineState = lineState; };
    int getLineState(){ return m_lineState; };
    
    int linePos;
    
private:
    int m_lineState;
    string m_lineStr;
};


/*
 * Block of lines inside a Diff
 */
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
    
    int getNumLines(){ return m_hunkData.size(); };
    void addLine(Line line){ m_hunkData.push_back(line); };
    Line getLine(int index){ return m_hunkData[index]; };
    
private:
    string m_preLinePos;
    string m_preBlockSize;
    string m_postLinePos;
    string m_postBlockSize;
    vector<Line> m_hunkData;
};


/*
 * Collection of changes made to one file
 */
class Diff {
public:
    Diff();
    string fileType;
    string fileMode;
    void addDiffHunk(boost::shared_ptr<DiffHunk> hunk){ m_hunkList.push_back(hunk); };
    void setFileNameA(string filename){ m_fileNameA = filename; };
    void setFileNameB(string filename){ m_fileNameB = filename; };
    
    string getFileName(){
        if(m_fileNameB != "/dev/null") return m_fileNameB;
        if(m_fileNameA != "/dev/null") return m_fileNameA;
        return "";
    }
    
    int getNumHunks(){ return m_hunkList.size(); };
    boost::shared_ptr<DiffHunk> getDiffHunk(int index){ return m_hunkList[index]; };

private:
    string m_fileNameA;
    string m_fileNameB;
    vector<boost::shared_ptr< DiffHunk> > m_hunkList;
};


/*
 * All file additions/deletions/changes made in one commit
 */
class Commit {
public:
    Commit(string _commit, string _date, string _author = "", string _message = "");
    string commitHash;
    string author;
    string date;
    string message;
    
    void addDiff(boost::shared_ptr<Diff> diff){ m_diffList.push_back(diff); };
    void addDiffList(vector< boost::shared_ptr<Diff> > diffList){
        for(int i = 0; i < diffList.size(); i++){
            m_diffList.push_back(diffList[i]);
        }
    }
    
    int getNumDiffs(){ return m_diffList.size(); };
    boost::shared_ptr<Diff> getDiff(int index){ return m_diffList[index]; };


private:
    vector< boost::shared_ptr<Diff> > m_diffList;
};



#endif /* defined(__GitDive_Cinder__GitDataTypes__) */