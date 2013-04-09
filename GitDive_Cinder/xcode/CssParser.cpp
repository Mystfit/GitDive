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
    
    parseCss(lines);
    
    return lines;
}

int CssParser::getColour(string elem){
    if(m_cssMap[elem]) return m_cssMap[elem];
    return 0;
}


void CssParser::parseCss(vector<string> cssData){
    
    bool insideBlock = false;
    string key;
    string line;
    int colour;
    for(vector<string>::iterator it = cssData.begin(); it != cssData.end(); ++it){
        line = *it;
        
        if(starts_with(line, ".")){
            insideBlock = true;
            string key = line;
            Utils::strip(key, ".{");
            
        } else if(starts_with(line, "}")){
            insideBlock = false;
            m_cssMap[key] = colour;
        }
        
        if(insideBlock){
            if(find_first(line, "color")){
                stringstream colourStr;
                bool foundHash = false;
                int numChars = 0;
                for(int i = 0; i < line.size(); i++){
                    if("#" == line[i]){
                        foundHash = true;
                    }
                    if(foundHash && numChars<6){
                        colourStr << line[i+1];
                        numChars++;
                    }
                }
                colourStr >> std::hex >> colour;
                cout << "LOADED COLOUR:" << colourStr.str() << endl;
            }
        }
    }
}