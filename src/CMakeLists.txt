if(CMAKE_COMPILER_IS_GNUCXX OR APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE KCLIB_SOURCES *.cpp ${PROJECT_SOURCE_DIR}/include/*.h)
add_library(kclib ${KCLIB_SOURCES})

find_library(LIBZ z)
target_link_libraries(kclib ${LIBZ})
