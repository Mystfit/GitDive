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
    
    typedef boost::iostreams::stream<boost::iostreams::file_descriptor_source> boost_stream;
    
    
    
    static string getCmdOutput()
    {
        FILE *cmdStream = popen("pwd", "r");

        if (!cmdStream) return "Command failed";
        
        
       
        file_descriptor_source d(fileno(cmdStream), close_handle);
        stream_buffer<file_descriptor_source> pstream(d);
        cout << &pstream;
        pclose(cmdStream);
        
        string cmdResult;
        
        cmdResult << pstream;

        

//        char buffer[2048];
//        char *line_p = fgets(buffer, sizeof(buffer), cmdStream);        
        
        return cmdResult;
    }
};

#endif /* defined(__GitDive_Cinder__Utils__) */
