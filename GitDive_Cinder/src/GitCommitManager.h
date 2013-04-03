//
//  GitCommitManager.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 3/04/13.
//
//

#ifndef __GitDive_Cinder__GitCommitManager__
#define __GitDive_Cinder__GitCommitManager__

#include "GitDataTypes.h"

class GitCommitManager {
public:
    GitCommitManager();
    
    
    
    
    boost::shared_ptr< vector<Commit> > m_commitList;
    int m_commitIndex;
};

#endif /* defined(__GitDive_Cinder__GitCommitManager__) */
