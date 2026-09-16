#include "Object.hpp"

std::string Object::toString(const ClassRef& type, int indent) {
    return data->toString(type, indent);
}