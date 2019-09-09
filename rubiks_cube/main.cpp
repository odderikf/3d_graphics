#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <initializer_list>
#include <array>

double t = 0;

const double _PERSPECTIVE = 60.0;
const double _CAM_DISTANCE = 8;
const double _NEAR = 2;
const double _FAR = 15.;

enum sticker{
    U = 0,
    D = 1,
    F = 2,
    B = 3,
    L = 4,
    R = 5
};

std::array<double, 4> COLOR_U = {1.0, 1.0, 1.0, 1.0}; //white
std::array<double, 4> COLOR_D = {1.0, 1.0, 0.0, 1.0}; //yellow
std::array<double, 4> COLOR_F = {0.0, 1.0, 0.0, 1.0}; //green
std::array<double, 4> COLOR_B = {0.0, 0.0, 1.0, 1.0}; //blue
std::array<double, 4> COLOR_L = {1.0, 0.5, 0.0, 1.0}; //orange
std::array<double, 4> COLOR_R = {1.0, 0.0, 0.0, 1.0}; //red
std::array<double, 4> COLOR_INTERNAL = {0.0, 0.0, 0.0, 1.0}; //black

std::array<double, 4> ROTATION3d_NONE = {0.0, 0.0, 1.0, 0.0};
std::array<double, 4> ROTATION3d_U = {-90.0, 0.0, 1.0, 0.0};
std::array<double, 4> ROTATION3d_U2 = {-180.0, 0.0, 1.0, 0.0};
std::array<double, 4> ROTATION3d_U3 = {-270.0, 0.0, 1.0, 0.0};
std::array<double, 4> ROTATION3d_Z2 = {180.0, 0.0, 0.0, 1.0};
std::array<double, 4> ROTATION3d_Z2_U = {180.0, 0.0, 0.0, 1.0};

class corner{
private:
    std::array<double, 4> _color_U = {0,0,0,1};
    std::array<double, 4> _color_B = {0,0,0,1};
    std::array<double, 4> _color_R = {0,0,0,1};
    std::array<double, 4> _prerotate = {0,0,1,0};
    int rotation = 0;

public:
    corner() = default;

    corner(std::array<std::array<double, 4>, 3> UBRR) :
    _color_U(UBRR[0]), _color_B(UBRR[1]), _color_R(UBRR[2])
    {}

    corner(std::array<std::array<double, 4>, 3> UBRR, std::array<double, 4> prerotate) :
            _color_U(UBRR[0]), _color_B(UBRR[1]), _color_R(UBRR[2]), _prerotate(prerotate)
    {}


    void rotate(int amount){
        rotation += amount + 3;
        rotation %= 3;
    }

    void display(){
        glPushMatrix();

        if(rotation == 1) glRotated(-120, 1, 1, -1);
        if(rotation == 2) glRotated(-240, 1, 1, -1);

        glRotated(_prerotate[0], _prerotate[1], _prerotate[2], _prerotate[3]);
        glColor4dv(_color_U.data());
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3d(0, 1, 0);
            glVertex3d(1.5, 1.5, -1.5);
            glVertex3d(1.5, 1.5, -0.5);
            glVertex3d(0.5, 1.5, -1.5);
            glVertex3d(0.5, 1.5, -0.5);
        glEnd();

        glColor4dv(_color_B.data());
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3d(0, 0, -1);
            glVertex3d(1.5, 1.5, -1.5);
            glVertex3d(0.5, 1.5, -1.5);
            glVertex3d(1.5, 0.5, -1.5);
            glVertex3d(0.5, 0.5, -1.5);
        glEnd();

        glColor4dv(_color_R.data());
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3d(1, 0, 0);
            glVertex3d(1.5, 1.5, -1.5);
            glVertex3d(1.5, 0.5, -1.5);
            glVertex3d(1.5, 1.5, -0.5);
            glVertex3d(1.5, 0.5, -0.5);
        glEnd();

        glColor4dv(COLOR_INTERNAL.data());
        glBegin(GL_TRIANGLE_FAN);
            glNormal3d(-1, 0, 0);
            glVertex3d(0.5, 0.5, -0.5);
            glVertex3d(0.5, 0.5, -1.5);
            glVertex3d(0.5, 1.5, -1.5);
            glVertex3d(0.5, 1.5, -0.5);
            glNormal3d(0, 0, 1);
            glVertex3d(1.5, 1.5, -0.5);
            glVertex3d(1.5, 0.5, -0.5);
            glNormal3d(0, -1, 0);
            glVertex3d(1.5, 0.5, -1.5);
            glVertex3d(0.5, 0.5, -1.5);
        glEnd();

        glPopMatrix();
    }
};

