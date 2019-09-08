#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <string>

double x = 0, y = 0, z = 0, dirx = 0, diry = 0, dirz = -1;

double mspeed = 0.05, camspeed = 0.1;
void display()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);

    glPushMatrix();
        gluLookAt(x, y, z, x+dirx, y+diry, z+dirz, 0, 1, 0);

        glTranslated(0., 0., -18.);
        glutWireCube(2.);

        glTranslated(3., 0., 0.);
        glutWireCube(2.);
    glPopMatrix();
    glutSwapBuffers();

}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    gluPerspective(60.f, 1600.f/900.f, 0.00001f, 100.f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int, int){
    switch(key) {
        case 'w':
            z -= mspeed;
            break;
        case 'a':
            x -= mspeed;
            break;
        case 's':
            z += mspeed;
            break;
        case 'd':
            x += mspeed;
            break;
        case 'q':
            y += mspeed;
            break;
        case 'e':
            y -= mspeed;
            break;

        case 'i':
            diry += camspeed;
            break;
        case 'j':
            dirx += camspeed;
            break;
        case 'k':
            diry -= camspeed;
            break;
        case 'l':
            dirx -= camspeed;
            break;
        case 'u':
            dirz -= camspeed;
            break;
        case 'o':
            dirz += camspeed;
            break;

        default:break;
    }

    display();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (1600, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("2.4");
    init();
    display();
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}