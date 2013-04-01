//
//  GitFileManager.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 1/04/13.
//
//

#ifndef __GitDive_Cinder__GitFileManager__
#define __GitDive_Cinder__GitFileManager__

#include <iostream>
#include <vector>
#include "GitDataTypes.h"

using namespace std;

class GitFileManager {
public:
    GitFileManager();
    
    void addFile(GitFile file);
    boost::shared_ptr<GitFile> getFileByIndex(int index){ return m_fileList[index]; };
    boost::shared_ptr<GitFile> getFileByname(string fileName);
private:
    vector< shared_ptr<GitFile> > m_fileList;
};

#endif /* defined(__GitDive_Cinder__GitFileManager__) */
