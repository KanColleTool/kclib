if(CMAKE_COMPILER_IS_GNUCXX OR APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

file(GLOB KCLIB_SOURCES *.cpp)

add_library(kclib ${KCLIB_SOURCES})

find_library(LIBZ z)
target_link_libraries(kclib ${LIBZ})

find_package(Qt5Network)
if(Qt5Network_FOUND)
	add_subdirectory(qt)
	target_link_libraries(kclib kclib_qt)
endif()
