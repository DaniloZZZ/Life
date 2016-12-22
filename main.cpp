#include <iostream>
#include <math.h>
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
int width = 250, height = 250;
float x;
float dx;
float y;
float dy;
float n = 0.1;

void idle(){        
    int *AMirrow = new int[height*width];
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
                       // Each set of 4 vertices form a quad
                if (A.lone[i].guest != nullptr) {
                glColor3f( (4./ log(pow(2.71, 4) +(A.lone[i].guest->params.age))),
                  log(1 + (A.lone[i].guest->params.age))/10.,
                   0.0f); // Blue
                }
                if (A.lone[i].hunter != nullptr){
                   glColor3f( log(1 +(A.lone[i].hunter->params.age))/10.,
                  (4./ log(pow(2.71, 4) +(A.lone[i].hunter->params.age))),
                   0.0f); 
     
                }
            
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
        //display()
    delete[] AMirrow;
}

void  DisplayLinux(int argc, char** argv){
    A.fill_field(n,1000);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640  , 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Life");    
    glutDisplayFunc(idle);    
    glutIdleFunc(idle);
    //glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    glutMainLoop();
    
}
int main(int argc, char** argv)
{
    DisplayLinux(argc,argv);

    return 0;
}