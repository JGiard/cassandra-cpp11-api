set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SOURCES cluster.cpp collection.cpp error.cpp future.cpp internal.cpp result.cpp row.cpp session.cpp statement.cpp uuid.cpp)
add_library(cassandra-cpp11-api ${SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(test)