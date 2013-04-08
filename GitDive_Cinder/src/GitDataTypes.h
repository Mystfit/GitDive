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
#include <sstream>
#include <boost/shared_ptr.hpp>
#include "Utils.h"
#include "TextAnimateable.h"


using namespace std;


/*
 * A single line
 */

class LineElement : public TextAnimateable {
public:
    LineElement(string element, string elemStr, int pos)
    {
        elem = element;
        str = elemStr;
        position = pos;
        m_position = cinder::Vec2f((float)position * 10.0f, 0.0f);
    };
    string getStr(){return str;};
    string elem;
    string str;
    int position;
};

class Line : public TextAnimateable {
public:
    
    Line(string lineStr, bool justUpdated = false);
    
    string getStr();
    
    int getLinePos(){ return m_linePos; };
    void setLinePos(int linePos){ m_linePos = linePos; };
    
    void addLineElement(LineElement element);
    vector< LineElement > getLineElements(){ return m_lineElements; };
    
    enum lineState{LINE_NORMAL = 0, LINE_ADDED, LINE_DELETED};
    int getLineState(){ return m_lineState; };
    void setLineState(int state){ m_lineState = state; };
    string getLineStateSymbol(){
        if(m_lineState == LINE_ADDED) return "+";
        if(m_lineState == LINE_DELETED) return "-";
        return " ";
    }
    
    //Line is queued for deletion
    void markForRemoval();
    
private:
    int m_lineState;
    int m_linePos;
    string m_lineStr;
    vector< LineElement > m_lineElements;
};


/*
 * Block of lines inside a Diff
 */
class DiffHunk {
public:
    DiffHunk();
    
    //Methods for storing pre/post line information about the hunk line start and length
    void setPreChangedLines(int linePos, int numLines){
        m_preLinePos = linePos;
        m_preBlockSize = numLines;
    };
    
    void setPostChangedLines(int linePos, int numLines){
        m_postLinePos = linePos;
        m_postBlockSize = numLines;
    }
    
    int getPreBlockStart(){ return m_postLinePos; };
    int getPostBlockStart(){ return m_postLinePos; };
    
    //Line data addition/retrieval
    int getNumLines(){ return m_hunkData.size(); };
    void addLine(Line line){ m_hunkData.push_back(line); };
    Line getLine(int index){ return m_hunkData[index]; };
    
    //Methods for setting/calculating line positions based on the modified line positions
    void setLinePos(int pos){m_linePos = pos; };
    int getLinepos(){return m_linePos; };
    void incrementLinePos(){ m_linePos++; };
    
    //Methods for setting calculating line positions based on the old line positions
    void setOldLinePos(int pos){m_oldLinePos = pos; };
    int getOldLinePos(){return m_oldLinePos; };
    void incrementOldLinePos(){ m_oldLinePos++; };
    
private:
    int m_linePos;
    int m_oldLinePos;
    int m_preLinePos;
    int m_preBlockSize;
    int m_postLinePos;
    int m_postBlockSize;
    vector<Line> m_hunkData;
};


/*
 * Collection of changes made to one file
 */
class Diff {
public:
    Diff();
    
    enum fileTypes {FILETYPE_TEXT = 0, FILETYPE_BINARY };
    int fileType;    
    
    enum fileModes {FILEMODE_ADDED = 0, FILEMODE_DELETED, FILEMODE_UPDATED };
    int fileMode;
    
    void addDiffHunk(boost::shared_ptr<DiffHunk> hunk){ m_hunkList.push_back(hunk); };
    void setFileNameA(string filename){ m_fileNameA = filename; };  //Filename before renaming
    void setFileNameB(string filename){ m_fileNameB = filename; };  //Filename after renaming
    
    //Always returns the renamed file first
    string getFileName(){
        if(m_fileNameB != "/dev/null") return m_fileNameB;
        if(m_fileNameA != "/dev/null") return m_fileNameA;
        return "";
    }
    
    int getNumHunks(){ return m_hunkList.size(); };
    int getNumDeltaLines();
    boost::shared_ptr<DiffHunk> getDiffHunk(int index){ return m_hunkList[index]; };
    
    vector<Line> getAllDeltaLines();
    void updateDeltaLists();
    vector<Line> getDeltaAddLines(){ return m_deltaAddLines; };
    vector<Line> getDeltaRemoveLines(){ return m_deltaRemoveLines; };

private:
    string m_fileNameA;
    string m_fileNameB;
    vector<boost::shared_ptr< DiffHunk> > m_hunkList;
    vector<Line> m_deltaAddLines;
    vector<Line> m_deltaRemoveLines;
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


/*
 * File object constructed from git diff deltas
 */
class GitFile {
public:
    GitFile(string filename);
    
    string getFilename(){ return m_filename; };
    
    //Set active states
    bool active(){ return bIsActive; };
    void setInactive(){ bIsActive = false; };
    void setActive(){ bIsActive = true; };
    
    void setLines(vector< boost::shared_ptr<Line> > lines);
    vector< boost::shared_ptr<Line> > & getLines(){ return m_activeLines; };
    
    void resetLineOrder();
    
    //Syntax highlighting
    string getStr();
    void setColourfulString(string colourfulString){ m_colourfulString = colourfulString; };
    string getColourfulString(string colourfulString){ return m_colourfulString; };
    
private:
    bool bIsActive;
    string m_filename;
    string m_colourfulString;

    vector< boost::shared_ptr<Line> > m_activeLines;
};



/*
 * A a block describing a removed section from a file
 */
struct FileChangeBlock{
    enum fileChangeType {FILECHANGE_ADD = 0, FILECHANGE_DELETE};
    int blockType;
    int blockStart;
    int blockEnd;
};




#endif /* defined(__GitDive_Cinder__GitDataTypes__) */