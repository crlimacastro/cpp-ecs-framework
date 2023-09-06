#include "fae_pch.hpp"
#include "fae_default_plugins.hpp"
#include "fae_input.hpp"
#include "fae_rendering.hpp"
#include "fae_physics.hpp"

namespace fae
{
	void default_plugins(application& application)
	{
		application
			.add_plugin<&input_plugin>()
			.add_plugin<&rendering_plugin>()
			.add_plugin<&physics_plugin>()
			;
	}
}