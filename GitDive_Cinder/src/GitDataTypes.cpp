//
//  GitDataTypes.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#include "GitDataTypes.h"


Commit::Commit(string _commit, string _date, string _author, string _message){
    commitHash = commit;
    date = date;
}

Diff::Diff(){
    diffType = "text";
    fileMode = "updated";
}

DiffHunk::DiffHunk(){
    
}