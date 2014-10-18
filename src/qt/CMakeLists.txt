set(CMAKE_AUTOMOC ON)
file(GLOB kclib_QT_SOURCES *.cpp *.h)
file(GLOB kclib_QT_SOURCES_JUNK moc_*.cpp *_automoc.cpp)
list(REMOVE_ITEM kclib_QT_SOURCES "${kclib_QT_SOURCES_JUNK}")

add_library(kclib_qt ${kclib_QT_SOURCES})

find_package(Qt5Network)
target_link_libraries(kclib_qt Qt5::Network)
