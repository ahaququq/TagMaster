#pragma once

#include <string>
#include <memory>

#include "../Utils/Types.hpp"
#include "./Definition.hpp"

// Storage searchable based on typenames
class DataStorage {
public:
    virtual ~DataStorage() = default;

    virtual std::shared_ptr<Definition> operator[](std::string id) const = 0;
};

/// Storage backed by an array-like object.
/// Serchable by indicies
class ArrayDataStorage: public virtual DataStorage {
public:
	virtual std::shared_ptr<Definition> operator[](u64 id) const = 0;
	[[nodiscard]] virtual u64 size() const = 0;
};