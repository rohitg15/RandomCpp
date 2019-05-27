set(data_structures_SRCS
    union_find.h
    union_find.cpp
    morris_traversal.h
    main.cpp
    string_utils.cpp
    string_utils.h
)

set(Boost_INCLUDE_DIR /usr/local/boost/include/)

#FIND_PACKAGE( Boost 1.69 )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


add_executable(data_structures
    ${data_structures_SRCS}
)

install(TARGETS data_structures DESTINATION bin)

target_link_libraries(data_structures
    ${Boost_LIBRARIES}
)

# Specify here the include directories exported
# by this library
# target_include_directories(libsocket PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

