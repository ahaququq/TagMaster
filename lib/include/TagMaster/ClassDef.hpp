#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "ClassRef.hpp"
#include "Object.hpp"

class ClassDef {
public:
    struct FieldProp {
        std::string name; ClassRef type; 
        std::shared_ptr<Object> def;

        FieldProp(
            std::string name, ClassRef type, 
            std::shared_ptr<Object> def = nullptr
        );

        FieldProp(const FieldProp& other);

        FieldProp& operator*(Object o);
    };

    struct TagProp {
        ClassRef type;
        std::shared_ptr<Object> def;

        TagProp(
            ClassRef type, 
            std::shared_ptr<Object> def = nullptr
        );

        TagProp(const TagProp& other);
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

    std::string toString(std::string name, int indent = 1);
};

ClassDef::FieldProp operator/(std::string name, ClassRef type);
ClassDef::TagProp operator*(ClassRef type, Object o);