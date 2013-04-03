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
    //Commit traversal
    boost::shared_ptr< vector<Commit> > getCommitSource(){ return m_commitList; };
    void setCommitSource(boost::shared_ptr< vector<Commit> > commitList){ m_commitList = commitList; };
    bool applyNextCommit();
    int getCommitIndex(){ return m_commitIndex; };
private:
};

#endif /* defined(__GitDive_Cinder__GitCommitManager__) */
