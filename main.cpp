#include <iostream>
#ifdef PLATFORM_MAC
    #include <SFML/OpenGL.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include "DisplayMac.cpp"
#else
    #include "DisplayLinux.cpp"
#endif
#include <unistd.h>
#include "classes.cpp"

int main(int argc, char** argv)
{
    try{
        DisplayMac();
    }
    catch{
        DisplayLinux(int argc, char** argv);
    }
}