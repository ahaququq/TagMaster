#pragma once

#include <vector>
#include <optional>

#include "ObjectData.hpp"
#include "Object.hpp"

class ClassObjectData: public virtual ObjectData {
public:
    struct FieldValue {
        std::string name;
        ClassRef type;
        Object value;
    };

    struct TagValue {
        ClassRef type;
        Object value;
    };

    // Based on types from class, empty if default
    std::vector<std::optional<Object>> named;

    // Tags added to object, or values for tags required by parent
    std::vector<TagValue> tags;

    ClassObjectData();

    std::vector<FieldValue> getNamed(const ClassRef& type) const;

    virtual std::string toString(const ClassRef& type, int indent) const override;

    ClassObjectData& operator+(Object value);
    ClassObjectData& operator+(std::nullptr_t);
};