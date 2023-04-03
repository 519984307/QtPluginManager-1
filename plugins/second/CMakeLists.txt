
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set (HEADERS
    secondplugin.h
)

set (SOURCES
    secondplugin.cpp
)

ADD_LIBRARY(secondplugin SHARED ${SOURCES} ${HEADERS})
target_link_libraries(secondplugin PRIVATE Qt5::Core)
