#pragma once

#include <string>
#include <memory>
#include <vector>

#include "../Utils/Types.hpp"

class Definition {
public:
	virtual ~Definition() = default;

	[[nodiscard]] virtual std::string getName() const = 0;
    [[nodiscard]] virtual std::string toString(std::shared_ptr<Definition> ctx = nullptr) const = 0;

    virtual bool operator==(std::shared_ptr<Definition> other) const;
    virtual bool matches(std::shared_ptr<Definition> other) const;
    virtual bool implements(std::shared_ptr<Definition> other) const;
    virtual bool isAbstract() const;
};

class TypeDefinition: public virtual Definition {};

class NativeNumberType: public virtual Definition {
private:
    NativeNumberType(bool s, u8 w);
public:
    bool sign;
    u8 width;
    
    // NativeNumberType(const NativeNumberType& other);
    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string toString(std::shared_ptr<Definition> ctx = nullptr) const override;

    bool operator==(std::shared_ptr<Definition> other) const override;
    bool matches(std::shared_ptr<Definition> other) const override;

    static std::shared_ptr<NativeNumberType>& I8();
    static std::shared_ptr<NativeNumberType>& I16();
    static std::shared_ptr<NativeNumberType>& I32();
    static std::shared_ptr<NativeNumberType>& I64();
    static std::shared_ptr<NativeNumberType>& U8();
    static std::shared_ptr<NativeNumberType>& U16();
    static std::shared_ptr<NativeNumberType>& U32();
    static std::shared_ptr<NativeNumberType>& U64();
};

class Number: public virtual Definition {
public:
    std::shared_ptr<NativeNumberType> type;
    std::vector<u8> data;

    [[nodiscard]] std::string getName() const override;
    [[nodiscard]] std::string toString(std::shared_ptr<Definition> ctx = nullptr) const override;

    i64 getSigned() const;
    u64 getUnsigned() const;
};

class CompoundDef: public virtual Definition {
public:
    struct FieldDef {
        std::string id;
        std::shared_ptr<Definition> type;
        std::shared_ptr<Definition> value;
        bool abstract = false, nullable = false;
        // Abstract - if a class has one it can't be used to make an object
        // Nullable - I8 vs I8? - can it be null; if false nullptr value requires abstract = true
    };

    struct AttrDef {
        std::shared_ptr<Definition> type;
        std::shared_ptr<Definition> value;
    };

    std::string name;
    std::vector<std::shared_ptr<Definition>> parents;
    std::vector<FieldDef> named;
    std::vector<AttrDef> unnamed;

    std::string getName() const override;
    std::string toString(std::shared_ptr<Definition> ctx = nullptr) const override;

    bool matches(std::shared_ptr<Definition> other) const override;
    bool isAbstract() const override;

    // Get a field value ()
    std::shared_ptr<Definition> operator[](std::string id) const;
    std::shared_ptr<Definition> getTag(std::shared_ptr<Definition> type);

    void addField(std::string name, std::shared_ptr<Definition> type, std::shared_ptr<Definition> def = nullptr);
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
    [[nodiscard]] std::string toString(std::shared_ptr<Definition> ctx = nullptr) const override;
};

class GenericTypeSpec: public virtual TypeDefinition {
public:
    virtual std::shared_ptr<GenericTypeDef> getGenDef() const = 0;
    virtual std::shared_ptr<TypeDefinition> getGenValue(std::string id) const = 0;
};

class NativeArray: public virtual GenericTypeDef {
public:
    [[nodiscard]] std::string getName() const override;
	[[nodiscard]] std::vector<GenField> getGenFields() const override;
};

class NativeArraySpec: public virtual GenericTypeSpec {

};