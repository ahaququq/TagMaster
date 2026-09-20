#include "Storage/NativeReg.hpp"

NativeRegistry::NativeRegistry(std::initializer_list<std::shared_ptr<Definition>> d) {
    for (const auto& def : d) {
        data.emplace_back(def);
    }
}

std::shared_ptr<Definition> NativeRegistry::operator[](std::string id) const {
    for (auto& def: data) {
        if (def->getName() == id) return def;
    }
    return nullptr;
}