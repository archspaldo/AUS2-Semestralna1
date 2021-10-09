#pragma once

namespace AUS2
{
	template <class Derived, class Base>
	concept CheckType = std::is_base_of<Base, Derived>::value;
}