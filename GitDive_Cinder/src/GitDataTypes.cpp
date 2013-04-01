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
}

string Line::getLineStr(){
    if(m_lineState == LINE_ADDED) return "+" + m_lineStr;
    if(m_lineState == LINE_DELETED) return "-" + m_lineStr;
    return m_lineStr;
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
    
}