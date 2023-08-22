#pragma once

namespace fae
{
	struct iwindow {
		virtual bool should_close() = 0;
	};
}