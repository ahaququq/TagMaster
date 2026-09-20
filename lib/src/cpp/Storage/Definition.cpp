#include "Storage/Definition.hpp"

#include <sstream>

// ----- class NativeNumber -----

NativeNumber::NativeNumber(const bool s, const u8 w): sign(s), width(w) {}

// NativeNumber::NativeNumber(const NativeNumber& other)
// : sign(other.sign), width(other.width) {}

std::string NativeNumber::getName() const {
    return (sign ? "I" : "U") + std::to_string(width * 8);
}

std::string NativeNumber::toString() const {
    return "builtin type " + getName();
}

std::shared_ptr<NativeNumber>& NativeNumber::I8() {
	static auto ptr = std::shared_ptr<NativeNumber>{ new NativeNumber(true,  1) };
	return ptr;
}

std::shared_ptr<NativeNumber>& NativeNumber::I16() {
	static auto ptr = std::shared_ptr<NativeNumber>{ new NativeNumber(true,  2) };
	return ptr;
}

std::shared_ptr<NativeNumber>& NativeNumber::I32() {
	static auto ptr = std::shared_ptr<NativeNumber>{ new NativeNumber(true,  4) };
	return ptr;
}

std::shared_ptr<NativeNumber>& NativeNumber::I64() {
	static auto ptr = std::shared_ptr<NativeNumber>{ new NativeNumber(true,  8) };
	return ptr;
}

std::shared_ptr<NativeNumber>& NativeNumber::U8() {
	static auto ptr = std::shared_ptr<NativeNumber>{ new NativeNumber(false, 1) };
	return ptr;
}

std::shared_ptr<NativeNumber>& NativeNumber::U16() {
	static auto ptr = std::shared_ptr<NativeNumber>{ new NativeNumber(false, 2) };
	return ptr;
}

std::shared_ptr<NativeNumber>& NativeNumber::U32() {
	static auto ptr = std::shared_ptr<NativeNumber>{ new NativeNumber(false, 4) };
	return ptr;
}

std::shared_ptr<NativeNumber>& NativeNumber::U64() {
	static auto ptr = std::shared_ptr<NativeNumber>{ new NativeNumber(false, 8) };
	return ptr;
}

std::string GenericTypeDef::genericDefToString() const {
	std::stringstream out;
	out << "<";
	bool first = true;
	for (const GenField& gen: getGenFields()) {
		if (first) {
			first = false;
		} else {
			out << ", ";
		}
		out << gen.id;
	}
	out << ">";
	return out.str();
}

std::string GenericTypeDef::toString() const {
	return "generic def " + getName() + genericDefToString();
}

std::string NativeArray::getName() const {
	return "NativeArray";
}

std::vector<GenericTypeDef::GenField> NativeArray::getGenFields() const {
	return {
		{"ElementType"}
	};
}
