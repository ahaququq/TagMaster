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

std::shared_ptr<Definition> NativeRegistry::operator[](const u64 id) const {
	return data[id];
}

u64 NativeRegistry::size() const {
	return data.size();
}

std::shared_ptr<NativeRegistry>& NativeRegistry::defNatives() {
	static auto ptr = std::make_shared<NativeRegistry>(NativeRegistry{
		NativeNumberType::I8(), NativeNumberType::I16(), NativeNumberType::I32(), NativeNumberType::I64(),
		NativeNumberType::U8(), NativeNumberType::U16(), NativeNumberType::U32(), NativeNumberType::U64()
	});
	return ptr;
}
