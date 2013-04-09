//
//  CssParser.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 9/04/13.
//
//

#ifndef __GitDive_Cinder__CssParser__
#define __GitDive_Cinder__CssParser__

#include <iostream>
#include <fstream>
#include <map>
#include "Utils.h"

class CssParser {
public:
    CssParser();
    void loadFile(string path);
    void parseCss(string cssData);
private:
    
};

#endif /* defined(__GitDive_Cinder__CssParser__) */
