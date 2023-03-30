
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set (HEADERS
    iplugin.h
    firstplugin.h
)

set (SOURCES
    firstplugin.cpp
)

ADD_LIBRARY(firstplugin SHARED ${SOURCES} ${HEADERS})
target_link_libraries(firstplugin PRIVATE Qt5::Core)
