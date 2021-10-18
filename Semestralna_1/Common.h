#pragma once
#include <compare>

namespace AUS2
{
	template <class DataType>
	concept PrimaryKeyProtocol = requires(const DataType & data) {
		{ data < data } -> std::convertible_to<bool>;
		{ data > data } -> std::convertible_to<bool>;
		{ data == data } -> std::convertible_to<bool>;
	};
}