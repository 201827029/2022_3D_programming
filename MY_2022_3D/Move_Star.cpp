#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>
#include "MuSoenMath.h"
// #include <glm/glm.hpp>  //GLM���� ����� �� �ִ� ����� ����� ���� �ڷ����� ������ ����
// #include <glm/gtc/matrix_transform.hpp> //��� ��ȯ�� ���Ǵ� ���� �Լ����� ������ ����


#pragma comment(lib, "OpenGL32")

using namespace std;

chrono::system_clock::time_point startRenderTimePoint;
chrono::duration<double> renderDuration;

GLFWwindow* window;
bool isFirstFrame = true;


struct Vertex   //struct = ����ü      //����ü = ���� �ڷ����� ���� �������� �ϳ��� ���� �ڷ������� ����� �� �ֵ��� ����
{
    vector3 pos; //������ ����
    float r, g, b, a;

};

matrix3 translate(         //���� �̵�

    1, 0, 0,
    0, 1, 0,
    0, 0, 1

);

matrix3 rotation(          //���� ȸ��

    cos(0), -sin(0), 0,
    sin(0), cos(0), 0,
    0, 0, 1

);

matrix3 scale(        //���� ũ�� ����

    1, 0, 0,
    0, 1, 0,
    0, 0, 1

);

Vertex star[5];             // static mesh
Vertex transformedStar[5];  //ȭ�鿡 �׸� ������
Vertex circle[360];             // static mesh 
Vertex transformedCircle[360];  // ȭ�鿡 �׷��� ��

  //world ����� �� transform

//<����>////////�������� ���°�////////////////////////////////////////////////////////////

        //1. translate �� �����Ӵ� ���������� 0.001�� �������Ѽ� ��ü�� �̵��غ�����.
        //2. Rotation �� �����Ӵ� 1���� �������Ѽ� ��ü�� ȸ�����Ѻ�����.
        //3. Scale�� �ʴ� 0.01�� �ִ� 1.3����� �þ�ٰ� 0.7����� �پ�鵵�� ����ÿ� (�ݺ�)
        //   (1.3�� �̻��� �Ǹ� �پ��� 0.7�� ���ϰ� �Ǹ� �ٽ� �þ�� ����ÿ�)

float scale_default = 1.0f;           //�⺻ ũ��
float scale_plus = 1.01f;              //ũ�Ⱑ Ŀ�� �� ���̴� ����
float scale_minus = 0.99f;           //ũ�Ⱑ �۾��� �� ���̴� ����

bool scale_change = true;                      //�Ұ��� ���� ũ�Ⱑ Ŀ���� �۾�����.

matrix3 translate_move(         //���� �̵�

    1,0,0,
    0,1,0,
    0.001,0,1

);

matrix3 rotation_move(          //���� ȸ��

    cos(2 * (3.14 / 180)), -sin(2 * (3.14 / 180)), 0,
    sin(2 * (3.14 / 180)), cos(2 * (3.14 / 180)), 0,
    0, 0, 1

);

matrix3 circle_scale_plus(        //���� ũ�� ����

    1.01, 0, 0,
    0, 1.01, 0,
    0, 0, 1

);

matrix3 circle_scale_minus(       //���� ũ�� ����

    0.99, 0, 0,
    0, 0.99, 0,
    0, 0, 1

);


//////////////////////////////////////////////////////////////////////////////////////////

void Init();
void Update();
void Release();

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void);


void Init()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(720, 720, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);

    startRenderTimePoint = chrono::system_clock::now();


    //object������
     /// Star(������) ����
    int i = 0;
    for (float theta = 0; theta < 360; theta += 72)
    {

        star[i].pos.vec3[0][0] = -sin(theta*(3.14/180)) * 0.5f;
        star[i].pos.vec3[0][1] = cos(theta * (3.14 / 180)) * 0.5f;
        star[i].pos.vec3[0][2] = 1.0f;

        star[i].r = 0.3f;
        star[i].g = 0.0f;
        star[i].b = theta / 360.0f;
        star[i].a = 0.7f;


        transformedStar[i] = star[i];

        i++;
    }

    // �� ����
    for (int theta = 0; theta < 360; theta++)
    {
        circle[theta].pos.vec3[0][0] = -sin(theta * (3.14 / 180)) * 0.5;
        circle[theta].pos.vec3[0][1] = cos(theta * (3.14 / 180)) * 0.5;
        circle[theta].pos.vec3[0][2] = 1.0f;

        circle[theta].r = 0.3f;
        circle[theta].g = 0.0f;
        circle[theta].b = (float)theta / 360.0f;
        circle[theta].a = 0.7f;

        transformedCircle[theta] = circle[theta];
    }



   
}

