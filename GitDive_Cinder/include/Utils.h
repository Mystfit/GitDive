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
    static void strip(string &input, string search){ boost::replace_all(input, search, ""); }
    static string checkStrIndexInRange(vector<string> &strs, int index);
    static string checkIndexInRange(vector<string> &strs, int index);
};

#endif /* defined(__GitDive_Cinder__Utils__) */
