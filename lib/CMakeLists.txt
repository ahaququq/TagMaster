add_library(TagMasterLib STATIC
    src/cpp/TagMaster.cpp
)

target_include_directories(TagMasterLib
    PUBLIC include
)