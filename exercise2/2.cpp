#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

double t = 0;
void display()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);
    t += 0.01;
    glPushMatrix();
        glTranslated(-4., 0., -18.);
        glRotated(t, 1, 1, 0);
        glScaled(2., 1., 1.);
        glutWireCube(2.);
    glPopMatrix();

    glPushMatrix();
        glRotated(t, 1, 1, 0);
        glScaled(2., 1., 1.);
        glTranslated(0., 0., -18.);
        glutWireCube(2.);
    glPopMatrix();

    glPushMatrix();
        glTranslated(+4., 0., -18.);
        glScaled(2., 1., 1.);
        glRotated(t, 1, 1, 0);
        glutWireCube(2.);
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    gluPerspective(45.f, 1.0f, 5.f, 30.f);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 0, 0, 0, -1.0f, 0, 1, 0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("2.2");
    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}