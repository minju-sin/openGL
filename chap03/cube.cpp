#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>

#define   PI   3.1415926
float radius, phi, theta;
float delta_theta, delta_phi;

GLfloat      vertices[][3] = {
      { -1.0, -1.0,  1.0 },      // 0 
      { -1.0,  1.0,  1.0 },      // 1
      { 1.0,  1.0,  1.0 },      // 2
      { 1.0, -1.0,  1.0 },      // 3
      { -1.0, -1.0, -1.0 },      // 4
      { -1.0,  1.0, -1.0 },      // 5
      { 1.0,  1.0, -1.0 },      // 6
      { 1.0, -1.0, -1.0 } };      // 7

GLfloat      colors[][3] = {
      { 1.0, 0.0, 0.0 },         // red 0
      { 0.0, 1.0, 0.0 },         // green 1 
      { 1.0, 1.0, 0.0 },         // yellow 2
      { 1.0, 1.0, 1.0 },         // white 3
      { 0.0, 0.0, 1.0 },         // blue 4
      { 1.0, 0.0, 1.0 } };      // magenta 5


void polygon(int a, int b, int c, int d) {
    glColor3fv(colors[a]);
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}


void cube(void) {
    polygon(2, 3, 7, 6); 
    polygon(3, 0, 4, 7); 
    polygon(4, 5, 6, 7);
    polygon(5, 4, 0, 1); 
    polygon(0, 3, 2, 1);
    polygon(1, 2, 6, 5); 
}



void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // y축의 화각(확대/축소), x축의 폭 ,  z축의 카메라 위치 1.0 부터 20.0까지 보이게 함    
    gluPerspective(60.0, 1.0, 1.0, 20.0);

    // 카메라의 위치에서 좌표계 만큼 화면에 보여주는 함수 ( x,y,z 축의 인자를 받음) 
    //glOrtho(-5.0, 5.0, -5.0, 5.0, -10.0, 10.0);
}


// 은면제거법
void init(void) {
    radius = 5.0;
    phi = 0.5;
    theta = 0.5;
    delta_theta = 0.01;
    delta_phi = 0.01;

    glEnable(GL_DEPTH_TEST);
}

void axis(void) {

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // x축 
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0); // y축 
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    glColor3f(0.0, 0.0, 1.0); // z축 
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
}

void frame_reset(void) {
    glClearColor(0.6, 0.6, 0.6, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void camera(void) {
    float x, y, z;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    x = radius * cos(phi) * cos(theta);
    y = radius * cos(phi) * sin(theta);
    z = radius * sin(phi);

    //gluLookAt(3.0, 4.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}


void display(void)
{
    frame_reset();

    camera();
    axis();
    cube();

    glFlush();
    glutSwapBuffers();
}

void MySpecial(int key, int x, int y) {
    switch (key) {
        // 경도 바꾸기 
    case GLUT_KEY_LEFT:   theta -= delta_theta; break;
    case GLUT_KEY_RIGHT: theta += delta_theta;   break;
        // 위도 바꾸기 
    case GLUT_KEY_UP: phi += delta_phi;   break;
    case GLUT_KEY_DOWN: phi -= delta_phi;   break;

    default:   break;
    }
    glutPostRedisplay(); // event로 바뀐 정보가 전달되어야 함 
}
void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("cube");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
}