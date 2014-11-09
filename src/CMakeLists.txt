if(CMAKE_COMPILER_IS_GNUCXX OR APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

include("${PROJECT_SOURCE_DIR}/vendor/includes.cmake")

file(GLOB KCLIB_SOURCES *.cpp *.h)

add_library(kclib ${KCLIB_SOURCES})
