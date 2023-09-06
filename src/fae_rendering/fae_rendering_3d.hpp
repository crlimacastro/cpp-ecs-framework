#pragma once
#include <stx/option.h>
#include "../fae_application.hpp"
#include "fae_rendering_common.hpp"

namespace fae
{
	struct active_camera_3d {
		stx::Option<entity> camera_entity = stx::None;
	};
	using active_camera = active_camera_3d;

	struct draw_3d_step : public application_step { draw_3d_step(const application_step& step) : application_step(step) {} };

	struct common_resources {
		raylib::Shader lighting_shader = raylib::Shader("resources/shaders/lighting.vs.glsl", "resources/shaders/lighting.fs.glsl");
		raylib::Mesh unit_cube = raylib::Mesh::Cube(1, 1, 1);

		common_resources()
		{
			lighting_shader.locs[SHADER_LOC_VECTOR_VIEW] = lighting_shader.GetLocation("viewPos");
		}
	};

	void rendering_3d_plugin(application& application);
	void setup_active_camera_3d(setup_step& step);
	void setup_lighting_shader(setup_step& step);
	void update_lighting_shader(update_step& step);
	void update_lights(update_step& step);
	void update_camera_3ds_with_transform(update_step& step);
	void update_models_with_transform(update_step& step);
	void update_3d_rendering(draw_step& step);
	void render_models(draw_3d_step& step);
}