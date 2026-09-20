#pragma once

#include <string>
#include <memory>
#include <vector>

#include "../Utils/Types.hpp"

class Definition {
public:
	virtual ~Definition() = default;

	[[nodiscard]] virtual std::string getName() const = 0;
    [[nodiscard]] virtual std::string toString() const = 0;
};

class TypeDefinition: public virtual Definition {};

class NativeNumber: public virtual TypeDefinition {
private:
    bool sign;
    u8 width;

    NativeNumber(bool s, u8 w);
public:
    // NativeNumber(const NativeNumber& other);
    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string toString() const override;

    static std::shared_ptr<NativeNumber>& I8();
    static std::shared_ptr<NativeNumber>& I16();
    static std::shared_ptr<NativeNumber>& I32();
    static std::shared_ptr<NativeNumber>& I64();
    static std::shared_ptr<NativeNumber>& U8();
    static std::shared_ptr<NativeNumber>& U16();
    static std::shared_ptr<NativeNumber>& U32();
    static std::shared_ptr<NativeNumber>& U64();
};

/// Type definition with generic fields (Array<I32>, Pair<I32, U16>, etc.)
class GenericTypeDef: public virtual TypeDefinition {
public:
	struct GenField {
		std::string id;
		// std::shared_ptr<TypeDefinition> limit; // Limit storable types
	};
	[[nodiscard]] virtual std::vector<GenField> getGenFields() const = 0;

	[[nodiscard]] std::string genericDefToString() const;
};

class NativeArray: public virtual GenericTypeDef {
public:
	[[nodiscard]] std::vector<GenField> getGenFields() const override;
};