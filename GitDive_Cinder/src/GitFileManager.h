//
//  GitFileManager.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 1/04/13.
//
//

#ifndef __GitDive_Cinder__GitFileManager__
#define __GitDive_Cinder__GitFileManager__

#include "GitDataTypes.h"

using namespace std;

class GitFileManager {
public:
    GitFileManager();
    
    //File addition/retrieval
    void updateFilesFromCommit(boost::shared_ptr<Commit> commit);
    void addFile(boost::shared_ptr<GitFile> file){ m_fileList.push_back(file); };
    boost::shared_ptr<GitFile> getFileByIndex(int index){ return m_fileList[index]; };
    boost::shared_ptr<GitFile> getFileByName(string fileName);
    
    
    //File modification
    static void applyDiffToFile(boost::shared_ptr<GitFile>, boost::shared_ptr<Diff> diff );
    
    //File display
    string serializeAllFiles();
    string serializeFile(boost::shared_ptr<GitFile> file);

    
private:
    vector< boost::shared_ptr<GitFile> > m_fileList;
};

#endif /* defined(__GitDive_Cinder__GitFileManager__) */
