#include <iostream>

#ifdef PLATFORM_MAC
    #include <SFML/OpenGL.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glext.h>
    #include <stdio.h>
   // #include "hoods.cpp"
#endif
//#include "DisplayMac.cpp"
//#include "header.h"
#include <unistd.h>
#include "classes.cpp"
//#include "DisplayLinux.cpp"
field A(250, 250);
void idle(){

    int width = 250, height = 250, *AMirrow = new int[height*width];
    float n = 0.1;
    A.fill_field(n);

    float x;
    float dx;
    float y;
    float dy;
    while (1)
    {
    // Keep runnin
        
        glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
        for(int i = 0; i < width*height; i++)
            if(!A.lone[i].free)
                AMirrow[i] = 1;
            else
                AMirrow[i] = 0;

        glBegin(GL_QUADS);   // Start drawing quads
        for(int i = 0; i < width*height; i++) {
            if(AMirrow[i] == 1) {  
                               
                x = -1+ 2.*(i%height)/width;
                y = 1- (2.*((float)i / width))/height;
                dx = 2./width;
                dy = 2./height;
                std::cout<< y<<"; ";
                       // Each set of 4 vertices form a quad
                glColor3f(1.0f, 0.0f, 0.0f); // Red
                glVertex2f(x, y);     // Define vertices in counter-clockwise (CCW) order
                glVertex2f(x, y-dy);     //  so that the normal (front-face) is facing you
                glVertex2f(x+dx, y-dy);
                glVertex2f(x+dx, y);            
            }
        }
        glEnd();

        A.sellput(rand()%width, rand()%height);
        usleep(20000);
        A.field_update();
        glFlush();
        // end the current frame
        //display();
    }
    
    //glfwDestroyWindow(window);
    delete[] AMirrow;
}


int main(int argc, char** argv)
{
    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640  , 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Life");
    
    glutDisplayFunc(idle);
    
    glutIdleFunc(idle);
    //glutDisplayFunc(display);
    //glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    glutMainLoop();

    return 0;
}