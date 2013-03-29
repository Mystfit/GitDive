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



using namespace std;
using namespace boost::iostreams;

class Utils {
public:
    static string getCmdOutput()
    {
        FILE *cmdStream = popen("pwd", "r");

        if (!cmdStream) return "Command failed";
        
       
        boost::iostreams::file_descriptor_source d(fileno(cmdStream), close_handle);
        boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_source> pstream(d);
        cout << &pstream;
        pclose(cmdStream);
        
        string cmdResult = "End";
             
        return cmdResult;
    }
};

#endif /* defined(__GitDive_Cinder__Utils__) */
