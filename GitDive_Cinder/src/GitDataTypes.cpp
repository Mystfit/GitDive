//
//  GitDataTypes.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#include "GitDataTypes.h"


Commit::Commit(string commit, string date, string author, string message){
    commitHash = commit;
}

Diff::Diff(){
    diffType = "text";
    fileMode = "updated";
}

DiffHunk::DiffHunk(){
    
}