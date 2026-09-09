#include <iostream>
#include <vector>

#include "TagMaster/TagMaster.hpp"
#include "TagMaster/ClassDef.hpp"
#include "TagMaster/ClassOwner.hpp"

int main() {
    std::cout << "TagMaster Version: " << TagMaster::getVersion() << "\n";

    auto A = ClassOwner("A", {ClassDef::Type::CLASS});
    auto B = ClassOwner("B", 
        ClassDef(ClassDef::Type::CLASS) 
        + ClassDef::FieldProp{"foo", A.ref}
        + ClassDef::FieldProp{"bar", A.ref}
    );
    auto C = ClassOwner("C", {ClassDef::Type::TAG});
    auto D = ClassOwner("D", 
        ClassDef(ClassDef::Type::CLASS)
        + ClassDef::FieldProp{"fear", A.ref}
        + ClassDef::FieldProp{"bear", B.ref}
        + C.ref
    );

    std::cout << A.ref.toString() << "\n";
    std::cout << B.ref.toString() << "\n";
    std::cout << C.ref.toString() << "\n";
    std::cout << D.ref.toString() << "\n";
}