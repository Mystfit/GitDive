//
//  GitDataTypes.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#include "GitDataTypes.h"

Line::Line(string lineStr){
    m_lineStr = lineStr;
    
    if(lineStr.compare(0, 1, "+") == 0){
        m_lineState = LINE_ADDED;
        m_lineStr.erase(0,1);
    }
    else if(lineStr.compare(0, 1, "-") == 0){
        m_lineState = LINE_DELETED;
        m_lineStr.erase(0,1);
    }
    else{
        m_lineState = LINE_NORMAL;
    }    
}

Commit::Commit(string _commit, string _date, string _author, string _message){
    commitHash = _commit;
    date = _date;
    author = _author;
    message = _message;
}

Diff::Diff(){
    fileType = Diff::FILETYPE_TEXT;
    fileMode = Diff::FILEMODE_UPDATED;
}


int Diff::getNumDeltaLines(){
    int addLines = 0;
    int removeLines = 0;
    
    for(int i = 0; i < m_hunkList.size(); i++){
        for(int j = 0; j < m_hunkList[i]->getNumLines(); j++){
            Line cLine = m_hunkList[i]->getLine(j);
            
            if(cLine.getLineState() == Line::LINE_ADDED) addLines++;
            else if(cLine.getLineState() == Line::LINE_DELETED) removeLines++;
        }
    }
    
    return addLines - removeLines;
}

vector<Line> Diff::getAllDeltaLines(){
    
    vector<Line> deltaLineList;
    
    for(int i = 0; i < m_hunkList.size(); i++){
        boost::shared_ptr<DiffHunk> diffHunk = m_hunkList[i];
        
        for(int j = 0; j < diffHunk->getNumLines(); j++)
        {
            deltaLineList.push_back(diffHunk->getLine(j));

        }
    }
    
    return deltaLineList;
}


void Diff::updateDeltaLists(){
    vector<Line> originalLines = getAllDeltaLines();
    
    m_deltaAddLines.clear();
    m_deltaRemoveLines.clear();
    
    for(int i = 0; i < originalLines.size(); i++){
        if(originalLines[i].getLineState() == Line::LINE_ADDED) m_deltaAddLines.push_back(originalLines[i]);
        else if(originalLines[i].getLineState() == Line::LINE_DELETED) m_deltaRemoveLines.push_back(originalLines[i]);
    }
}



DiffHunk::DiffHunk(){
    m_linePos = 0;
}

GitFile::GitFile(string filename){
    m_filename = filename;
    bIsActive = true;
}