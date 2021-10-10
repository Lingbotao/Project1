// Project2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//  帧缓冲大小函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char* fragmenShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f,1.0f);\n"
    "}\n\0";
int main()
{
    std::cout << "Hello World!\n";
    glfwInit(); // 初始化GLFW
    //  配置GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //  glfwCreateWindow(宽，高，窗口名称, monitor，share)，monitor用于全屏模式的监视器，share用于上下文共享资源的窗口
    GLFWwindow* windows = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (windows == NULL)
    {
        std::cout << "Failed to create GFLW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(windows);
    glfwSetFramebufferSizeCallback(windows, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Faile to initialize GLAD" << std::endl;
        return -1;
    }
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //  检测glComileShader编译是否成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout <<"ERROR::SHADER::VERTEX::COMPILAION_FAILED\n"<< infoLog<< std::endl;
    }
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmenShaderSource, NULL);
    glCompileShader(fragmentShader);

    //  创建一个程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //  把编译的着色器附加到程序对象上
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //  检测连接着色器是否失败
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //  着色器对象连接到程序对象后，删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   //top right
        0.5f, -0.5f, 0.0f,  //bottom right
        -0.5f, -0.5f, 0.0f, //bottom left
        -0.5f, 0.5f, 0.0f   //top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //  解析顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //  glViewport(窗口的x坐标，窗口的y坐标，窗口的宽度，窗口的高度) 坐标以窗口的左下角为准
    //glViewport(0, 0, 800, 600);
    //  循环渲染
    while (!glfwWindowShouldClose(windows))
    {
        //  输入
        processInput(windows);
        //  渲染指令
        //  设置清空屏幕所用的颜色额
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //  清除颜色缓冲后，整个颜色缓冲会被填充为glClearColor所设置的颜色
        glClear(GL_COLOR_BUFFER_BIT);
        //  画三角形
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //激活程序对象
        glUseProgram(shaderProgram);

        //  交换颜色缓冲  (不懂)
        glfwSwapBuffers(windows);
        //  检出是否触发事件
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        //std::cout <<"按下" << std::endl;
        glfwSetWindowShouldClose(window, true);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件7