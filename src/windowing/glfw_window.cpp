#include "fae_windowing/glfw_window.hpp"

fae::glfw_window::glfw_window() :
	_window(glfwCreateWindow(1920, 1080, "", nullptr, nullptr))
{
}

bool fae::glfw_window::should_close()
{
	return glfwWindowShouldClose(_window);
}
