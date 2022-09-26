set (LIB_PUB_HEADERS
    include/lib.h
)

set (LIB_PRIV_HEADERS
)

set (LIB_PRIV_SOURCES
   lib.cpp
)

set (EXE_PRIV_HEADERS
)

set (EXE_PRIV_SOURCES
   main.cpp
)

add_library(template_lib)
target_sources(template_lib
    PUBLIC ${LIB_PUB_HEADERS}
    PRIVATE ${LIB_PRIV_HEADERS} ${LIB_PRIV_SOURCES})

add_executable(template_exe)
target_sources(template_exe PRIVATE ${EXE_PRIV_HEADERS} ${EXE_PRIV_SOURCES})
target_include_directories(template_exe PRIVATE include)
target_link_libraries(template_exe PRIVATE template_lib)

add_subdirectory(test)
