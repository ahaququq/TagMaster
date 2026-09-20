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
		NativeNumber::I8(), NativeNumber::I16(), NativeNumber::I32(), NativeNumber::I64(),
		NativeNumber::U8(), NativeNumber::U16(), NativeNumber::U32(), NativeNumber::U64()
	});
	return ptr;
}
