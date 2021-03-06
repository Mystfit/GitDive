//
//  Utils.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#include "Utils.h"

string Utils::getCmdOutput(const char* command)
{
    FILE *cmdStream = popen(command, "r");
    
    if (!cmdStream) return "Command failed";
    
    io::file_descriptor_source d(fileno(cmdStream), io::close_handle);
    
    io::stream_buffer<io::file_descriptor_source> pstream(d);
    istream in(&pstream);
    
    string cmdResult = "";
    string line;
    
    while(in){
        getline(in, line);
        cmdResult += line + "\n";
    }
    
    pclose(cmdStream);
    
    return cmdResult;
}


string Utils::checkStrIndexInRange(vector<string> &strs, int index, bool padZero)
{
    if(index < strs.size()) return strs[index];
    if(padZero) return "0";
    return "";
}




