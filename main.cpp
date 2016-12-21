#include <iostream>

#ifdef PLATFORM_MAC
    #include <SFML/OpenGL.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
#else
   // #include "hoods.cpp"
#endif
//#include "DisplayMac.cpp"
//#include "header.h"
#include "classes.cpp"
#include "DisplayLinux.cpp"



int main(int argc, char** argv)
{
    int a;
    
    #ifdef PLATFORM_MAC
      //  a = DisplayMac();
    #else
        a = DisplayLinux(argc,  argv);
    #endif

    return a;
}