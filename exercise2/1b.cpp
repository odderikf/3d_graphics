#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(0., 0., -8.);
    glColor3f (1.0, 0.0, 0.0);
    glutWireCube(2.);
    glPopMatrix();
    glutSwapBuffers();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    gluPerspective(45.f, 1.0f, 0.1f, 10.f);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 0, 0, 0, -1.0f, 0, 1, 0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("2.1b");
    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}