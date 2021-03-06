//
//  Utils.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#ifndef __GitDive_Cinder__Utils__
#define __GitDive_Cinder__Utils__

#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>


namespace io = boost::iostreams;
using namespace std;

class Utils {
public:
    //Returns stdout from a given command
    static string getCmdOutput(const char* command);
    
    //Strips a string from a string
    static void strip(string &input, string search){ boost::replace_all(input, search, ""); }
    
    //Checks that the output from a string vector is not out of bounds
    static string checkStrIndexInRange(vector<string> &strs, int index, bool padZero = false);
};

#endif /* defined(__GitDive_Cinder__Utils__) */
