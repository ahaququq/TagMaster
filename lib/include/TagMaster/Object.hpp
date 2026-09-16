#pragma once

#include <memory>
#include <string>

#include "ClassRef.hpp"
#include "ObjectData.hpp"

class Object {
public:
    template <class OD>
    Object(const OD& data);

    std::shared_ptr<ObjectData> data;

    std::string toString(const ClassRef& type, int indent = 1);
};

template <class OD>
Object::Object(const OD& data) {
    this->data = std::static_pointer_cast<ObjectData>(
        std::make_shared<OD>(data)
    );
}