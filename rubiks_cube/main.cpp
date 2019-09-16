#define GLM_ENABLE_EXPERIMENTAL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/string_cast.hpp>

#include <cmath>
#include <initializer_list>
#include <array>
#include <iostream>

double t = 0;
double camera_ang_y = 0;
double camera_ang_xz = 0;
bool is_animating = false;

const double _PERSPECTIVE = 60.0;
const double _CAM_DISTANCE = 8;
const double _CAM_SPEED = 0.1;
const double _NEAR = 2;
const double _FAR = 15.;
const double _ANIM_STEPS = 100;

enum face{
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

glm::dvec3 move_axes[6] = {
        {0, 1, 0}, //U
        {0, -1, 0}, //D
        {0, 0, 1}, //F
        {0, 0, -1}, //B
        {-1, 0, 0}, //L
        {1, 0, 0}, //R
};

glm::dmat4 &turn_face_mat(glm::dmat4 &mat, const face &f, const double &angle = -glm::half_pi<double>()){
    mat = glm::rotate(mat, angle, move_axes[f]);
    return mat;
}

class corner{
private:
    std::array<double, 4> _color_U = {0,0,0,1};
    std::array<double, 4> _color_B = {0,0,0,1};
    std::array<double, 4> _color_R = {0,0,0,1};
    bool piece_animating = false;
    glm::dmat4 _model = glm::dmat4(1.);
    glm::dmat4 animation_target = _model;
    glm::dvec3 animation_axes = {0,0,0};

public:
    corner() = default;

    corner(std::array<std::array<double, 4>, 3> UBRR) :
    _color_U(UBRR[0]), _color_B(UBRR[1]), _color_R(UBRR[2])
    {}

    corner(std::array<std::array<double, 4>, 3> UBRR, std::array<double, 4> initial_rotation) :
            _color_U(UBRR[0]), _color_B(UBRR[1]), _color_R(UBRR[2])
    {
        _model = glm::rotate(_model, initial_rotation[0], {initial_rotation[1], initial_rotation[2], initial_rotation[3]});
    }

    corner(std::array<std::array<double, 4>, 3> UBRR, glm::dmat4 model) :
            _color_U(UBRR[0]), _color_B(UBRR[1]), _color_R(UBRR[2]), _model(model)
    {}

    void animate(glm::dvec3 axes){
        piece_animating = true;

        glm::dvec4 v(1.,1.,-1., 1);
        animation_target = glm::rotate(glm::dmat4(1.), glm::half_pi<double>(), axes) * _model;
        std::cout << glm::to_string(animation_target * v) << std::endl << std::endl;
        animation_axes = axes;
    }

