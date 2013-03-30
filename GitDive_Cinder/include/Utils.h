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
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>


namespace io = boost::iostreams;
using namespace std;

class Utils {
public:
    //Returns stdout from a given command
    static string getCmdOutput(const char* command);
    static splitTextLines(string input, vector<string &dest);
};

#endif /* defined(__GitDive_Cinder__Utils__) */
