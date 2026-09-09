#include "TagMaster.hpp"

namespace TagMaster {
    Version getVersion() {
        return {0, 1, 0};
    }

    std::ostream& operator<<(
        std::ostream& os, Version version
    ) {
        os  << (int) version.major << 
        "." << (int) version.minor << 
        "." << (int) version.patch;
        return os;
    }
}