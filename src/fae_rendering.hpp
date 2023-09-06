#pragma once
#include "fae_rendering/fae_rendering_common.hpp"
#include "fae_rendering/fae_rendering_2d.hpp"
#include "fae_rendering/fae_rendering_3d.hpp"

namespace fae
{
	void rendering_plugin(application& application);
	void quit_on_window_should_close(update_step& step);
	void update_rendering(update_step& step);
}