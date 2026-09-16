#pragma once

#include <string>

#include "ClassRef.hpp"

class ObjectData {
public:
    virtual std::string toString(const ClassRef& type, int indent) const = 0;
};