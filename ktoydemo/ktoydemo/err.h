#pragma once

#include <exception>

namespace ktoy {
	class toy_error : std::exception {
	public:
		toy_error(char const* const msg) noexcept :
			std::exception(msg) {}
	};
}