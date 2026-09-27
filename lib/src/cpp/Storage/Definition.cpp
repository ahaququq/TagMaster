#include "Storage/Definition.hpp"

#include <sstream>

// Is it the same
bool Definition::operator==(std::shared_ptr<Definition> other) const {
	return false;
}

// Is it of that type
bool Definition::matches(std::shared_ptr<Definition> other) const {
	return false;
}

// Can it be stored in that type of field
bool Definition::implements(std::shared_ptr<Definition> other) const {
	return false;
}

bool Definition::isAbstract() const { return false; }

// ----- class NativeNumberType -----

NativeNumberType::NativeNumberType(const bool s, const u8 w): sign(s), width(w) {}

// NativeNumberType::NativeNumberType(const NativeNumberType& other)
// : sign(other.sign), width(other.width) {}

std::string NativeNumberType::getName() const {
    return (sign ? "I" : "U") + std::to_string(width * 8);
}

std::string NativeNumberType::toString(std::shared_ptr<Definition> ctx) const {
    return matches(ctx) ? "builtin" : ("builtin type " + getName());
}

bool NativeNumberType::operator==(std::shared_ptr<Definition> other) const {
	std::shared_ptr<NativeNumberType> cast = std::dynamic_pointer_cast<NativeNumberType>(other);
	if (!cast) return false;
	return cast->sign == sign && cast->width == width;
}

bool NativeNumberType::matches(std::shared_ptr<Definition> other) const {
	return false;
}

std::shared_ptr<NativeNumberType>& NativeNumberType::I8() {
	static auto ptr = std::shared_ptr<NativeNumberType>{ new NativeNumberType(true,  1) };
	return ptr;
}

std::shared_ptr<NativeNumberType>& NativeNumberType::I16() {
	static auto ptr = std::shared_ptr<NativeNumberType>{ new NativeNumberType(true,  2) };
	return ptr;
}

std::shared_ptr<NativeNumberType>& NativeNumberType::I32() {
	static auto ptr = std::shared_ptr<NativeNumberType>{ new NativeNumberType(true,  4) };
	return ptr;
}

std::shared_ptr<NativeNumberType>& NativeNumberType::I64() {
	static auto ptr = std::shared_ptr<NativeNumberType>{ new NativeNumberType(true,  8) };
	return ptr;
}

std::shared_ptr<NativeNumberType>& NativeNumberType::U8() {
	static auto ptr = std::shared_ptr<NativeNumberType>{ new NativeNumberType(false, 1) };
	return ptr;
}

std::shared_ptr<NativeNumberType>& NativeNumberType::U16() {
	static auto ptr = std::shared_ptr<NativeNumberType>{ new NativeNumberType(false, 2) };
	return ptr;
}

std::shared_ptr<NativeNumberType>& NativeNumberType::U32() {
	static auto ptr = std::shared_ptr<NativeNumberType>{ new NativeNumberType(false, 4) };
	return ptr;
}

std::shared_ptr<NativeNumberType>& NativeNumberType::U64() {
	static auto ptr = std::shared_ptr<NativeNumberType>{ new NativeNumberType(false, 8) };
	return ptr;
}

std::string Number::getName() const {
	return "number";
}

std::string Number::toString(std::shared_ptr<Definition> ctx) const {
	return "number ";
}

i64 Number::getSigned() const {
	if (!type) return 0;
	if (data.size() != type->width) return 0;
	if (!type->sign) return 0;
	switch (type->width) {
		case 1: return *((i8 *) data.data());
		case 2: return *((i16 *) data.data());
		case 4: return *((i32 *) data.data());
		case 8: return *((i64 *) data.data());
		default: return 0;
	}
}

u64 Number::getUnsigned() const {
	if (!type) return 0;
	if (data.size() != type->width) return 0;
	if (type->sign) return 0;
	switch (type->width) {
		case 1: return *((u8 *) data.data());
		case 2: return *((u16 *) data.data());
		case 4: return *((u32 *) data.data());
		case 8: return *((u64 *) data.data());
		default: return 0;
	}
}

std::string CompoundDef::getName() const {
	return name;
}

std::string CompoundDef::toString(std::shared_ptr<Definition> ctx) const {
	std::stringstream out;
	if (isAbstract()) out << "abstract ";
	if (!name.empty()) out << "compound " << name;
	else out << "anon";
	// Don't show parents if empty OR if there is only one that matches the context (eg. type of field that it's being printed from)
	if (!parents.empty() && !(parents.size() == 1 && parents[0]->matches(ctx))) {
		out << ": ";
		bool first = true;
		for (const auto& parent : parents) {
			if (first) first = false; else out << ", ";
			out << parent->getName();
		}
		out << " ";
	}
	{
	out << "{ ";
		bool first = true;
		for (const FieldDef& field : named) {
			if (first) first = false; else out << ", ";
			out << "var " << field.id << ": " << field.type->getName();
			if (field.nullable) out << "?";
			if (field.value) out << " = " << field.value->toString(field.type);
			else if (field.nullable && !field.abstract) out << " = null";
			else if (!field.nullable && !field.abstract) out << " = [Error]";
		}
		for (const AttrDef& tag : unnamed) {
			if (first) first = false; else out << ", ";
			out << "atr: " << tag.type->getName();
			if (tag.value) out << " = " << tag.value->toString();
		}
		out << " }";
	}
	return out.str();
}

void addField(std::string name, std::shared_ptr<Definition> type, std::shared_ptr<Definition> def = nullptr) {

}

bool CompoundDef::matches(std::shared_ptr<Definition> other) const {
	std::shared_ptr<CompoundDef> cast = std::dynamic_pointer_cast<CompoundDef>(other);
	if (!cast) return false;
	return 
		cast->name == name && true;
		// cast->parents == parents && 
		// cast->named == named &&
		// cast->unnamed == unnamed;
}

bool CompoundDef::isAbstract() const {
	for (auto& field : named) {
		if (field.abstract) return true;
	}
	return false;
}

std::shared_ptr<Definition> CompoundDef::operator[](std::string id) const {
	for (auto& field : named) {
		if (field.id == id) return field.value;
	}
	return nullptr;
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

std::string GenericTypeDef::toString(std::shared_ptr<Definition> ctx) const {
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
