#pragma once
#include <memory>
#include "fae_application.hpp"
#include "fae_rendering.hpp"

namespace fae
{
	struct physics
	{
		float time_step = 1.f / 60.f;
		reactphysics3d::PhysicsCommon common;
		reactphysics3d::PhysicsWorld* world;

		physics() : world(common.createPhysicsWorld()) {}

		physics& update(float delta_time) {
			_time_accumulator += delta_time;
			while (_time_accumulator >= time_step) {
				world->update(time_step);
				_time_accumulator -= time_step;
			}
			return *this;
		}

	private:
		float _time_accumulator = 0.f;
	};

	struct rigid_body
	{
		rigid_body(reactphysics3d::RigidBody* rigid_body) : _rigid_body(rigid_body) {}
		const reactphysics3d::Transform& get_transform() const { return _rigid_body->getTransform(); }
	private:
		reactphysics3d::RigidBody* _rigid_body;
	};

	void physics_plugin(application& application);
	void update_transforms_with_rigid_bodies(update_step& step);
	void update_physics(update_step& step);
	void debug_draw_physics(draw_3d_step& step);
}