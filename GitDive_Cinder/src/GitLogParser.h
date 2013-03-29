//
//  GitLogParser.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#ifndef __GitDive_Cinder__GitLogParser__
#define __GitDive_Cinder__GitLogParser__

#include <iostream>
#include "GitDataTypes.h"

class GitLogParser {
public:
    static vector<Commit> parseLog();
};

#endif /* defined(__GitDive_Cinder__GitLogParser__) */
