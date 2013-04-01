//
//  GitDataTypes.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#include "GitDataTypes.h"

Line::Line(string lineStr){
    
    strcmp(lineStr.c_str(), "+");
    if(lineStr.at(0) == "+") m_lineState == LINE_ADDED;
    else if(lineStr.at(0) == "-") m_lineState == LINE_DELETED;
    else m_lineState == LINE_NORMAL;

    
    
    m_lineStr = lineStr;
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