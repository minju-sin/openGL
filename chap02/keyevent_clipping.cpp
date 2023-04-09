#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI				3.1415926
#define		Window_Width	500
#define		Window_Height	500

int			model_type = GL_POLYGON;
// ���� ����
int			num = 10;
// ������
float		radius = 100;
// ȸ�� �� ����
float		angle = 0.0;
// clipping ����
float		standard_x = -250.0;
float		standard_y = -250.0;
// ���� ����
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
	glRotatef(angle, 0.0, 0.0, 1.0); // ���� ȸ�� 
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

//�簢��
void Modeling_Rectangle(void) {
	glColor3f(0.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0); // ���� ������ �����ϴ� ��ó�� �簢���� �� �߽��� ������ -> �¾��..?

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
	Modeling_Axis();		// x��� y�� 
	Modeling_Rectangle();	// 1��и鿡 �ִ� ���簢�� 
	//Modeling_Axis();		// x��� y�� 
	Modeling_Circle();		// �������� ũ�Ⱑ 100�� ��

	glFlush();
}


void MyKey(unsigned char key, int x, int y) {

	switch (key) {
	// ���� �����ϴ� ������ �� ����
	case 'n':	num += 1;	break;
	case 'm':	num -= 1; 
		if (num < 3) {
			num = 3;
			break;
		}
		break;

	// ���� ũ�� ���� 
	case 'q':	radius += 10;	break;
	case 'w':	radius -= 10;
		if (radius < 10) {
			radius = 10;
			break;
		}
		break;
	// �� ȸ�� 
	case 't':	angle += 0.1;	break;
	case 'y':	angle -= 0.1;	break;
	// ���� ����
	case 'r':	rColor += 0.01;	break;
	case 'g':	gColor += 0.01;	break;
	case 'b':	bColor += 0.01;	break;
	default:	break;
	}
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y) { 
	switch (key) {
	// ���� ��Ÿ���� ��ü�� ��� ��ȭ
	case GLUT_KEY_F1:	model_type = GL_POINTS;		break;	// ��
	case GLUT_KEY_F2:	model_type = GL_LINE_STRIP;	break;	// ����� ����
	case GLUT_KEY_F3:	model_type = GL_LINE_LOOP;		break;	// �������� ������ ���� ����
	case GLUT_KEY_F4:	model_type = GL_LINES;	break;	// �ΰ��� �������� ���� ����
	case GLUT_KEY_F5:	model_type = GL_TRIANGLES;	break;	// �� ���� ������ �ﰢ��
	case GLUT_KEY_F6:	model_type = GL_TRIANGLE_STRIP;	break;	// ����� �ﰢ��
	case GLUT_KEY_F7:	model_type = GL_TRIANGLE_FAN;	break;	// �߽��� �����ϴ� �ﰢ��
	case GLUT_KEY_F8:	model_type = GL_QUADS;	break;	// ���� 4������ �����Ͽ� �簢���� �׸�
	case GLUT_KEY_F9:	model_type = GL_QUAD_STRIP;	break;	// ����� �簢��
	case GLUT_KEY_F10:	model_type = GL_POLYGON;	break;	// ����� ��� �ٰ���

	// ����Ű�� Clipping ���� ��ȭ 
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