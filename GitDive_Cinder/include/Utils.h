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


using namespace std;

class Utils {
public:
    
    typedef boost::iostreams::stream<boost::iostreams::file_descriptor_source> boost_stream;
    
    string getCmdOutput()
    {
        FILE *cmdStream = popen("ls", "r");

        if (!cmdStream) return "Command failed";

        boost_stream stream(fileno(cmdStream));
        stream.set_auto_close(false);
        
        string cmdOutput;
        while(getline(stream, cmdOutput));
        
        pclose(cmdStream);
        
        return cmdOutput;
    }
};

#endif /* defined(__GitDive_Cinder__Utils__) */
