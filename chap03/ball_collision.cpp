#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)
#include <math.h>

#define   width          400.0
#define   height         600.0
#define   PI            3.1415
#define   polygon_num      50

int      left = 0;
int      bottom = 0;

int      collision_count = 0;

float   radius1, moving_ball_radius, paddle_speed;

typedef struct _Point {
    float   x;
    float   y;
} Point;

Point   fixed_ball, moving_ball, paddle, paddle2, velocity, delta;


void init(void) {
    radius1 = 20.0;
    fixed_ball.x = width / 2;
    fixed_ball.y = height / 2;

    moving_ball_radius = 10.0;
    moving_ball.x = width / 2;
    moving_ball.y = height / 4;

    paddle.x = width / 2.6;
    paddle.y = height / 20;
    paddle2.x = width / 1.6;
    paddle2.y = height / 15;

    velocity.x = 0.05;
    velocity.y = 0.05;
    paddle_speed = 5.0;
    collision_count = 0;
}


void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 관측영역 셋팅
    gluOrtho2D(left, left + width, bottom, bottom + height); // mouse2()
}

// 원 그리는 함수 
void   Modeling_Circle(float radius, Point CC) {
    float   delta;

    delta = 2 * PI / polygon_num;
    glBegin(GL_POLYGON);
    for (int i = 0; i < polygon_num; i++)
        glVertex2f(CC.x + radius * cos(delta * i), CC.y + radius * sin(delta * i));
    glEnd();
}

//  패들 그리는 함수
void Modeling_Paddle(void) {
    glColor3f(0.0, 0.0, 0.0);
    glRectf(paddle.x, paddle.y, paddle2.x, paddle2.y);
}

// Game-Over 화면 출력 함수
void showGameOverScreen() {
    // 화면을 검은색으로 지우기
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 텍스트 색상 지정 (흰색)
    glColor3f(1.0, 1.0, 1.0);
    // 텍스트 출력 위치 지정
    glRasterPos2f(120, height/2);

    // 텍스트 출력
    const char* str = "!GAME OVER!";
    for (int i = 0; str[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }

    // 화면에 출력
    glutSwapBuffers();
}

/// <summary>
/// 공과 공이 충돌하는 함수
/// </summary>
/// <param name=""></param>
void Collision_Detection_Between_Balls(void) {
    float   distance;

    delta.x = moving_ball.x - fixed_ball.x; // x 변화량
    delta.y = moving_ball.y - fixed_ball.y; // y 변화량 
     
    distance = sqrt(pow(delta.x, 2) + pow(delta.y, 2)); // 원과 원 사이의 거리
    if (distance <= radius1 + moving_ball_radius) {
        velocity.y *= -1;
        velocity.x *= -1;
        collision_count++;
    }
}

/// <summary>
/// 공과 벽이 충돌하는 함수
/// </summary>
/// <param name=""></param>
void Collision_Detection_to_Walls(void) {
    float distance_left = moving_ball.x - moving_ball_radius; // left
    float distance_right = moving_ball.x + moving_ball_radius; // right
    float distance_top = moving_ball.y + moving_ball_radius; // top
    float distance_bottom = moving_ball.y - moving_ball_radius; // bottom

    // ************** 당신의 코드 
    // 왼쪽 벽과 오른쪽 벽 충돌
    if (distance_left <= left || distance_right >= left + width) {
        velocity.x *= -1;
    }
    // 위쪽 벽 충돌
    else if (distance_top >= bottom + height) {
        velocity.y *= -1;
    }
    // 아래쪽 벽 -> 게임 오버 
    else if (distance_bottom <= bottom) {
        showGameOverScreen();
        glutSwapBuffers();
    }

    /* 위쪽 벽과 아래쪽 벽 충돌
    else if (distance_top >= bottom + height || distance_bottom <= bottom) {
        velocity.y *= -1;
    }*/
}
/// <summary>
/// 공과 패들 충돌
/// </summary>
/// <param name=""></param>
void Collision_Detection_to_Paddle(void) {
    // 패들의 중심 좌표
    float Rect_x = (paddle.x + paddle2.x) / 2.0;
    float Rect_y = (paddle.y + paddle2.y) / 2.0;

    // 원의 중심점과 사각형의 중심점 간의 거리 구하기
    float distance_x = fabs(moving_ball.x - Rect_x);
    float distance_y = fabs(moving_ball.y - Rect_y);

    // 패들의 반지름
    float paddleX = (paddle2.x - paddle.x) / 2.0; // 가로길이의 반지름
    float paddleY = (paddle2.y - paddle.y) / 2.0; // 세로길이의 반지름

    // 충돌 판정
    if (distance_x > (paddleX + moving_ball_radius) ||
        distance_y > (paddleY + moving_ball_radius)) {
        // 충돌하지 않음
        return;
    }
    if (distance_x <= paddleX || distance_y <= paddleY) {
        // 원이 사각형 안에 있음
        velocity.y *= -1; // y방향 반대로
    }
    else {
        // 원이 사각형 모서리에 충돌함
        float corner_distance = pow(distance_x - paddleX, 2) + pow(distance_y - paddleY, 2);
        if (corner_distance <= pow(moving_ball_radius, 2)) {
            // 원과 모서리 간 충돌
            velocity.x *= -1; // x방향 반대로
            velocity.y *= -1; // y방향 반대로
        }
    }
}

// 방향키로 패들 바 움직이기 
void SpecialKey(int key, int x, int y) {
    switch (key)
    {
    case GLUT_KEY_LEFT:		paddle.x -= paddle_speed; paddle2.x -= paddle_speed;
        // 왼쪽 벽을 넘지 못하도록 막음 
        if (paddle.x < left) {
            paddle.x = left;
            paddle2.x = width / 4;
        }
        break;
    case GLUT_KEY_RIGHT:	paddle.x += paddle_speed; paddle2.x += paddle_speed;	
        // 오른쪽 벽을 넘지 못하도록 막음
        if (paddle2.x > width) {
            paddle.x = width / 1.3;
            paddle2.x = width;
        }
        break;
    default:
        break;
    }
}

void RenderScene(void) {

    glClearColor(0.5, 0.5, 0.5, 0.0); // Set display-window color to gray
    glClear(GL_COLOR_BUFFER_BIT);

    // 윈도우 중심의 위치에 고정된 공 그리기 
    glColor3f(1.0, 0.0, 0.0);
    if (collision_count % 2 == 0) {
        Modeling_Circle(radius1, fixed_ball);
    }

    // 충돌 처리 부분
    Collision_Detection_Between_Balls();      // 공과 공의 충돌 함수 
    Collision_Detection_to_Paddle();           // 공과 바의 충돌 함수
    Collision_Detection_to_Walls();         // 공과 벽의 충돌 함수 

    // 움직이는 공의 위치 변화 
    moving_ball.x += velocity.x;
    moving_ball.y += velocity.y;

    // 움직이는 공 그리기 
    glColor3f(0.0, 0.0, 1.0);
    Modeling_Circle(moving_ball_radius, moving_ball);

    // 패들 그리기
    Modeling_Paddle();

    glutSwapBuffers();
    glFlush();
}

void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutCreateWindow("Bouncing Ball & Wall");
    init();
    glutReshapeFunc(MyReshape);
    glutSpecialFunc(SpecialKey);
    glutDisplayFunc(RenderScene);
    glutIdleFunc(RenderScene);
    glutMainLoop();
}