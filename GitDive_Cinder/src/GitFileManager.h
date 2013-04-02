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
using namespace boost;

class GitFileManager {
public:
    GitFileManager();
    
    //File addition/retrieval
    void addFile(shared_ptr<GitFile> file){ m_fileList.push_back(file); };
    shared_ptr<GitFile> getFileByIndex(int index){ return m_fileList[index]; };
    shared_ptr<GitFile> getFileByName(string fileName);
    
    //File modification
    static void applyDiffToFile(shared_ptr<GitFile>, shared_ptr<Diff> diff );
    
private:
    vector< boost::shared_ptr<GitFile> > m_fileList;
};

#endif /* defined(__GitDive_Cinder__GitFileManager__) */
