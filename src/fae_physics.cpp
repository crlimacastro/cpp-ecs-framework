#include "fae_pch.hpp"
#include "fae_physics.hpp"
#include "fae_raylib.hpp"
#include "fae_rendering.hpp"

namespace fae
{
	void physics_plugin(application& application)
	{
		application
			.init_resource<physics>()
			.set_system<update_step, &update_transforms_with_rigid_bodies>()
			.set_system<update_step, &update_physics>()
			.set_system<draw_3d_step, &debug_draw_physics>()
			;
	}
	void update_transforms_with_rigid_bodies(update_step& step)
	{
		for (auto [entity, transform, rigid_body] : step.query<raylib::Transform, const rigid_body>()) {
			transform = raylib::Transform(
				raylib::Vector3(
					rigid_body.get_transform().getPosition().x,
					rigid_body.get_transform().getPosition().y,
					rigid_body.get_transform().getPosition().z
				),
				raylib::Quaternion(
					rigid_body.get_transform().getOrientation().x,
					rigid_body.get_transform().getOrientation().y,
					rigid_body.get_transform().getOrientation().z,
					rigid_body.get_transform().getOrientation().w
				),
				transform.GetScale()
			);
		}
	}
	void update_physics(update_step& step)
	{
		step.get_resource<physics>().match([](physics& physics)
			{
				physics.world->setIsDebugRenderingEnabled(true);
				physics.world->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
				physics.update(GetFrameTime());
			}, []() {});
	}
	void debug_draw_physics(draw_3d_step& step)
	{
		step.get_resource<physics>().match([](physics& physics)
			{
				for (const auto& line : physics.world->getDebugRenderer().getLines())
				{
					raylib::Color color1 = raylib::Color(line.color1);
					color1.a = 255;
					raylib::Color color2 = raylib::Color(line.color2);
					color2.a = 255;
					DrawPoint3D({ line.point1.x, line.point1.y, line.point1.z }, color1);
					DrawLine3D({ line.point1.x, line.point1.y, line.point1.z }, { line.point2.x, line.point2.y, line.point2.z }, color1);
					DrawPoint3D({ line.point2.x, line.point2.y, line.point2.z }, color2);
				}
				for (const auto& triangle : physics.world->getDebugRenderer().getTriangles())
				{
					raylib::Color color1 = raylib::Color(triangle.color1);
					color1.a = 255;
					raylib::Color color2 = raylib::Color(triangle.color2);
					color2.a = 255;
					raylib::Color color3 = raylib::Color(triangle.color3);
					color3.a = 255;
					DrawLine3D({ triangle.point1.x, triangle.point1.y, triangle.point1.z }, { triangle.point2.x, triangle.point2.y, triangle.point2.z }, color1);
					DrawLine3D({ triangle.point2.x, triangle.point2.y, triangle.point2.z }, { triangle.point3.x, triangle.point3.y, triangle.point3.z }, color2);
					DrawLine3D({ triangle.point3.x, triangle.point3.y, triangle.point3.z }, { triangle.point1.x, triangle.point1.y, triangle.point1.z }, color3);
				}
			}, []() {});
	}
}