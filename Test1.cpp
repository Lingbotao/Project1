// Project2.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
    glfwInit(); // ��ʼ��GLFW
    //  ����GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //  glfwCreateWindow(���ߣ���������, monitor��share)��monitor����ȫ��ģʽ�ļ�������share���������Ĺ�����Դ�Ĵ���
    GLFWwindow* windows = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (windows == NULL)
    {
        std::cout << "Failed to create GFLW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(windows);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Faile to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;

}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�7