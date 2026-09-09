#include "ClassRef.hpp"
#include "ClassDef.hpp"

ClassRef::ClassRef(std::string name, ClassDef* definition)
: name(name), definition(definition) {}

std::string ClassRef::getName() {
    return name;
}

ClassDef& ClassRef::getDefinition() {
    return *definition;
}

std::string ClassRef::toString() {
    return definition->toString(name);
}