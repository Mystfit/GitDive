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
private:
    vector<GitFile> m_fileList;
};

#endif /* defined(__GitDive_Cinder__GitFileManager__) */
