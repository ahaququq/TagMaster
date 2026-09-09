add_executable(TagMasterTest
    src/cpp/main.cpp
)

target_link_libraries(TagMasterTest
    PRIVATE TagMasterLib
)