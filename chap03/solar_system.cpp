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

// �༺ ������
float		sun_radius = 20.0;	// �¾�
float		merkury_radius = 7.0;	// ����
float		venus_radius = 9.0;	// �ݼ�
float		earth_radius = 10.0; // ����
float		moon_radius = 5.0; // ��
float		mars_radius = 8.0;	// ȭ��
float		jupiter_radius = 21.0;	// ��
float		saturn_radius = 17.0;	// �伺
float		uranus_radius = 14.0;	// õ�ռ�
float		neptune_radius = 14.0;	// õ�ռ�

// �༺ ȸ��
float		merkuryRotation = 0.0, venusRotation = 0.0, earthRotation = 0.0, moonRotation = 0.0;
float		marsRotation = 0.0, jupiterRotation = 0.0, saturnRotation = 0.0, uranusRotation = 0.0, neptuneRotation = 0.0;

// �༺ �Ÿ� 
float		merkuryTransforms = 40.0, venusTransforms = 60.0, earthTransforms = 100.0, moonTransforms = 30.0;
float		marsTransforms = 120.0, jupiterTransforms = 200.0, saturnTransforms = 250.0, uranusTransforms = 300.0, neptuneTransforms = 350.0;

// �༺ �ӵ� 
float		merkury_rotation_speed = 0.04;
float		venus_rotation_speed = 0.03;
float		earth_rotation_speed = 0.025;
float		moon_rotation_speed = 0.1;
float		mars_rotation_speed = 0.02;
float		jupiter_rotation_speed = 0.01;
float		saturn_rotation_speed = 0.008;
float		uranus_rotation_speed = 0.005;
float		neptune_rotation_speed = 0.003;


void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 * Width / 2.0, Width / 2.0, -1.0 * Height / 2.0, Height / 2.0);
}

//	�༺ �׸���
void Draw_Circle(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius * cos(delta * i), c_radius * sin(delta * i));
	glEnd();
}
void Solar(float rotation, float transforms, float radius) {
	glRotatef(rotation, 0.0, 0.0, 1.0);	// ���� ��ǥ���� rotation ��ŭ z�� �������� ȸ��
	glTranslatef(transforms, 0.0, 0.0);	// ���� ��ǥ���� x�ุ trabsforms��ŭ �̵�
	Draw_Circle(radius);
}

// �˵� �׸��� 
void Draw_Orbit(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_LINES);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius * cos(delta * i), c_radius * sin(delta * i));
	glEnd();
}
void Orbit(float transforms) {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // �˵� ���� ���
	Draw_Orbit(transforms); // �༺�� �¾� ������ �Ÿ� 
	// ���� �ް� ���� ������ �Ÿ��� �˵� ���������� ����
	glPopMatrix();
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // Set display-window color to black.

	merkuryRotation += merkury_rotation_speed;
	venusRotation += venus_rotation_speed;
	earthRotation += earth_rotation_speed;
	moonRotation += moon_rotation_speed;
	marsRotation += mars_rotation_speed;
	jupiterRotation += jupiter_rotation_speed;
	saturnRotation += saturn_rotation_speed;
	uranusRotation += uranus_rotation_speed;
	neptuneRotation += neptune_rotation_speed;

	/***********�ڵ� �ۼ��ϱ� ***************/
	// �¾� : �������� �� 
	glColor3f(1.0, 0.0, 0.0);
	Draw_Circle(sun_radius);

	// ���� : ȸ�� ��
	glPushMatrix(); // �¾��� ��ȯ ��ǥ ����
	glColor3f(0.5, 0.5, 0.5);
	Solar(merkuryRotation, merkuryTransforms, merkury_radius);
	glPopMatrix(); // �¾� ��ȯ ��ǥ�� ���� 
	// ���� �˵� 
	Orbit(merkuryTransforms);

	// �ݼ� : �ݻ� ��
	glPushMatrix(); // �¾��� ��ȯ ��ǥ ����
	glColor3f(1.0, 0.7, 0.0);
	Solar(venusRotation, venusTransforms, venus_radius);
	glPopMatrix(); // �¾� ��ȯ ��ǥ�� ���� 
	// �ݼ� �˵�
	Orbit(venusTransforms);

	// ���� �˵� 
	Orbit(earthTransforms);
	// ���� : �ϴû��� ��
	glPushMatrix();	//	�¾��� ��ȯ ��ǥ�� ������ ����
	glColor3f(0.0, 1.0, 1.0);
	Solar(earthRotation, earthTransforms, earth_radius);

	// ��   : ������� �� 
	glPushMatrix();	//	������ ��ȯ ��ǥ�� ������ ���� 
	glColor3f(1.0, 1.0, 0.0);
	Solar(moonRotation, moonTransforms, moon_radius);
	glPopMatrix();	//	���� ��ȯ ��ǥ�� ����
	// �� �˵�
	Orbit(moonTransforms);
	glPopMatrix();	//	�¾��� ��ȯ ��ǥ�� ����
	glPopMatrix();	//	�¾� ���� ��ȯ ��ǥ�� ���� 

	// ȭ�� : ��ȫ�� �� 
	glPushMatrix();
	glColor3f(1.0, 0.3, 0.0);
	Solar(marsRotation, marsTransforms, mars_radius);
	glPopMatrix();
	// ȭ�� �˵�
	Orbit(marsTransforms);

	// �� : ����� �� 
	glPushMatrix();
	glColor3f(0.5, 0.4, 1.0);
	Solar(jupiterRotation, jupiterTransforms, jupiter_radius);
	glPopMatrix();
	// �� �˵�
	Orbit(jupiterTransforms);

	// �伺 : ��Ȳ�� �� 
	glPushMatrix();
	glColor3f(1.0, 0.4, 0.0);
	Solar(saturnRotation, saturnTransforms, saturn_radius);
	glPopMatrix();
	// �伺 �˵�
	Orbit(saturnTransforms);

	// õ�ռ� : �Ķ��� �� 
	glPushMatrix();
	glColor3f(0.0, 0.6, 1.0);
	Solar(uranusRotation, uranusTransforms, uranus_radius);
	glPopMatrix();
	// õ�ռ� �˵�
	Orbit(uranusTransforms);

	// �ؿռ� : ���� �� 
	glPushMatrix();
	glColor3f(0.2, 0.0, 0.8);
	Solar(neptuneRotation, neptuneTransforms, neptune_radius);
	glPopMatrix();
	// �ؿռ� �˵�
	Orbit(neptuneTransforms);
	glFlush();
	glutSwapBuffers();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("�¾�� �ùķ��̼�");
	init();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}

