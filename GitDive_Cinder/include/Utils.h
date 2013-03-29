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
    
    
    
    static string getCmdOutput()
    {
        FILE *cmdStream = popen("pwd", "r");

        if (!cmdStream) return "Command failed";
        
        
        ifstream p2(fileno(cmdStream));
        
        string s;
        
        p2 >> s;
        
        p2.close();
        

//        char buffer[2048];
//        char *line_p = fgets(buffer, sizeof(buffer), cmdStream);        
//        pclose(cmdStream);
        
        return s;
    }
};

#endif /* defined(__GitDive_Cinder__Utils__) */
