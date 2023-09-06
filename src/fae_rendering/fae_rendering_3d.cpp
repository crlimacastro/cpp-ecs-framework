#include "fae_pch.hpp"
#include "fae_rendering_3d.hpp"
#include "../fae_raylib.hpp"
#include "../fae_math.hpp"
#define RLIGHTS_IMPLEMENTATION
#include "fae_raylib/rlights.h"

namespace fae
{
	void rendering_3d_plugin(application& application)
	{
		application
			.init_resource<active_camera_3d>()
			.set_system<setup_step, &setup_active_camera_3d>()
			.set_system<setup_step, &setup_lighting_shader>()
			.set_system<update_step, &update_camera_3ds_with_transform>()
			.set_system<update_step, &update_lighting_shader>()
			.set_system<update_step, &update_lights>()
			.set_system<update_step, &update_models_with_transform>()
			.set_system<draw_step, &update_3d_rendering>()
			.set_system<draw_3d_step, &render_models>();
		;
	}

	void setup_active_camera_3d(setup_step& step)
	{
		fae::entity entity = step.create_entity()
			.set_component<raylib::Transform3>(
				raylib::Vector3{ 0, 0, 10 },
				raylib::Quaternion::FromEuler(0, to_radians(180), 0),
				raylib::Vector3{ 1, 1, 1 })
			.set_component<raylib::Camera3D>(
				raylib::Camera3D{
			raylib::Vector3{ 0, 0, 10 },
				raylib::Vector3{ 0, 0, 9 },
				raylib::Vector3{ 0, 1, 0 },
				45,
				CAMERA_PERSPECTIVE
		});
		step.get_resource<active_camera_3d>().match([&](active_camera_3d& active_camera_3d)
			{
				active_camera_3d.camera_entity = stx::Some<fae::entity>(std::move(entity));
			}, []() {});
	}

	void setup_lighting_shader(setup_step& step)
	{
		step.init_resource<common_resources>();
	}

	void update_lighting_shader(update_step& step)
	{
		step.get_resource<common_resources>().match([&](common_resources& lighting_shader)
			{
				step.get_resource<clear_color>().match([&](clear_color& clear_color)
					{

						step.get_resource<active_camera_3d>().match([&](active_camera_3d& active_camera_3d)
							{
								raylib::Vector4 ambient{ clear_color.color.r / 255.f, clear_color.color.g / 255.f, clear_color.color.b / 255.f, clear_color.color.a / 255.f };
								lighting_shader.lighting_shader.SetValue(lighting_shader.lighting_shader.GetLocation("ambient"), &ambient, SHADER_UNIFORM_VEC4);

								active_camera_3d.camera_entity.match([&](fae::entity camera_entity)
									{
										camera_entity.get_component<raylib::Transform>().match([&](raylib::Transform& transform)
											{
												lighting_shader.lighting_shader.SetValue(lighting_shader.lighting_shader.locs[SHADER_LOC_VECTOR_VIEW], &transform.translation, SHADER_UNIFORM_VEC3);
											}, []() {});

									}, []() {});
							}, []() {});
					}, []() {});
			}, []() {});
	}

	void update_lights(update_step& step)
	{
		step.get_resource<common_resources>().match([&](common_resources& lighting_shader)
			{
				for (auto [entity, light] : step.query<const Light>())
				{
					UpdateLightValues(lighting_shader.lighting_shader, light);
				}
			}, []() {});
	}

	void update_camera_3ds_with_transform(update_step& step)
	{
		for (auto [entity, transform, camera] : step.query<const raylib::Transform, raylib::Camera3D>())
		{
			camera.position = transform.translation;
			camera.target = transform.translation + raylib::Vector3{ 0, 0, 1 }.Transform(transform.GetRotation().ToMatrix());
		}
	}

	void update_models_with_transform(update_step& step)
	{
		for (auto [entity, transform, model] : step.query<const raylib::Transform, raylib::Model>())
		{
			model.transform = transform.ToMatrix();
		}
	}

	void update_3d_rendering(draw_step& step)
	{
		step.get_resource<active_camera_3d>().match([&](const active_camera_3d& active_camera) {
			active_camera.camera_entity.match([&](const entity& entity) {
				if (entity.is_valid())
				{
					entity.get_component<raylib::Camera3D>().match([&](raylib::Camera3D& camera_3d) {
						camera_3d.BeginMode();
						step.write_event(draw_3d_step{ step });
						camera_3d.EndMode();
						}, []() {});
				}
				}, []() {});
			}, []() {});
	}

	void render_models(draw_3d_step& step)
	{
		for (auto [id, model] : step.query<const raylib::Model>())
		{
			fae::entity entity = step.get_entity(id);
			bool should_draw = true;
			entity.get_component<visibility>().match([&](const visibility& visibility)
				{
					should_draw = visibility.is_visible;
				}, []() {});
			if (!should_draw)
			{
				continue;
			}

			raylib::Color tint = raylib::Color::White();
			entity.get_component<raylib::Color>().match([&](raylib::Color& color) {
				tint = color;
				}, []() {});
			model.Draw({ 0, 0, 0 }, 1.f, tint);
		}
	}
}