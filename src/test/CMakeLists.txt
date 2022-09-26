include(GoogleTest)

SET (THIS_SRC
        test.cpp
    )

# Improve containers and algorithms
add_executable(template_test ${THIS_SRC})
target_link_libraries(template_test ${GTEST_LIBS_TO_LINK} ${CMAKE_THREAD_LIBS_INIT} template_lib)
target_include_directories(template_test PRIVATE ../include)

gtest_discover_tests(template_test)
