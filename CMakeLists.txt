cmake_minimum_required(VERSION 3.10)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(include)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/CartaNumero.cpp
    src/CartaAccion.cpp
    src/CartaComodin.cpp
    src/CartaFlip.cpp
    src/CartaPersonalizada.cpp
    src/Jugador.cpp
    src/Mazo.cpp
    src/Reglas.cpp
    src/ListaCircular.cpp
    src/VistaConsola.cpp
)

add_executable(test_stack
    tests/test_stack.cpp
    src/CartaNumero.cpp
    src/CartaAccion.cpp
    src/CartaComodin.cpp
    src/CartaFlip.cpp
    src/CartaPersonalizada.cpp
    src/Jugador.cpp
    src/Mazo.cpp
    src/Reglas.cpp
    src/ListaCircular.cpp
    src/VistaConsola.cpp
)

set_target_properties(${PROJECT_NAME} test_stack PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)