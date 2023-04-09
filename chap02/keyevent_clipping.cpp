#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI				3.1415926
#define		Window_Width	500
#define		Window_Height	500

int			model_type = GL_POLYGON;
// 점의 개수
int			num = 10;
// 반지름
float		radius = 100;
// 회전 각 변수
float		angle = 0.0;
// clipping 변수
float		standard_x = -250.0;
float		standard_y = -250.0;
// 색상 변수
float		rColor = 0.0;
float		gColor = 0.0;
float		bColor = 0.0;

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(standard_x, standard_x + Window_Width, standard_y, standard_y + Window_Height);
	//gluOrtho2D(LEFT,RIGHT,TOP,BOTTOM);
}

void Modeling_Circle(void) {
	float	delta, theta;
	float	x, y;

	glColor3f(rColor, gColor, bColor);
	glPointSize(3.0);
	glRotatef(angle, 0.0, 0.0, 1.0); // 도형 회전 
	delta = 2 * PI / num;

	glBegin(model_type);
	for (int i = 0; i < num; i++) {
		theta = angle + delta * i;
		x = radius * cos(theta);
		y = radius * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void Modeling_Axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-250, 0.0);
	glVertex2f(250, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0, -250);
	glVertex2f(0, 250);
	glEnd();
}

//사각형
void Modeling_Rectangle(void) {
	glColor3f(0.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0); // 지구 주위를 공전하는 달처럼 사각형이 원 중심을 공전함 -> 태양계..?

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
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(standard_x, standard_x + Window_Width, standard_y, standard_y + Window_Height);
	Modeling_Axis();		// x축과 y축 
	Modeling_Rectangle();	// 1사분면에 있는 정사각형 
	//Modeling_Axis();		// x축과 y축 
	Modeling_Circle();		// 반지름의 크기가 100인 원

	glFlush();
}


void MyKey(unsigned char key, int x, int y) {

	switch (key) {
	// 원을 형성하는 선분의 수 조절
	case 'n':	num += 1;	break;
	case 'm':	num -= 1; 
		if (num < 3) {
			num = 3;
			break;
		}
		break;

	// 원의 크기 조정 
	case 'q':	radius += 10;	break;
	case 'w':	radius -= 10;
		if (radius < 10) {
			radius = 10;
			break;
		}
		break;
	// 원 회전 
	case 't':	angle += 0.1;	break;
	case 'y':	angle -= 0.1;	break;
	// 색상 변경
	case 'r':	rColor += 0.01;	break;
	case 'g':	gColor += 0.01;	break;
	case 'b':	bColor += 0.01;	break;
	default:	break;
	}
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y) { 
	switch (key) {
	// 원을 나타내는 물체의 모양 변화
	case GLUT_KEY_F1:	model_type = GL_POINTS;		break;	// 점
	case GLUT_KEY_F2:	model_type = GL_LINE_STRIP;	break;	// 연결된 선분
	case GLUT_KEY_F3:	model_type = GL_LINE_LOOP;		break;	// 시작점과 끝점을 이은 선분
	case GLUT_KEY_F4:	model_type = GL_LINES;	break;	// 두개의 정점들을 이은 선분
	case GLUT_KEY_F5:	model_type = GL_TRIANGLES;	break;	// 세 개씩 연결한 삼각형
	case GLUT_KEY_F6:	model_type = GL_TRIANGLE_STRIP;	break;	// 연결된 삼각형
	case GLUT_KEY_F7:	model_type = GL_TRIANGLE_FAN;	break;	// 중심을 공유하는 삼각형
	case GLUT_KEY_F8:	model_type = GL_QUADS;	break;	// 정점 4개씩을 연결하여 사각형을 그림
	case GLUT_KEY_F9:	model_type = GL_QUAD_STRIP;	break;	// 연결된 사각형
	case GLUT_KEY_F10:	model_type = GL_POLYGON;	break;	// 연결된 블록 다각형

	// 방향키로 Clipping 영역 변화 
	case GLUT_KEY_UP:		standard_y += 1.0;	break;
	case GLUT_KEY_LEFT:		standard_x -= 1.0; break;
	case GLUT_KEY_DOWN:		standard_y -= 1.0; break;
	case GLUT_KEY_RIGHT:	standard_x += 1.0;	break;
	default:	break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("N-Polygon & Keyboard Event");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKey);
	glutSpecialFunc(SpecialKey);
	glutDisplayFunc(RenderScene);
	glutMainLoop();
	return 0;
}