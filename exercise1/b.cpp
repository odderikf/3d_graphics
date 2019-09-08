#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLdouble points[8][3] = {
        0.0, 2.0, 0.0,
        1.5, 1.5, 0.0,
        2.0, 0.0, 0.0,
        1.5, -1.5, 0.0,
        0.0, -2.0, 0.0,
        -1.5, -1.5, 0.0,
        -2.0, 0.0, 0.0,
        -1.5, 1.5, 0.0
};

double width = 4.0;
double height = 4.0;
double buffer = 0.2;

void display()
{

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto p0 = points[0], p1 = points[1], p2 = points[2], p3 = points[3], p4 = points[4], p5 = points[5], p6 = points[6], p7 = points[7];

    glPushMatrix();
    glColor3f (1.0, 0.0, 0.0);
    glTranslated(width/2+buffer, height*3.5, 0.);
    GLenum methodslists[3][3] = {
            {GL_POINTS,       GL_LINES,     GL_LINE_STRIP},
            {GL_LINE_LOOP,    GL_TRIANGLES, GL_TRIANGLE_STRIP},
            {GL_TRIANGLE_FAN, GL_QUADS,     GL_QUAD_STRIP}
    };
    for (auto &methodslist : methodslists) {
        for (unsigned int j : methodslist) {
            glBegin(j);
            {
                glVertex3dv(p0);
                glVertex3dv(p1);
                glVertex3dv(p2);
                glVertex3dv(p3);
                glVertex3dv(p4);
                glVertex3dv(p5);
                glVertex3dv(p6);
                glVertex3dv(p7);
            }
            glEnd();
            glTranslated(width + buffer, 0., 0.);
        }
        glTranslated(-3*(width+buffer), -height - buffer, 0.);
    }

    glBegin(GL_POLYGON);
    {
        glVertex3dv(p0);
        glVertex3dv(p1);
        glVertex3dv(p2);
        glVertex3dv(p3);
        glVertex3dv(p4);
        glVertex3dv(p5);
        glVertex3dv(p6);
        glVertex3dv(p7);
    }
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void init() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glOrtho(0, width*3 + buffer*4, -buffer, height*4 + buffer*5, -1., 1.);
}


int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("1b");
    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}