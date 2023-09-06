#pragma once
#include <functional>
#include <stx/option.h>
#include <entt/entt.hpp>

namespace fae
{
	struct entity
	{
		entity(entt::entity entity, entt::registry& registry) :
			_entity(entity),
			_registry(registry)
		{

		}

		template<typename Type, typename... Args>
		const entity& set_component(Args &&...args) const
		{
			_registry.get().emplace_or_replace<Type>(_entity, std::forward<Args>(args)...);
			return *this;
		}

		template<typename... Type>
		stx::Option<std::reference_wrapper<Type>...> get_component() const
		{
			auto component_ptr = _registry.get().try_get<Type...>(_entity);
			if (!component_ptr)
			{
				return stx::None;
			}
			return stx::Some<std::reference_wrapper<Type>...>(*component_ptr);
		}

		void destroy() const
		{
			_registry.get().destroy(_entity);
		}

		bool is_valid() const
		{
			return _registry.get().valid(_entity);
		}



	private:
		entt::entity _entity;
		std::reference_wrapper<entt::registry> _registry;
	};
}