#pragma once
#include <GLFW/glfw3.h>
#include "iwindow.hpp"

namespace fae
{
	struct glfw_window : public iwindow {
		glfw_window();
		virtual bool should_close() override;
	private:
		GLFWwindow* _window;
	};
}