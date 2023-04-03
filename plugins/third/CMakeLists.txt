
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set (HEADERS
    thirdplugin.h
)

set (SOURCES
    thirdplugin.cpp
)

ADD_LIBRARY(thirdplugin SHARED ${SOURCES} ${HEADERS})
target_link_libraries(thirdplugin PRIVATE Qt5::Core)
