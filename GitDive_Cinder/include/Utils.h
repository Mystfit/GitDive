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

class Utils {
public:
    
    typedef boost::iostreams::stream<boost::iostreams::file_descriptor_sink> boost_stream;
    
    string getCmdOutput()
    {
        FILE *cmdStream;
        // make sure to popen and it succeeds
        
        boost_stream stream(fileno(cmdStream));
        stream.set_auto_close(false);
        
        string cmdOutput;
        while(getline(stream, cmdOutput)){
        }
        
        return cmdOutput;
    }
};

#endif /* defined(__GitDive_Cinder__Utils__) */
