//
//  GitFileManager.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 1/04/13.
//
//

#ifndef __GitDive_Cinder__GitFileManager__
#define __GitDive_Cinder__GitFileManager__

#include <fstream>
#include <sstream>
#include "sourcehighlight.h"
#include "GitDataTypes.h"

using namespace std;

class GitFileManager {
public:
    GitFileManager();
    
    //File addition/retrieval
    void updateFilesFromCommit(Commit &commit);
    void addFile(boost::shared_ptr<GitFile> file){ m_fileList.push_back(file); };
    boost::shared_ptr<GitFile> getFileByIndex(int index){ return m_fileList[index]; };
    boost::shared_ptr<GitFile> getFileByName(string fileName);
    
    //Commit traversal
    vector<Commit> & getCommitSource(){ return m_commitList; };
    void setCommitSource(vector<Commit> commitList){ m_commitList = commitList; };
    bool applyNextCommit();
    int getCommitIndex(){ return m_commitIndex; };
    void resetCommitIndex(){ m_commitIndex = 0; };
    
    //File modification
    static void applyDiffToFile(GitFile &file, boost::shared_ptr<Diff> diff );
    
    //File display
    void dumpFileOutput(string path);
    void dumpAllFiles(string path);
    void saveFileToDisk(boost::shared_ptr<GitFile> file, string path);
    string serializeAllFiles();
    string serializeFile(boost::shared_ptr<GitFile> file);
    string colourfyFile(GitFile & file);
    
private:
    srchilite::SourceHighlight m_srcHiglight;

    vector<Commit> m_commitList;
    vector< boost::shared_ptr<GitFile> > m_fileList;
    
    int m_commitIndex;
};

#endif /* defined(__GitDive_Cinder__GitFileManager__) */
