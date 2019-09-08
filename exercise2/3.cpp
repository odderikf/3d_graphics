#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <string>

int i = 03;

void display()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);

    glPushMatrix();
    switch(i){
    case 0: default:
            gluLookAt(0, 0, 0, 0, 0, -1.0f, 0, 1, 0);
            break;
        case 1:
            gluLookAt(1.6, 0, 0, 1.5, 0, -1.0f, 0, 1, 0);
            break;
        case 2:
            gluLookAt(0, 0, 0, 0.2, 0, -1.0f, 0, 1, 0);
            break;
    }
    glTranslated(0., 0., -18.);
    glutWireCube(2.);
    glPopMatrix();
    glutSwapBuffers();

}

void keyboard(unsigned char key, int, int){
    switch(key) {
        case '1':
            i = 0;
            break;
        case '2':
            i = 1;
            break;
        case '3':
            i = 2;
            break;

        default:break;
    }
    display();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    gluPerspective(45.f, 1.0f, 0.1f, 50.f);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("2.3");
    init();
    display();
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}