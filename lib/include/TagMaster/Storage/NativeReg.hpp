#pragma once

#include "./DataStorage.hpp"
#include <vector>
#include <string>
#include <memory>

class NativeRegistry: public virtual DataStorage {
private:
    std::vector<std::shared_ptr<Definition>> data;
public:
    NativeRegistry(std::initializer_list<std::shared_ptr<Definition>> d);

    std::shared_ptr<Definition> operator[](std::string id) const override;
};