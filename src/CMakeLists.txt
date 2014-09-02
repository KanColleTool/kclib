if(CMAKE_COMPILER_IS_GNUCXX OR APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE KCLIB_SOURCES *.cpp ${PROJECT_SOURCE_DIR}/include/*.h)

find_package(Qt5Network)
if(Qt5Network_FOUND)
	message("Qt available")
	set(CMAKE_AUTOMOC ON)
	file(GLOB KCLIB_QT_SOURCES qt/*.cpp ${PROJECT_SOURCE_DIR}/include/qt/*.h)
	list(APPEND KCLIB_SOURCES ${KCLIB_QT_SOURCES})
else()
	message("Qt unavailable")
endif()

add_library(kclib ${KCLIB_SOURCES})

find_library(LIBZ z)
target_link_libraries(kclib ${LIBZ})

if(Qt5Network_FOUND)
	target_link_libraries(kclib Qt5::Network)
endif()
