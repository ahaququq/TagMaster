#pragma once

#include "../ObjectData.hpp"

class StringData: public virtual ObjectData {
public:
    std::string str;
    StringData(std::string str);

    virtual std::string toString(const ClassRef& type, int indent) const override;
};