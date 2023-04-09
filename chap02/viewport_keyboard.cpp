#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI				3.1415926
#define		Window_Width	500
#define		Window_Height	500

int			num = 10;
float		radius = 30;



void Modeling_Circle(void) {
	float	delta, theta;
	float	x, y;

	glColor3f(1.0, 1.0, 0.0);
	glPointSize(3.0);
	delta = 2 * PI / num;

	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++) {
		theta = delta * i;
		x = radius * cos(theta);
		y = radius * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void Modeling_Axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-250.0, 0.0);
	glVertex2f(250.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0, -250.0);
	glVertex2f(0, 250.0);
	glEnd();
}

void Modeling_Rectangle(void) {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(100, 100);
	glVertex2i(150, 100);
	glVertex2i(150, 150);
	glVertex2i(100, 150);
	glEnd();
}

void Modeling_Ground(void) {
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(250, 250);
	glVertex2i(-250, 250);
	glVertex2i(-250, -250);
	glVertex2i(250, -250);
	glEnd();
}


void RenderScene(void) {
	glClearColor(0.5, 0.5, 0.5, 0.0);	// 바탕색 회색
	glClear(GL_COLOR_BUFFER_BIT);

	Modeling_Ground();	// 핑크 사각형 
	Modeling_Rectangle();	// 1사분면에 있는 정사각형 
	Modeling_Axis();		// x축과 y축 
	Modeling_Circle();		// 반지름의 크기가 30인 원

	glFlush();	// 위의 값을 넘겨주는 함수 -> 안넘겨주면 빈화면 나타남 
}

void MyReshape(int w, int h) {
	//glViewport(0, 0, w, h); // 화면에 꽉차게 보여줌 
	//glViewport(0, 0, w/2, h/2); // 왼쪽 하단 위치
	glViewport( w/2, 0, w/2, h/2); // 오른쪽 하단 위치 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 / 2.0 * w, 1.0 / 2.0 * w, -1.0 / 2.0 * h, 1.0 / 2.0 * h);
}

// 키보드로 Viewport 변환하는 함수 
void MyKey(unsigned char key, int x, int y) {
	switch (key) {
	case '0' :	glViewport(0,				0,					Window_Width,	Window_Height);	// 화면에 꽉차게 보여줌
				break;
	case '1' :	glViewport(0,				0,					Window_Width/2, Window_Height/2); //  좌측 하단에 위치 
				break;
	case '2' :	glViewport(Window_Width/2,	0,					Window_Width/2,	Window_Height/2);	// 우측 하단에 위치 
				break;
	case '3' :	glViewport(Window_Width/2,	Window_Height/2,	Window_Width/2, Window_Height/2);	// 우측 상단 위치 
				break;
	case '4' :	glViewport(0,				Window_Height/2,	Window_Width/2, Window_Height/2);	// 좌측 상단 위치 
				break;
	case '5':	glViewport(Window_Width/4, Window_Height/4,		Window_Width/2, Window_Height/2);	// 중앙 위치 
		break;
	case '6':	glViewport(Window_Width*3/4, Window_Height*3/4, Window_Width / 2, Window_Height / 2);	// 우측 상단을 넘어가는 위치 
		break;
	default:	break;
	}
	glutPostRedisplay();	// 키보드 이벤트를 실행하기 위해 필요한 함수 

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Viewport");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKey);
	glutMainLoop();
	return 0;
}