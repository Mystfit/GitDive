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
    return 0xffffff;
}


void CssParser::parseCss(vector<string> cssData){
    
    bool insideBlock = false;
    string key;
    string line;
    int colour;
    for(vector<string>::iterator it = cssData.begin(); it != cssData.end(); ++it){
        line = *it;
        
        if(starts_with(line, ".") || starts_with(line, "body")){
            insideBlock = true;
            key = line;
            if(starts_with(line, "body")) key = CSS_BACKGROUND;
            erase_all(key, ".");
            erase_all(key, " ");
            erase_all(key, "{");
            erase_all(key, "\r");
            erase_all(key, "\n");

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
                    int offset = line.find("#");
                    if(offset != std::string::npos){
                        foundHash = true;
                    }
                    if(foundHash && numChars<6){
                        colourStr << line[i + offset + 1];
                        numChars++;
                    }
                }
                colourStr >> std::hex >> colour;
                cout << "LOADED ELEM:" << key << " COLOUR:" << colourStr.str() << endl;
            }
        }
    }
}