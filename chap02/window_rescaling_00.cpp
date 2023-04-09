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

	glColor3f(1.0, 1.0, 0.0); //노란색 
	glPointSize(3.0);
	delta = 2 * PI / num;

	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++) {
		theta =  delta * i;
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

void draw_Another(void) {
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(300, -150);
	glVertex2i(500, -150);
	glVertex2i(500, 150);
	glVertex2i(300, 150);
	glEnd();
}




void RenderScene(void) {
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 / 2.0 * Window_Width, 1.0 / 2.0 * Window_Width, -1.0 / 2.0 * Window_Height, 1.0 / 2.0 * Window_Height);
	*/


	Modeling_Rectangle();	// 1사분면에 있는 정사각형 
	Modeling_Axis();		// x축과 y축 
	Modeling_Circle();		// 반지름의 크기가 30인 원
	draw_Another();

	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(-1.0 / 2.0 * w, 1.0 / 2.0 * w, -1.0 / 2.0 * h, 1.0 / 2.0 * h);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Window Rescaling");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}