#pragma once

#include "ClassDef.hpp"

class ClassOwner {
public:
    ClassDef definition;
    ClassRef ref;

    ClassOwner(std::string name, ClassDef definition);
};