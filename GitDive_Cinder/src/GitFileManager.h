//
//  GitFileManager.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 1/04/13.
//
//

#ifndef __GitDive_Cinder__GitFileManager__
#define __GitDive_Cinder__GitFileManager__

#ifndef DATADIR
#define DATADIR "/usr/local/share/source-highlight"
#endif

#include <fstream>
#include <sstream>


#include "srchilite/formatter.h"
#include "srchilite/formatterparams.h"
#include "srchilite/sourcehighlight.h"
#include "srchilite/langmap.h"
#include "srchilite/langdefmanager.h"
#include "srchilite/regexrulefactory.h"
#include "srchilite/sourcehighlighter.h"
#include "srchilite/formattermanager.h"

#include "GitDataTypes.h"
#include "SyntaxColourListener.h

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
    
    void syntaxParseAllFiles(){ for(int i = 0; i < m_fileList.size(); i++) syntaxParseFile(*(m_fileList[i])); };
    void syntaxParseFile(GitFile &file );
    
private:
    srchilite::SourceHighlight m_srcHiglight;

    vector<Commit> m_commitList;
    vector< boost::shared_ptr<GitFile> > m_fileList;
    
    int m_commitIndex;
};


class InfoFormatter: public srchilite::Formatter {
    /// the language element represented by this formatter
    std::string elem;
    
public:
    InfoFormatter(const std::string &elem_ = "normal") :
    elem(elem_) {
    }
    
    virtual void format(const std::string &s,
                        const srchilite::FormatterParams *params = 0) {
        // do not print anything if normal or string to format is empty
        if (elem != "normal" || !s.size()) {
            std::cout << elem << ": " << s;
            if (params)
                std::cout << ", start: " << params->start;
            std::cout << std::endl;
        }
    }
};

/// shared pointer for InfoFormatter
typedef boost::shared_ptr<InfoFormatter> InfoFormatterPtr;

#endif /* defined(__GitDive_Cinder__GitFileManager__) */
