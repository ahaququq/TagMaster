#include "ClassDef.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "Utils/Text.hpp"

ClassDef::FieldProp::FieldProp(
    std::string name, ClassRef type, std::shared_ptr<Object> def
): name(name), type(type), def(std::move(def)) {}

ClassDef::FieldProp::FieldProp(const FieldProp& other)
: FieldProp(other.name, other.type, other.def) {}

ClassDef::FieldProp& ClassDef::FieldProp::operator*(Object o) {
    def = std::make_shared<Object>(o);
    return *this;
}

ClassDef::FieldProp operator/(std::string name, ClassRef type) {
    return ClassDef::FieldProp(name, type);
}

ClassDef::TagProp::TagProp(
    ClassRef type, std::shared_ptr<Object> def
): type(type), def(std::move(def)) {}

ClassDef::TagProp::TagProp(const TagProp& other)
: TagProp(other.type, other.def) {}

ClassDef::TagProp operator*(ClassRef type, Object o) {
    return ClassDef::TagProp(type, std::make_shared<Object>(o));
}

ClassDef& ClassDef::operator+(FieldProp field) {
    if (field.type.getDefinition().classType != Type::CLASS) 
        throw std::runtime_error("Field is not of type field!");
    if (std::any_of(
        named.begin(), 
        named.end(), 
        [&field](FieldProp& p){ return p.name == field.name; })
    ) throw std::runtime_error("Field " + field.name + " already exists!");

    named.emplace_back(field);

    return *this;
}

ClassDef& ClassDef::operator+(TagProp attribute) {
    if (attribute.type.getDefinition().classType != Type::TAG)
        throw std::runtime_error("Attribute is not of type tag");
    unnamed.emplace_back(attribute);

    return *this;
}

ClassDef::ClassDef(Type type): classType(type) {}

std::string ClassDef::toString(std::string name, int indent) {
    std::ostringstream out;

    switch (classType) {
        case Type::CLASS:
            out << "class ";
            break;
        case Type::TAG:
            out << "attribute ";
            break;
    }

    if (name != "") out << name << " ";
    out << "{\n";
    for (auto field: named) {
        out << ind(indent) << "var " << field.name << ": " << field.type.getName();
        if (field.def) out << " = " << field.def->toString(field.type, indent + 1);
        out << "\n";
    }
    if(!unnamed.empty()) out << "\n";
    for (auto tag: unnamed) {
        out << ind(indent) << tag.type.getName();
        if (tag.def) out << " = " << tag.def->toString(tag.type, indent + 1);
        out << "\n";
    }
    out << "}\n";
    return out.str();
}