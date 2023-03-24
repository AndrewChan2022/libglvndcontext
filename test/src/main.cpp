//
//  main.cpp
//  test libGLVNDGLContext
//
//  Created by kai chen on 2/8/23.
//

#include    <stdio.h>
#include    <stdlib.h>

extern "C" 
bool test_libglvndglcontext();

int main(int argc, char *argv[]) {

    bool ret = test_libglvndglcontext();

    if(ret) {
        printf("test_libglvndglcontext success\n");
    } else {
        printf("test_libglvndglcontext fail\n");
    }
    
    return 0;
}

