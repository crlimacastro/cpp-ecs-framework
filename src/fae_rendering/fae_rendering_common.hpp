#pragma once
#include <raylib-cpp.hpp>
#include "../fae_application.hpp"

namespace fae
{
	constexpr auto DEFAULT_CLEAR_COLOR = BLACK;

	struct clear_color
	{
		raylib::Color color = DEFAULT_CLEAR_COLOR;
	};

	struct visibility
	{
		bool is_visible = true;
	};

	struct draw_step : public application_step { draw_step(const application_step& step) : application_step(step) {} };
}