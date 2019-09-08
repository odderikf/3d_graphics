#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLdouble points[][3] = {
        {-1, -1, -1},
        {-1, -1, 1},
        {-1, 1, 1},
        {-1, 1, -1},
        {1, -1, -1},
        {1, -1, 1},
        {1, 1, 1},
        {1, 1, -1},
        {1, -1, -1},

};

void display()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(0., 0., -8.);
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    {
        glVertex3dv(points[0]);
        glVertex3dv(points[1]);
        glVertex3dv(points[2]);
        glVertex3dv(points[3]);
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    {
        glVertex3dv(points[4]);
        glVertex3dv(points[5]);
        glVertex3dv(points[6]);
        glVertex3dv(points[7]);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glVertex3dv(points[0]);
        glVertex3dv(points[4]);
        glVertex3dv(points[1]);
        glVertex3dv(points[5]);
        glVertex3dv(points[2]);
        glVertex3dv(points[6]);
        glVertex3dv(points[3]);
        glVertex3dv(points[7]);
    }
    glEnd();
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
    glutCreateWindow ("2.1a");
    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}