#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)
#include <math.h>

#define	width 			400
#define	height			600
#define	PI				3.1415
#define	polygon_num		30

int		left = 0;
int		bottom = 0;

int		mouse_motion = 0;

float	radius = 10.0;
float	point[1000][2];
int		point_num = 0;

typedef struct _Point {
	float	x;
	float	y;
} Point;

Point	circle_center;

void Modeling_Axis(void) {
		glLineWidth(2.0);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0); // x축 
			glVertex2i(0, 0);
			glVertex2i(1.0*width, 0);

			glColor3f(0.0, 0.0, 1.0); // y축 
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 1.0*height);
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


void	Modeling_Points_from_Screen(void) {
		glPointSize(5.0);
		glColor3f(0.0, 0.0, 0.0);
	
		glBegin(GL_POINTS);
			for (int k = 0; k < point_num; k++)
				glVertex2f(point[k][0], point[k][1]);
		glEnd();
}

void RenderScene(void) {
	
	glClearColor(1.0, 1.0, 0.0, 0.0); // Set display-window color to Yellow
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//관측 공간을 어떻게 설정해야 하는가?
	//gluOrtho2D(0, width, 0, height); // mouse1()
	gluOrtho2D (left, left+width, bottom, bottom+height); //mouse2()
	
	Modeling_Axis();

	// 제일 마지막으로 입력된 점을 중심으로 하는 원 생성하기
	Modeling_Circle(circle_center);

	// 마우스 왼쪽 버튼 클릭을 통해 얻어진 점 생성하기
	Modeling_Points_from_Screen();

	glFlush();
}


void mouse1(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// 왼쪽 버튼을 누르면 어떤 일을 수행해야 하는가?
		//	점 찍기	-> 점 위치가 마우스를 클릭하면 바뀜 
		point[point_num][0] = x;
		point[point_num][1] = height - y;	// window상(가상세계) y좌표와 모니터에서 y좌표는 반대 
		point_num++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		// 오른쪽 버튼을 누르면 그렸던 점을 삭제
		point_num = 0;
	}
	glutPostRedisplay();
}

void mouse2(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// 관심 영역 이동했을 때, 점 제대로 안찍힘 -> 영역 이동한 것과 같이 이동
		point[point_num][0] = left + x;
		point[point_num][1] = bottom + height - y; // window상(가상세계) y좌표와 모니터에서 y좌표는 반대

		// 빨간 원이 현재 점을 찍은 좌표로 따라옴 
		circle_center.x = point[point_num][0];
		circle_center.y = point[point_num][1];
		point_num++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		point_num = 0;
	}
	glutPostRedisplay();
}

void motion(int x, int y) {
	circle_center.x = left + x;
	circle_center.y = bottom + height - y;
	glutPostRedisplay();
}

void MySpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:		left -= 1.0; break;
	case GLUT_KEY_RIGHT:	left += 1.0; break;
	case GLUT_KEY_DOWN:		bottom -= 1.0; break;
	case GLUT_KEY_UP:		bottom += 1.0; break;
	default:	break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Draw Points by Mouse Input");
	glutDisplayFunc(RenderScene);
	//glutMouseFunc(mouse1);	// mouse event 
	glutMouseFunc(mouse2);
	glutMotionFunc(motion);	// 마우스 움직임을 받아들이는 함수 
	glutSpecialFunc(MySpecial);
	glutMainLoop();
}