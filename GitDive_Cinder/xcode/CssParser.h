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
#include <sstream>
#include <map>
#include "Utils.h"
#include "cinder/Color.h"

using namespace boost;

class CssParser {
public:
    CssParser();
    vector<string> loadFile(string path);
    int getColour(string elem);
    void parseCss(vector<string> cssData);
        
private:
    map<string, string> m_cssMap;
    bool bIsLoaded;
};

#endif /* defined(__GitDive_Cinder__CssParser__) */
