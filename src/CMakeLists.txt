if(CMAKE_COMPILER_IS_GNUCXX OR APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

file(GLOB KCLIB_SOURCES *.cpp *.h)

add_library(kclib ${KCLIB_SOURCES})
