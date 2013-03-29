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
    static string getCmdOutput(string command)
    {
        FILE *cmdStream = popen(command, "r");

        if (!cmdStream) return "Command failed";
       
        io::file_descriptor_source d(fileno(cmdStream), io::close_handle);
        
        io::stream_buffer<io::file_descriptor_source> pstream(d);
        //cout << &pstream;
        pclose(cmdStream);
                     
        return pstream;
    }
};

#endif /* defined(__GitDive_Cinder__Utils__) */