std::array<corner, 8> corners;

std::array<corner *, 8> corner_positions;

void display() {
    glClearColor(0.5, 0.5, 0.5, 1.f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glTranslated(0, 0, -_CAM_DISTANCE);
    glRotated(t, 1, 1, 0);

    corner_positions[0]->display();
    corner_positions[1]->display();
    glRotated(-90, 0, 1, 0);
    corner_positions[2]->display();
    glRotated(-90, 0, 1, 0);
    corner_positions[3]->display();
    glRotated(-90, 0, 1, 0);

    glRotated(180, 0, 0, 1);

    corner_positions[4]->display();
    glRotated(-90, 0, 1, 0);
    corner_positions[5]->display();
    glRotated(-90, 0, 1, 0);
    corner_positions[6]->display();
    glRotated(-90, 0, 1, 0);
    corner_positions[7]->display();
    glRotated(-90, 0, 1, 0);

    glPopMatrix();
    glutSwapBuffers();

    t += 1;
}

void keyboard(unsigned char key, int, int){
    std::array<int, 4> swap = {0, 0, 0, 0};
    int rotate = 0;
    switch(key) {
        case 'u':
            swap = {3, 0, 1, 2};
            break;
        case 'U':
            swap = {2, 1, 0, 3};
            break;
        case 'd':
            swap = {7, 4, 5, 6};
            break;
        case 'D':
            swap = {6, 5, 4, 7};
            break;
        case 'f':
            swap = {2, 1, 6, 5};
            rotate = 1;
            break;
        case 'F':
            swap = {5, 6, 1, 2};
            rotate = -1;
            break;
        case 'b':
            swap = {0, 3, 4, 7};
            rotate = 1;
            break;
        case 'B':
            swap = {7, 4, 3, 0};
            rotate = -1;
            break;
        case 'r':
            swap = {1, 0, 7, 6};
            rotate = 1;
            break;
        case 'R':
            swap = {6, 7, 0, 1};
            rotate = -1;
            break;
        case 'l':
            swap = {3, 2, 5, 4};
            rotate = 1;
            break;
        case 'L':
            swap = {4,5,2,3};
            rotate = -1;
            break;

        default: break;
    }

    corner_positions[swap[0]]->rotate(rotate);
    corner_positions[swap[1]]->rotate(-rotate);
    corner_positions[swap[2]]->rotate(rotate);
    corner_positions[swap[3]]->rotate(-rotate);

    auto temp = corner_positions[swap[3]];
    corner_positions[swap[3]] = corner_positions[swap[2]];
    corner_positions[swap[2]] = corner_positions[swap[1]];
    corner_positions[swap[1]] = corner_positions[swap[0]];
    corner_positions[swap[0]] = temp;
    display();
}

void reshape(int w, int h){
    if (h==0) h=1;
    double ratio = double(w)/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LEQUAL);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, w, h);
    gluPerspective(_PERSPECTIVE, ratio, _NEAR, _FAR);
    gluLookAt(0, 0, 0, 0, 0, -_CAM_DISTANCE, 0, 1, 0);

    display();
}

void init_cube(){
    corners[0] = corner({COLOR_U, COLOR_B, COLOR_R}, ROTATION3d_NONE);
    corners[1] = corner({COLOR_U, COLOR_R, COLOR_F}, ROTATION3d_U);
    corners[2] = corner({COLOR_U, COLOR_F, COLOR_L});
    corners[3] = corner({COLOR_U, COLOR_L, COLOR_B});

    corners[4] = corner({COLOR_D, COLOR_B, COLOR_L});
    corners[5] = corner({COLOR_D, COLOR_L, COLOR_F});
    corners[6] = corner({COLOR_D, COLOR_F, COLOR_R});
    corners[7] = corner({COLOR_D, COLOR_R, COLOR_B});

    for(int i = 0; i < corners.size(); ++i){
        corner_positions[i] = &corners[i];
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Rubik's Cube");


    init_cube();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    reshape(800, 800);
    glutMainLoop();

    return 0;
}