    void display(){
        auto curr_model = _model;
        if(piece_animating) {
            if(is_animating){
                curr_model = glm::rotate(glm::dmat4(1.), t * glm::half_pi<double>(), animation_axes) * _model;
            }
            else {
                _model = animation_target;
                curr_model = _model;
                piece_animating = false;
            }
        }

        glPushMatrix();
            glMultMatrixd( glm::value_ptr( curr_model ) );

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
            glBegin(GL_LINES);
                glVertex3d(0, 0, 0);
                glVertex3d(1.5, 1.5, -1.5);
            glEnd();
        glPopMatrix();
    }
};

std::array<corner *, 8> corners;

std::array<corner *, 8> corner_positions;

void display() {

    glClearColor(0.5, 0.5, 0.5, 1.f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    if(is_animating) {
        t += 1./_ANIM_STEPS;
    }
    if(t >= 1){
        t = 0;
        is_animating = false;
    }
    glm::dvec4 cam_pos = {0, _CAM_DISTANCE*std::sin(camera_ang_y), _CAM_DISTANCE*std::cos(camera_ang_y), 1};
    glm::dmat4 rot_mat(1.);
    rot_mat = glm::rotate(rot_mat, camera_ang_xz, {0, 1, 0});
    cam_pos = rot_mat * cam_pos;
    gluLookAt(cam_pos[0], cam_pos[1], cam_pos[2], 0, 0, 0, 0, 1, 0);


    for (auto c : corners){
        c->display();
    }

    glPointSize(50.f);
    glBegin(GL_POINTS);
    glVertex3d(1.5, 1.5, -1.5);
    glEnd();

    glPopMatrix();
    glutSwapBuffers();

}

void special_input(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            camera_ang_y += _CAM_SPEED;
            break;
        case GLUT_KEY_DOWN:
            camera_ang_y -= _CAM_SPEED;
            break;
        case GLUT_KEY_LEFT:
            camera_ang_xz -= _CAM_SPEED;
            break;
        case GLUT_KEY_RIGHT:
            camera_ang_xz += _CAM_SPEED;
            break;

        default: break;
    }
}

void start_animating_maybe(unsigned char key){
    std::array<int, 4> swap = {0, 0, 0, 0};
    glm::dvec3 axes;
    switch(key) {
        default: return;

        case 'u':
            swap = {3, 0, 1, 2};
            axes = - move_axes[U];
            break;
        case 'U':
            swap = {2, 1, 0, 3};
            axes = move_axes[U];
            break;
        case 'd':
            swap = {7, 4, 5, 6};
            axes = - move_axes[D];
            break;
        case 'D':
            swap = {6, 5, 4, 7};
            axes = move_axes[D];
            break;
        case 'f':
            swap = {2, 1, 6, 5};
            axes = - move_axes[F];
            break;
        case 'F':
            swap = {5, 6, 1, 2};
            axes = move_axes[F];
            break;
        case 'b':
            swap = {0, 3, 4, 7};
            axes = - move_axes[B];
            break;
        case 'B':
            swap = {7, 4, 3, 0};
            axes = move_axes[B];
            break;
        case 'r':
            swap = {1, 0, 7, 6};
            axes = - move_axes[R];
            break;
        case 'R':
            swap = {6, 7, 0, 1};
            axes = move_axes[R];
            break;
        case 'l':
            swap = {3, 2, 5, 4};
            axes = - move_axes[L];
            break;
        case 'L':
            swap = {4,5,2,3};
            axes = move_axes[L];
            break;
    }

    for (auto i : swap){
        corner_positions[i]->animate(axes);
    }
    is_animating = true;
    t = 0;

    corner * temp = corner_positions[swap[3]];
    corner_positions[swap[3]] = corner_positions[swap[2]];
    corner_positions[swap[2]] = corner_positions[swap[1]];
    corner_positions[swap[1]] = corner_positions[swap[0]];
    corner_positions[swap[0]] = temp;

}

void keyboard(unsigned char key, int, int){
    if(not is_animating){
        start_animating_maybe(key);
    }
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

}

void init_cube(){
    glm::dmat4 model(1.);

    corners[0] = new corner({COLOR_U, COLOR_B, COLOR_R}, model);
    turn_face_mat(model, U);
    corners[1] = new corner({COLOR_U, COLOR_R, COLOR_F}, model);
    turn_face_mat(model, U);
    corners[2] = new corner({COLOR_U, COLOR_F, COLOR_L}, model);
    turn_face_mat(model, U);
    corners[3] = new corner({COLOR_U, COLOR_L, COLOR_B}, model);

    model = glm::dmat4(1.);
    model = glm::rotate(model, -glm::pi<double>(), {0, 0, 1});

    corners[4] = new corner({COLOR_D, COLOR_B, COLOR_L}, model);
    turn_face_mat(model, U);
    corners[5] = new corner({COLOR_D, COLOR_L, COLOR_F}, model);
    turn_face_mat(model, U);
    corners[6] = new corner({COLOR_D, COLOR_F, COLOR_R}, model);
    turn_face_mat(model, U);
    corners[7] = new corner({COLOR_D, COLOR_R, COLOR_B}, model);

    for(int i = 0; i < corners.size(); ++i){
        corner_positions[i] = corners[i];
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
    glutSpecialFunc(special_input);
    glutReshapeFunc(reshape);

    glutIdleFunc(display);
    reshape(800, 800);
    glutMainLoop();

    for (auto c : corners){
        delete c;
    }

    return 0;
}