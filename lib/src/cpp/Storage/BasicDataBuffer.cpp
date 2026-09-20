#include "Storage/BasicDataBuffer.hpp"

#include <stdexcept>
#include <sstream>

BasicDataBuffer::BasicDataBuffer() {
    // Add magic
    data.emplace_back(magic >> 24);
    data.emplace_back(magic >> 16);
    data.emplace_back(magic >> 8);
    data.emplace_back(magic);
}

BasicDataBuffer::BasicDataBuffer(std::istream& source) {
    std::cout << "data = ";
    while (source) {
        i8 ch = source.get();
        if (!source) break;
        data.emplace_back(ch);
        std::cout << "0x";
        const auto fmt = std::cout.setf(std::ios::hex);
        std::cout.fill('0');
        std::cout.width(2);
        std::cout << std::hex << static_cast<u32>(static_cast<u8>(ch));
        std::cout.setf(fmt);
        std::cout << " ";
    }
    std::cout << "\n";

    std::cout.flush();

    if (!checkMagic(data.data())) throw std::runtime_error("BasicDataBuffer doesn't have proper magic bytes. Did you check your file before loading?");
}

std::shared_ptr<Definition> BasicDataBuffer::operator[](std::string id) const {
    return NativeNumber::U8();
}

bool BasicDataBuffer::checkMagic(const void* data) {
    const u8* dat = static_cast<const u8 *>(data);
    const u32 d = dat[0] << 24 | dat[1] << 16 | dat[2] << 8 | dat[3];
    return d == magic;
}

std::ostream& operator<<(std::ostream& os, const BasicDataBuffer & that) {
    os.write(reinterpret_cast<const i8*>(that.data.data()), that.data.size());
    return os;
}