#include "fae_pch.hpp"
#include "application.hpp"

namespace fae
{
	application& application::run()
	{
		_is_running = true;
		_registry.ctx().emplace<application*>(this);
		_dispatcher.sink<quit>().connect<&application::on_quit>(*this);
		_dispatcher.trigger(setup_step(_registry, _dispatcher));
		_dispatcher.trigger(start_step(_registry, _dispatcher));
		while (_is_running) {
			_dispatcher.trigger(update_step(_registry, _dispatcher));
		}
		_dispatcher.trigger(stop_step(_registry, _dispatcher));
		_dispatcher.trigger(cleanup_step(_registry, _dispatcher));
		return *this;
	}
}