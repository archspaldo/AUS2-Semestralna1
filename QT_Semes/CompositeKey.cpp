#include "CompositeKey.h"

AUS2::CKLocResult::CKLocResult(const location_t location, const int id, const bool result) : location_(location), id_(id), result_(result) {
}

AUS2::CKLocResult::CKLocResult(const CKLocResult &other) : location_(other.location_), id_(other.id_), result_(other.result_) {
}

bool AUS2::CKLocResult::operator==(const CKLocResult &other) const {
	return this->location_ == other.location_ && this->id_ == other.id_ && this->result_ == other.result_;
}

std::strong_ordering AUS2::CKLocResult::operator<=>(const CKLocResult &other) const {
	if (auto c = this->location_ <=> other.location_; c != 0) {
		return c;
	}
	if (auto c = this->id_ <=> other.id_; c != 0) {
		return c;
	}
	return this->result_ <=> other.result_;
}

AUS2::CKLocID::CKLocID(const location_t location, const int id) : location_(location), id_(id) {
}

AUS2::CKLocID::CKLocID(const CKLocID &other) : location_(other.location_), id_(other.id_) {
}

bool AUS2::CKLocID::operator==(const CKLocID &other) const {
	return this->location_ == other.location_ && this->id_ == other.id_;
}

std::strong_ordering AUS2::CKLocID::operator<=>(const CKLocID &other) const {
	if (auto c = this->location_ <=> other.location_; c != 0) {
		return c;
	}
	return this->id_ <=> other.id_;
}
