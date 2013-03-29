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
    
    typedef boost::iostreams::stream<boost::iostreams::file_descriptor_source> boost_stream;
    
    string getCmdOutput()
    {
        FILE *cmdStream = popen("ls", "r");

        if (!cmdStream) return "Command failed";

        char buffer[1024];
        char *line_p = fgets(buffer, sizeof(buffer), cmdStream);
        
        pclose(cmdStream);
        
        return line_p;
    }
};

#endif /* defined(__GitDive_Cinder__Utils__) */
