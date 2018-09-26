#include <GLUT/GLUT.h>
#include <iostream>

void displayTest(){
    glClearColor(1,1,0,0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(0.5,0,0);
    
    glVertex2f(300.0,210.0);
    glVertex2f(340.0,215.0);
    glVertex2f(320.0,250.0);
    
    glEnd();
    
    glFlush();
}

int main(int argc, char *argv[]){
    // this is a change in the repo
    
    glutInit(&argc, argv);
    glutInitWindowSize(640,500);
    glutInitWindowPosition(1,1);
    
    glutCreateWindow("Test");
    
    glutDisplayFunc(displayTest);
    glutMainLoop();
}
