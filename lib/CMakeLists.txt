add_library(TagMasterLib STATIC
    src/cpp/TagMaster.cpp
    src/cpp/ClassDef.cpp
    src/cpp/ClassRef.cpp
    src/cpp/ClassOwner.cpp
    src/cpp/Object.cpp
    src/cpp/ClassObjectData.cpp
    src/cpp/Native/StringData.cpp
    src/cpp/Utils/Text.cpp
    src/cpp/Storage/Definition.cpp
    src/cpp/Storage/BasicDataBuffer.cpp
)

target_include_directories(TagMasterLib
    INTERFACE include
    PRIVATE include/TagMaster
)