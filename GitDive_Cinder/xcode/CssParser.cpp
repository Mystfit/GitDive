//
//  CssParser.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 9/04/13.
//
//

#include "CssParser.h"

CssParser::CssParser(){
    
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
}


void CssParser::parseCss(string cssData){
    
}