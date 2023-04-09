#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)
#include <math.h>

#define	width 			400
#define	height			600
#define	PI				3.1415
#define	polygon_num		30

int		left = -200;
int		bottom = -300;

float	radius = 10.0;
float	zoom = 1.0;

typedef struct _Point {
	float	x;
	float	y;
} Point;
Point circle_center;

void Modeling_Axis(void) {
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x축 
	glVertex2i(0, 0);
	glVertex2i(1.0 * width, 0);

	glColor3f(0.0, 0.0, 1.0); // y축 
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 1.0 * height);
	glEnd();
}

void	Modeling_Circle(Point CC) {
	float	delta;

	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);
	delta = 2 * PI / polygon_num;

	glBegin(GL_POLYGON);
	for (int i = 0; i < polygon_num; i++)
		glVertex2f(CC.x + radius * cos(delta * i), CC.y + radius * sin(delta * i));
	glEnd();
}


void RenderScene(void) {

	glClearColor(1.0, 1.0, 0.0, 0.0); // Set display-window color to Yellow
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//관측 공간을 어떻게 설정해야 하는가?
	gluOrtho2D(left * zoom, (left + width) * zoom, bottom * zoom, (bottom + height) * zoom);

	Modeling_Axis();
	Modeling_Circle(circle_center);

	glFlush();
}


void mouse2(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
		// 확대 -> 관심영역을 줄임 
		zoom *= 0.9;
		left += (x - width / 2) * zoom;
		bottom += -(y - height / 2) * zoom;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) { 
		//축소 -> 관심영역을 늘림 
		zoom *= 1.1;
		left += (x - width / 2) * zoom;
		bottom += -(y - height / 2) * zoom;
	}
	glutPostRedisplay();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Zoom in-out");
	glutDisplayFunc(RenderScene);
	glutMouseFunc(mouse2);
	glutMainLoop();
}