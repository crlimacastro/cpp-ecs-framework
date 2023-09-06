#pragma once
#include "entity.hpp"
#include <functional>
#include <stx/option.h>
#include <entt/entt.hpp>

namespace fae
{
	struct application_step
	{
		application_step(entt::registry& registry, entt::dispatcher& dispatcher) :
			_registry(registry),
			_dispatcher(dispatcher)
		{

		}

		entity create_entity()
		{
			auto new_entity = _registry.get().create();
			return entity(new_entity, _registry);
		}

		entity get_entity(const entt::entity& id)
		{
			return entity(id, _registry);
		}

		template <typename Type>
		stx::Option<std::reference_wrapper<Type>> get_resource() {
			if (!_registry.get().ctx().contains<Type>())
			{
				return stx::None;
			}
			return stx::Some<std::reference_wrapper<Type>>(_registry.get().ctx().get<Type>());
		}

		template <typename Type, typename... Args>
		application_step& init_resource(Args &&...args)
		{
			_registry.get().ctx().emplace<Type>(std::forward<Args>(args)...);
			return *this;
		}

		template <typename Type>
		application_step& set_resource(Type&& resource)
		{
			_registry.get().ctx().insert_or_assign(std::forward<Type>(resource));
			return *this;
		}

		template <typename Type>
		application_step& write_event(Type&& value = {}) {
			_dispatcher.get().trigger(std::forward<Type&&>(value));
			return *this;
		}


		template<typename Type, typename... Other, typename... Exclude>
		[[nodiscard]] entt::basic_view<entt::get_t<entt::registry::storage_for_type<Type>, entt::registry::storage_for_type<Other>...>, entt::exclude_t<entt::registry::storage_for_type<Exclude>...>>::iterable
			query(entt::exclude_t<Exclude...> = entt::exclude_t{}) {
			return _registry.get().view<Type, Other..., Exclude...>().each();
		}

	private:
		std::reference_wrapper<entt::registry> _registry;
		std::reference_wrapper<entt::dispatcher> _dispatcher;
	};
}