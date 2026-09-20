#include "Storage/Definition.hpp"

// ----- class NativeNumber -----

NativeNumber::NativeNumber(bool s, u8 w): sign(s), width(w) {}

NativeNumber::NativeNumber(const NativeNumber& other)
: sign(other.sign), width(other.width) {}

std::string NativeNumber::getName() const {
    return sign ? "I" : "U" + std::to_string(width * 8);
}

std::string NativeNumber::toString() const {
    return "builtin type " + getName();
}

const NativeNumber NativeNumber::I8   = NativeNumber(true, 1);
const NativeNumber NativeNumber::I16  = NativeNumber(true, 2);
const NativeNumber NativeNumber::I32  = NativeNumber(true, 4);
const NativeNumber NativeNumber::I64  = NativeNumber(true, 8);

const NativeNumber NativeNumber::U8   = NativeNumber(false, 1);
const NativeNumber NativeNumber::U16  = NativeNumber(false, 2);
const NativeNumber NativeNumber::U32  = NativeNumber(false, 4);
const NativeNumber NativeNumber::U64  = NativeNumber(false, 8);