/*
glPushMatrix() �� �Լ��� �Ҹ��� ���� ��ȯ ��ǥ�� ������ ���´�.
glPopMatrix() �� ����� glPushMatrix() ������ ��ǥ ���¸� �ٽ� ȣ���Ѵ�.
*/

#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI	3.1415926

int			Width = 800;
int			Height = 800;

float		sun_radius = 50.0;
float		earth_radius = 10.0;
float		moon_radius = 5.0;
float		earthRotation = 0.0, moonRotation = 0.0;
float		earthTransforms = 200.0, moonTransforms = 30.0;

float		earth_rotation_speed = 0.005;
float		moon_rotation_speed = 0.05;


void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0*Width/2.0, Width/2.0, -1.0*Height/2.0, Height/2.0);
}

//	�༺ �׸���
void Draw_Circle(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius*cos(delta*i), c_radius*sin(delta*i));
	glEnd();
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // Set display-window color to black.

	earthRotation += earth_rotation_speed;	
	moonRotation += moon_rotation_speed;

	/***********�ڵ� �ۼ��ϱ� ***************/
	// �¾� : �������� �� 
	glColor3f(1.0, 0.0, 0.0);
	Draw_Circle(sun_radius);
	


	// ���� : �Ķ����� ��
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();	//	�¾��� ��ȯ ��ǥ�� ������ ����
		glRotatef(earthRotation, 0.0, 0.0, 1.0); // �¾� ���ؿ��� earthRotation ��ŭ z�� �������� ȸ�� 
		glTranslatef(earthTransforms, 0.0, 0.0); // �¾��� ��ǥ���� x�ุ +200 �̵�
		Draw_Circle(earth_radius);	//	������ �׸���
	

	// ��   : ������� �� 
		glPushMatrix();	//	������ ��ȯ ��ǥ�� ������ ���� 
			glColor3f(1.0, 1.0, 0.0);
			glRotatef(moonRotation, 0.0, 0.0, 1.0);	// ���� �������� ���� moonRotation ��ŭ z�� �������� ȸ�� 
			glTranslatef(moonTransforms, 0.0, 0.0); // ������ ��ǥ���� x�ุ +30 �̵�
			Draw_Circle(moon_radius);	//	���� �׸���.
		glPopMatrix();	//	���� ��ȯ ��ǥ�� ����
	glPopMatrix();	//	�¾��� ��ȯ ��ǥ�� ����
	glPopMatrix();	//	�¾� ���� ��ȯ ��ǥ�� ���� 

	glFlush();
	glutSwapBuffers();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("�¾�� �¾�-����-��");
	init();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}

