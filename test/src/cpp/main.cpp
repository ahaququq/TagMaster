#include <iostream>
#include <vector>
#include <fstream>

#include "TagMaster/TagMaster.hpp"
#include "TagMaster/ClassDef.hpp"
#include "TagMaster/ClassOwner.hpp"

#include "TagMaster/Native/StringData.hpp"
#include "TagMaster/ClassObjectData.hpp"

#include "TagMaster/Storage/BasicDataBuffer.hpp"
#include "TagMaster/Storage/NativeReg.hpp"

static void testV1() {
    auto A = ClassOwner("A", {ClassDef::Type::CLASS});
    auto B = ClassOwner("B", 
        ClassDef(ClassDef::Type::CLASS) 
        + "foo" / A.ref * Object(StringData("Foonction"))
        + "bar" / A.ref
    );
    auto C = ClassOwner("C", {ClassDef::Type::TAG});
    auto D = ClassOwner("D", 
        ClassDef(ClassDef::Type::TAG)
        + "green" / A.ref * Object(StringData("blue"))
    );
    auto E = ClassOwner("E", 
        ClassDef(ClassDef::Type::CLASS)
        + "fear" / A.ref
        + "bear" / B.ref * Object(StringData("Breaker"))
        + C.ref * Object(ClassObjectData())
        + D.ref * Object(ClassObjectData())
    );

    auto ObjB0 = Object(ClassObjectData()
        + nullptr
        + Object(StringData("Neverest"))
    );

    auto ObjB1 = Object(ClassObjectData()
        + Object(StringData("Neverest"))
        + nullptr
    );

    std::cout << A.ref.toString() << "\n";
    std::cout << B.ref.toString() << "\n";
    std::cout << C.ref.toString() << "\n";
    std::cout << D.ref.toString() << "\n";
    std::cout << E.ref.toString() << "\n";

    std::cout << "ObjB0 = " << ObjB0.toString(B.ref) << "\n";
    std::cout << "ObjB1 = " << ObjB1.toString(B.ref) << "\n";

    ClassDef::TagProp test1 = C.ref * Object(StringData("DatumMobile"));

    // std::cout << "0x";
    // std::cout.width(8);
    // std::cout.fill('0');
    // std::cout << std::hex << reinterpret_cast<long>(test1.def.get()) << " " << 31 << "\n";
}

static void testV2() {
    auto b1 = BasicDataBuffer();
    std::cout << b1[""]->toString() << "\n";
    std::ofstream("b1.tgm", std::ios::binary) << b1;
    std::ifstream f2("b1.tgm", std::ios::binary);
    auto b2 = BasicDataBuffer(f2);
    std::cout << b2[""]->toString() << "\n";
	auto& nat = NativeRegistry::defNatives();
	for (u64 i = 0; i < nat->size(); i++) {
		std::cout << i << " => " << (*nat)[i]->toString() << "\n";
	}
    std::cout << NativeArray().toString() << "\n";
}

int main() {
    std::cout << "TagMaster Version: " << TagMaster::getVersion() << "\n";

    // testV1();
    testV2();
}