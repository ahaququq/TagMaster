add_library(TagMasterLib STATIC
    src/cpp/TagMaster.cpp
    src/cpp/ClassDef.cpp
    src/cpp/ClassRef.cpp
    src/cpp/ClassOwner.cpp
)

target_include_directories(TagMasterLib
    INTERFACE include
    PRIVATE include/TagMaster
)