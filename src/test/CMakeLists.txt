set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(CxxTest)
if(CXXTEST_FOUND)
    include_directories(${CXXTEST_INCLUDE_DIR})
    enable_testing()
    CXXTEST_ADD_TEST(api_test tst_wrapper_gen.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/tst_wrapper.h)
    target_link_libraries(api_test cassandra-cpp11-api uuid ${LIBS})
endif()