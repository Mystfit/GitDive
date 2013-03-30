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
    static void splitTextLines(vector<string> &outStrings, string input, string format){ boost::split(outStrings, input, boost::is_any_of("format")); }
    static void strip(string &input, string search){ boost::replace_all(input, search, ""); }

};

#endif /* defined(__GitDive_Cinder__Utils__) */
