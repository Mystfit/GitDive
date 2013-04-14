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

#include "srchilite/formatter.h"
#include "srchilite/formatterparams.h"
#include "srchilite/sourcehighlight.h"
#include "srchilite/langmap.h"
#include "srchilite/sourcehighlighter.h"
#include "srchilite/formattermanager.h"

#include "TextRenderer.h"
#include "GitDataTypes.h"
#include "SyntaxColourTools.h"

using namespace std;

class GitFileManager {
public:
    GitFileManager();
    void setTextRenderer( boost::shared_ptr<TextRenderer> tRender ){ m_tRender = tRender; };
    void setFormatterManager(boost::shared_ptr<LineFormatterManager> formatterManager){ m_formatterManager = formatterManager; };
    
    //File addition/retrieval
    //-----------------------
    void updateFilesFromCommit(Commit &commit);
    void addFile(boost::shared_ptr<GitFile> file){ m_fileList.push_back(file); };

    boost::shared_ptr<GitFile> getFileByIndex(int index){ return m_fileList[index]; };
    boost::shared_ptr<GitFile> getFileByName(string fileName);
    
    
    
    //Commit traversal
    //----------------
    
    vector<Commit> & getCommitSource(){ return m_commitList; };
    void setCommitSource(vector<Commit> commitList){ m_commitList = commitList; };
    void reset();
    
    //Moves forward through the commit list and applies diffs to all files
    bool applyNextCommit();
    
    
    
    //File modification
    //-----------------
    
    //Applies a diff to the current state of a file object
    void applyDiffToFile(GitFile &file, boost::shared_ptr<Diff> diff, bool useSyntaxHighlighting);
    
    bool & getSyntaxHighlightStatus(){ return bUseSyntaxHighlighting; };
    void setSyntaxHighlightStatus(bool state){ bUseSyntaxHighlighting = state; };
    
    //File display
    //------------
    
    //Dumps the final file output to a text file
    void dumpFileOutput(string path);
    
    //Save all files at once
    void dumpAllFiles(string path);
    
    //Saves the file to the disk in its original format
    void saveFileToDisk(boost::shared_ptr<GitFile> file, string path);
    
    //Converts all files to strings
    string serializeAllFiles();
    
    //Converts a single file to a string
    string serializeFile(boost::shared_ptr<GitFile> file);
    
    //Converts file to a coloured string
    string colourfyFile(GitFile & file);
    
    //Runs all files through the syntax highlighter to seperate lines into language elements
    void syntaxParseAllFiles();
    
    //Gets syntax from a single file
    void syntaxParseFile(GitFile &file );
    
private:
    srchilite::SourceHighlight m_srcHiglight;

    vector<Commit> m_commitList;
    vector< boost::shared_ptr<GitFile> > m_fileList;
    
    boost::shared_ptr<TextRenderer> m_tRender;
    boost::shared_ptr<LineManager> m_lineManager;
    
    int m_commitIndex;
    bool bUseSyntaxHighlighting;
};

#endif /* defined(__GitDive_Cinder__GitFileManager__) */
