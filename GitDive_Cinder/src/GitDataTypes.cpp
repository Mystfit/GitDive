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
    fileType = "text";
    fileMode = "updated";
}

DiffHunk::DiffHunk(){
    m_linePos = 0;
}

GitFile::GitFile(){
    
}