#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "./DataStorage.hpp"
#include "../Utils/Types.hpp"

class BasicDataBuffer: public virtual DataStorage {
private:
    static constexpr u32 magic = 0x01020304;

    std::vector<u8> data;

    struct IndexEntry {
        u64 pos, length;
    };

    std::map<std::string, IndexEntry> index;
public:
    BasicDataBuffer();
    BasicDataBuffer(std::istream& source);

    std::shared_ptr<Definition> operator[](std::string id) const override;

    static bool checkMagic(const void* data);

    friend std::ostream& operator<<(std::ostream& os, const BasicDataBuffer & that);
};