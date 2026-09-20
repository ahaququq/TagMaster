#include "Native/StringData.hpp"

StringData::StringData(std::string str): str(str) {}

std::string StringData::toString(const ClassRef& type, int indent) const {
    return "\"" + str + "\"";
}