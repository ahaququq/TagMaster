#pragma once

#include <string>

#include "../Utils/Types.hpp"

class Definition {
public:
    virtual std::string getName() const = 0;
    virtual std::string toString() const = 0;
};

class TypeDefinition: public virtual Definition {};

class NativeNumber: public virtual TypeDefinition {
private:
    bool sign;
    u8 width;

    NativeNumber(bool s, u8 w);
public:
    NativeNumber(const NativeNumber& other);
    std::string getName() const override;
    std::string toString() const override;

    static const NativeNumber I8;
    static const NativeNumber I16;
    static const NativeNumber I32;
    static const NativeNumber I64;

    static const NativeNumber U8;
    static const NativeNumber U16;
    static const NativeNumber U32;
    static const NativeNumber U64;
};