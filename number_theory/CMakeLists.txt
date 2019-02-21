set(number_theory_SRCS
    factorization.h
    crypto_math.h
<<<<<<< HEAD
    #codes.h
    #codes.cpp
    factorization.cpp
    
=======
    primality.h
    file_helper.h
    file_helper.cpp
    factorization.cpp
    main.cpp
>>>>>>> a3f7d3af0132efd31cea7535eb3b053038e0ca40
)

set(Boost_INCLUDE_DIR /usr/local/boost/include/)

#FIND_PACKAGE( Boost 1.69 )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


add_executable(number_theory
    ${number_theory_SRCS}
)

install(TARGETS number_theory DESTINATION bin)

target_link_libraries(number_theory
    ${Boost_LIBRARIES}
)

# Specify here the include directories exported
# by this library
# target_include_directories(libsocket PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )
