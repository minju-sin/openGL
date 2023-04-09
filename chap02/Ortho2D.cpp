#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define PI 3.1415926
#define Window_Width 500 
#define Window_Height 500

int viewing_width = 500;
int viewing_height = 500;
int viewport_width = Window_Width; 
int viewport_height = Window_Height; 
int num = 10;
float radius = 30;

void init(void) {
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, 250, -250, 250);
}

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}

// 원에 가까운 노란색 다각형을 그리는 함수 
void Draw_Circle(void) {
	float delta;
	glColor3f(1.0, 1.0, 0.0); // 노란색 
	delta = 2 * PI / num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(radius * cos(delta * i), radius * sin(delta * i)); glEnd();
}

void MyDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT); 
	glClearColor(1.0, 1.0, 0.0, 0.0); 

	glColor3f(0.2, 0.2, 0.2); //회색 전체 배경 
	glBegin(GL_POLYGON);
	glVertex2f(-250.0, -250.0); 
	glVertex2f(250.0, -250.0);
	glVertex2f(250.0, 250.0);
	glVertex2f(-250.0, 250.0); 
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x축 빨간색 선 
	glVertex2f(-250.0, 0.0);
	glVertex2f(250.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // y축 파란색 선 
	glVertex2f(0, -250.0);
	glVertex2f(0, 250.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0); //초란색 사각형 
	glBegin(GL_POLYGON);
	glVertex2i(100, 100);
	glVertex2i(150, 100);
	glVertex2i(150, 150);
	glVertex2i(100, 150);
	glEnd();

	Draw_Circle();
	glFlush();
	glutSwapBuffers();
}

//키보드 입력 
void MyKey(unsigned char key, int x, int y) {
	switch (key) {
	case 'n': num += 1; break; // 오각형 -> 육각형 -> 칠각형 -> n각형 순으로 증가!
	case 'm': num -= 1; // 오각형 -> 사각형 -> 삼각형 순으로 감소!
		if (num < 3)
			num = 3; break; // 삼각형 이하로 도형이 나타나지 않음 
	case 'a': radius += 1.0; break; // 반지름 1.0 증가 
	case 's':radius -= 1.0; break; // 반지름 1.0 감소 
	default: break;
	} 
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("N-Polygon & Scaling");
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	//glutKeyboardFunc(MyKey);
	glutMainLoop();
}