void Release()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
void Update()
{
    while (!glfwWindowShouldClose(window))
    {
        //Update����
        //<����>//////////////////////////////////////////////////////////////////////////////////

        //1. translate �� �����Ӵ� ���������� 0.001�� �������Ѽ� ��ü�� �̵��غ�����.
        //2. Rotation �� �����Ӵ� 1���� �������Ѽ� ��ü�� ȸ�����Ѻ�����.
        //3. Scale�� �ʴ� 0.01�� �ִ� 1.3����� �þ�ٰ� 0.7����� �پ�鵵�� ����ÿ� (�ݺ�)
        //   (1.3�� �̻��� �Ǹ� �پ��� 0.7�� ���ϰ� �Ǹ� �ٽ� �þ�� ����ÿ�)

        translate = translate * translate_move;         //translate_move ���� ��� ���Ͽ� ������ �̵���Ŵ
        
        rotation = rotation * rotation_move;             //rotation_move ���� ��� ���Ͽ� ������ ȸ����Ŵ

        
        if (scale_change == true) {     // true�� ��

            scale = scale * circle_scale_plus;                  //���� ũ�� ����
            scale_default = scale_default * scale_plus;                                    //�⺻ ���� ���� ������ ���� �ʱ�ȭ ��Ų��.

        }
        else if (scale_change == false) {       //false�� ��

            scale = scale * circle_scale_minus;               //���� ũ�� ����
            scale_default = scale_default * scale_minus;                                //�⺻ ���� ���� ������ ���� �ʱ�ȭ ��Ų��.

        }

        if (scale_default >= 1.3f) {                                                                  //���� �⺻ ���� 1.3 �̻��̸�

            scale_change = false;                                                                      //false ������ �ٲ� ũ�⸦ �۰� �����.

        }
        else if (scale_default <= 0.7f) {                                                           //���� �⺻ ���� 0.7 ���ϸ�

            scale_change = true;                                                                       //true ������ �ٲ� ũ�⸦ ũ�� �����.

        }

        //////////////////////////////////////////////////////////////////////////////////////////

        for (int i = 0; i < 360; i++)
        {
            transformedCircle[i].pos = circle[i].pos * scale * rotation * translate;
        }

        for (int i = 0; i < 5; i++)
        {
            transformedStar[i].pos = star[i].pos * scale* rotation* translate;
        }



        //�� �ʱ�ȭ
        glClearColor(.0f, 0.0f, 0.0f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        //���β�
        glLineWidth(7.0f);
        //������ �׸���
        glBegin(GL_LINE_STRIP);

        int a = 0;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.vec3[0][0], transformedStar[a].pos.vec3[0][1], 0.0f);
        a = 3;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.vec3[0][0], transformedStar[a].pos.vec3[0][1], 0.0f);
        a = 1;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.vec3[0][0], transformedStar[a].pos.vec3[0][1], 0.0f);
        a = 4;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.vec3[0][0], transformedStar[a].pos.vec3[0][1], 0.0f);
        a = 2;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.vec3[0][0], transformedStar[a].pos.vec3[0][1], 0.0f);

        a = 0;
        glColor4f(transformedStar[a].r, transformedStar[a].g, transformedStar[a].b, transformedStar[a].a);
        glVertex3f(transformedStar[a].pos.vec3[0][0], transformedStar[a].pos.vec3[0][1], 0.0f);
        glEnd();

        //���׸���
        glBegin(GL_LINE_STRIP);
        for (int theta = 0; theta < 360; theta++)
        {
            glColor4f(transformedCircle[theta].r, transformedCircle[theta].g, transformedCircle[theta].b, transformedCircle[theta].a);
            glVertex3f(transformedCircle[theta].pos.vec3[0][0], transformedCircle[theta].pos.vec3[0][1], 0.0f);
        }
        glEnd();



        //ȭ�� ����
        glfwSwapBuffers(window);
        glfwPollEvents();

        //�����ð� ����
        renderDuration = chrono::system_clock::now() - startRenderTimePoint;
        startRenderTimePoint = chrono::system_clock::now();

        float fps = 1.0 / renderDuration.count();
        if (isFirstFrame == true)
        {
            isFirstFrame = false;
            continue;
        }
        if (renderDuration.count() < (1.0f / 60.0f))
            this_thread::sleep_for(chrono::milliseconds((int)(((1.0f / 60.0f) - renderDuration.count()) * 1000)));
        string fps_s = "FPS : " + to_string(fps);
        cout << fps_s << endl;

    }
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    Init();
    Update();
    Release();

    exit(EXIT_SUCCESS);
}