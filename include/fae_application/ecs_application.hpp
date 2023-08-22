#pragma once
#include "iapplication.hpp"

namespace fae
{
	struct ecs_application : public iapplication
	{
		virtual iapplication& run() override;
	};
}