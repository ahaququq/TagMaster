#pragma once

#include <vector>
#include <map>
#include <string>

#include "ClassRef.hpp"

class ClassDef {
public:
    struct FieldProp {
        std::string name; ClassRef type;

        FieldProp(std::string name, ClassRef type);
    };

    struct TagProp {
        ClassRef type;

        TagProp(ClassRef type);
    };

    std::vector<FieldProp> named; // Normal class fields
    std::vector<TagProp> unnamed; // Tags

    enum class Type {
        CLASS,
        TAG,
    };

    Type classType; // Is it a class, or a tag

    ClassDef(Type type);

    ClassDef& operator+(FieldProp field);
    ClassDef& operator+(TagProp attribute);

    std::string toString(std::string name);
};