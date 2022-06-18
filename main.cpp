#define STB_IMAGE_IMPLEMENTATION
# include"Test1.h"
# include"Test2.h"
# include"Test3.h"
# include"Test4.h"
# include"Test5.h"
# include"Test6.h"
# include"Test6_1.h"
# include"Test6_2.h"
#include "main.h"

#include <GLFW/glfw3.h>
#include <stb_image.h>


//  帧缓冲大小函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	Test6_1();
	//Test6_2();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		//std::cout <<"按下" << std::endl;
		glfwSetWindowShouldClose(window, true);
}