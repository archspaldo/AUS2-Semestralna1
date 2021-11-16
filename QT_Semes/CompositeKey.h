#pragma once
#include "DataItems.h"

namespace AUS2
{
	class CKLocResult
	{
		const location_t location_;
		const int id_;
		const bool result_;
	public:
		CKLocResult(const location_t location, const int id, const bool result);
		CKLocResult(const CKLocResult &other);
		std::strong_ordering operator<=>(const CKLocResult &other) const;
		bool operator==(const CKLocResult &other) const;
	};
	
	class CKLocID
	{
		const location_t location_;
		const int id_;
	public:
		CKLocID(const location_t location, const int id);
		CKLocID(const CKLocID &other);
		std::strong_ordering operator<=>(const CKLocID &other) const;
		bool operator==(const CKLocID &other) const;
	};
}

