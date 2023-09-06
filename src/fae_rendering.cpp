#include "fae_pch.hpp"
#include "fae_rendering.hpp"

namespace fae
{
	void rendering_plugin(application& application)
	{
		application
			.add_plugin<&rendering_3d_plugin>()
			.init_resource<clear_color>()
			.init_resource<raylib::Window>(1920, 1080, "")
			.set_system<update_step, &quit_on_window_should_close>()
			.set_system<update_step, &update_rendering>()
			;
		SetExitKey(KEY_NULL);
	}
	void quit_on_window_should_close(update_step& step)
	{
		step.get_resource<raylib::Window>().match([&](raylib::Window& window) {
			if (!window.ShouldClose()) return;
			step.write_event(application::quit());
			}, []() {});
	}
	void update_rendering(update_step& step)
	{
		step.get_resource<raylib::Window>().match([&](raylib::Window& window) {
			window.BeginDrawing();
			step.get_resource<clear_color>().match([&](clear_color& clear_color) {
				window.ClearBackground(clear_color.color);
				}, []() {});
			step.write_event<>(draw_step(step));
			window.EndDrawing();
			}, []() {});
	}
}