#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h> 
#include <math.h> // sin cos�Լ��� ����ϱ� ���� ������� 
#define PI 3.1415

int num = 17; // �� 17������ ����� ������ num�� 17�� ����
float radius = 100.0; //������

// ��17�����׸��� �Լ� 
void DrawPolygon(int n) {
	float x, y; 
	float delta; 

	delta = 2 * PI / n;
	
	glColor3f(1.0, 1.0, 0.0); // ����� 
	glBegin(GL_POLYGON); // �� 17���� ���� ��ĥ�ϱ� 
	for (int i = 0; i < n; i++) { // 17�����̹Ƿ� 17�� �ݺ������� ���� 

		x = 250.0 + radius * cos(delta * i);
		y = 250.0 + radius * sin(delta * i);
		glVertex2f(x, y);
	}
	glEnd();
}

// ������ �׸��� ���� ��ǥ�� �׸��� �Լ�
void Display(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0); //������ ������ 
	glClear(GL_COLOR_BUFFER_BIT); // �������� ���������� ���� (������ �ٲٸ� �ȵ�)
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); // ����� ������ķ� �ʱ�ȭ �� �� ��� -> ���ϴ� ��ġ�� �׸��� �׸��� ���� ���
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);

	glColor3f(1.0, 0.0, 0.0); // ������ 
	glBegin(GL_LINES); // x�� �׸��� 
	glVertex2i(0, 250);
	glVertex2i(500, 250);
	glEnd();
	
	glColor3f(0.0, 0.0, 1.0); // �Ķ��� 
	glBegin(GL_LINES); // y�� �� �׸��� 
	glVertex2i(250, 0);
	glVertex2i(250, 500); 
	glEnd();
	DrawPolygon(num); 
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(400, 400); // â�� ��ġ ����
	glutInitWindowSize(500, 500); // â�� ũ�� ���� 
	glutCreateWindow("��17���� �����");
	glutDisplayFunc(Display);
	glutMainLoop();
}
