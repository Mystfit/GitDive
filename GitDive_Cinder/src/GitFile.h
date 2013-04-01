//
//  GitFile.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 1/04/13.
//
//

#ifndef __GitDive_Cinder__GitFile__
#define __GitDive_Cinder__GitFile__

#include <iostream>
#include <vector>

class GitFile {
public:
    GitFile();
private:
    vector<string> m_activeLines;
};

#endif /* defined(__GitDive_Cinder__GitFile__) */
