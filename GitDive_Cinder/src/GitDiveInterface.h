//
//  GitDiveInterface.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 16/04/13.
//
//

#ifndef __GitDive_Cinder__GitDiveInterface__
#define __GitDive_Cinder__GitDiveInterface__

#include <iostream>
#include "cinder/params/Params.h"

class GitDiveInterface : public cinder::params::InterfaceGl {
    void minimize(){
        mBar.get()->g_TwMgr->maximize(mBar.get());
    }
    
    void maximize(){
        
    }
};

#endif /* defined(__GitDive_Cinder__GitDiveInterface__) */
