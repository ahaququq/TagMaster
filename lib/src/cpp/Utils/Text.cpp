#include "Utils/Text.hpp"

std::string ind(int indent) {
    std::string out;
    while (indent-- > 0) {
        out += "  ";
    }
    return out;
}