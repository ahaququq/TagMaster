#include "ClassDef.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>

ClassDef::FieldProp::FieldProp(std::string name, ClassRef type)
    : name(name), type(type) {}

ClassDef::TagProp::TagProp(ClassRef type): type(type) {}

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
    unnamed.emplace_back(attribute.type);

    return *this;
}

ClassDef::ClassDef(Type type): classType(type) {}

std::string ClassDef::toString(std::string name) {
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
        out << "    var " << field.name << ": " << field.type.getName();
        out << " = " << "\"value\"\n";
    }
    if(!unnamed.empty()) out << "\n";
    for (auto tag: unnamed) {
        out << "    " << tag.type.getName() << "(" << "\"value\"" << ")\n";
    }
    out << "}\n";
    return out.str();
}