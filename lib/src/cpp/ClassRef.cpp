#include "ClassRef.hpp"
#include "ClassDef.hpp"

ClassRef::ClassRef(std::string name, ClassDef* definition)
: name(name), definition(definition) {}

std::string ClassRef::getName() const {
    return name;
}

ClassDef& ClassRef::getDefinition() const {
    return *definition;
}

std::string ClassRef::toString() const {
    return definition->toString(name);
}