//
//  CssParser.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 9/04/13.
//
//

#include "CssParser.h"

CssParser::CssParser(){
    bIsLoaded = false;
}


vector<string> CssParser::loadFile(string path){
    ifstream file;
    string line;
    vector<string> lines;
    
    file.open(path.c_str(), ios::in);
    while(file.good()){
        std::getline(file, line);
        lines.push_back(line);
    }
    
    bIsLoaded = true;
    
    return lines;
}


void CssParser::parseCss(vector<string> cssData){
    
    bool insideBlock = false;
    string key;
    int32_t colour;
    for(vector<string>::iterator it = cssData.begin(); it != cssData.end(); ++it){
        
        if(starts_with(it, ".")){
            insideBlock = true;
            string key = *it;
            Utils::strip(key, ".{");
            
        } else if(starts_with(it, "}")){
            insideBlock = false;
            m_cssMap[key] = colour;
        }
        
        if(insideBlock)
        
    }
    
}