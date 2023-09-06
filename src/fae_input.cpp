#include "fae_pch.hpp"
#include "fae_input.hpp"
#include <raylib-cpp.hpp>

namespace fae
{
	void input_plugin(application& application)
	{

	}

	void quit_on_esc(update_step& step)
	{
		if (!IsKeyPressed(KEY_ESCAPE)) return;
		step.write_event(application::quit());
	}
}