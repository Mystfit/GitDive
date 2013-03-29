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
    static string getCmdOutput(const char* command)
    {
        FILE *cmdStream = popen(command, "r");
        
        if (!cmdStream) return "Command failed";
       
        io::file_descriptor_source d(fileno(cmdStream), io::close_handle);
        
        io::stream_buffer<io::file_descriptor_source> pstream(d);
        //cout << &pstream;
        string cmdResult;
        getline(pstream, cmdResult);

        pclose(cmdStream);
        
        
        //string cmdResult = "End";
             
        return cmdResult;
    }
};

#endif /* defined(__GitDive_Cinder__Utils__) */
