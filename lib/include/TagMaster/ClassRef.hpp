#pragma once

#include <string>

class ClassDef;

class ClassRef {
    std::string name;
    ClassDef *definition;
public:
    ClassRef(std::string name, ClassDef* definition);

    std::string getName();
    ClassDef& getDefinition();
    std::string toString();
};