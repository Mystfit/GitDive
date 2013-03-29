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

class Utils {
public:
    string getCmdOutput()
    {
        typedef boost::iostreams::stream<boost::iostreams::file_descriptor_sink>
        boost_stream;
        
        FILE *myfile;
        // make sure to popen and it succeeds
        boost_stream stream(fileno(myfile));
        stream.set_auto_close(false); // https://svn.boost.org/trac/boost/ticket/3517
        std::string mystring;
        while(std::getline(stream,mystring))
    }
};

#endif /* defined(__GitDive_Cinder__Utils__) */
