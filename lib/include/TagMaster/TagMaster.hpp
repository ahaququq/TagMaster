#include <ostream>

namespace TagMaster {
    struct Version {
        unsigned char major;
        unsigned char minor;
        unsigned short patch;

        friend std::ostream& operator<<(
            std::ostream& os, Version version
        );
    };

    Version getVersion();
}