#pragma once
#include "application_step.hpp"
#include <functional>
#include <entt/entt.hpp>

namespace fae
{
	struct application
	{
		using plugin = std::function<void(application&)>;

		struct quit {};

		application& run();
		bool is_running() const
		{
			return _is_running;
		}

		template<typename EventType, auto Candidate, typename... Type>
		application& set_system(Type &&...valueOrInstance)
		{
			_dispatcher.sink<EventType>().connect<Candidate>(std::forward<Type>(valueOrInstance)...);
			return *this;
		}

		template <typename Type, typename... Args>
		application& init_resource(Args &&...args)
		{
			_registry.ctx().emplace<Type>(std::forward<Args>(args)...);
			return *this;
		}

		template <typename Type>
		application& set_resource(Type&& resource)
		{
			_registry.ctx().insert_or_assign(std::forward<Type>(resource));
			return *this;
		}

		template <auto P>
		application& add_plugin()
		{
			(*P)(*this);
			return *this;
		}

	private:
		bool _is_running{};
		entt::registry _registry{};
		entt::dispatcher _dispatcher{};

		void on_quit(const quit& quit)
		{
			_is_running = false;
		}
	};

	struct setup_step : public application_step { setup_step(entt::registry& registry, entt::dispatcher& dispatcher) : application_step(registry, dispatcher) {} };
	struct start_step : public application_step { start_step(entt::registry& registry, entt::dispatcher& dispatcher) : application_step(registry, dispatcher) {} };
	struct update_step : public application_step { update_step(entt::registry& registry, entt::dispatcher& dispatcher) : application_step(registry, dispatcher) {} };
	struct stop_step : public application_step { stop_step(entt::registry& registry, entt::dispatcher& dispatcher) : application_step(registry, dispatcher) {} };
	struct cleanup_step : public application_step { cleanup_step(entt::registry& registry, entt::dispatcher& dispatcher) : application_step(registry, dispatcher) {} };
}