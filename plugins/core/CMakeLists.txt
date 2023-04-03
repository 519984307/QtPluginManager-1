
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set (HEADERS
    iplugin.h
)

ADD_LIBRARY(coreplugin SHARED ${SOURCES} ${HEADERS})
target_link_libraries(coreplugin PRIVATE Qt5::Core)
