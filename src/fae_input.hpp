#pragma once
#include "fae_application.hpp"

namespace fae
{
	void input_plugin(application& application);

	void quit_on_esc(update_step& step);
}