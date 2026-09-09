#include "ClassOwner.hpp"

ClassOwner::ClassOwner(std::string name, ClassDef def)
: definition(def), ref(name, &definition) {}