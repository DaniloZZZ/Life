//#include <OpnGl.cpp>

#include "classes.cpp"
#include <unistd.h>
#include <iostream>
#include <GL/glew.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdio.h>


int  DisplayLinux(int argc, char** argv){
    //glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640  , 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Life");
    //glutDisplayFunc(display);
    //glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    //glutMainLoop();

    int width = 250, height = 250, *AMirrow = new int[height*width];
    field A(height, width);
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
                x = -1+ 2*(i%height);
                y = 1+ (2*(int)((float)i / width));
                dx = 2./width;
                dy = 2./height;
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
        // end the current frame
        //display();
    }
    
    //glfwDestroyWindow(window);
    delete[] AMirrow;
    return 0;
}
