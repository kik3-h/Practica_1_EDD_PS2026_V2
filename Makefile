# Makefile – PRACTICA UNO EDD 2026

CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -I include
TARGET   := bin/Practica1_EDD_Enrique_Tebalan
TEST_BIN := bin/Test_de_prueba

SRCS := src/main.cpp \
        src/CartaNumero.cpp \
        src/CartaAccion.cpp \
        src/CartaComodin.cpp \
        src/CartaFlip.cpp \
        src/CartaPersonalizada.cpp \
        src/Jugador.cpp \
        src/Mazo.cpp \
        src/Reglas.cpp \
        src/ListaCircular.cpp \
        src/VistaConsola.cpp

TEST_SRCS := tests/test_stack.cpp \
             src/CartaNumero.cpp \
             src/CartaAccion.cpp \
             src/CartaComodin.cpp \
             src/CartaFlip.cpp \
             src/CartaPersonalizada.cpp \
             src/Jugador.cpp \
             src/Mazo.cpp \
             src/Reglas.cpp \
             src/ListaCircular.cpp \
             src/VistaConsola.cpp

OBJS      := $(patsubst src/%.cpp, build/%.o, $(filter src/%.cpp, $(SRCS)))
TEST_OBJS := $(patsubst src/%.cpp,  build/%.o, $(filter src/%.cpp,  $(TEST_SRCS))) \
             build/test_stack.o

.PHONY: all clean run test dirs

## all: Compila el juego principal
all: dirs $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo ""
	@echo "    Compilado correctamente en: $(TARGET)"
	@echo ""

## test: Compila y ejecuta las pruebas unitarias
test: dirs $(TEST_BIN)
	@echo ""
	@echo "    Ejecutando pruebas..."
	@echo ""
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

## run: Ejecuta el juego
run: all
	@echo ""
	./$(TARGET)

## clean: Elimina binarios y objetos
clean:
	rm -f bin/UNO bin/test_stack
	rm -rf build/*.o
	@echo "    Limpieza completada."

## dirs: Crea los directorios necesarios
dirs:
	@mkdir -p bin build

## help: Muestra esta ayuda
help:
	@echo ""
	@echo "  Targets disponibles:"
	@echo "    make all    – Compila el proyecto"
	@echo "    make run    – Compila y ejecuta"
	@echo "    make test   – Ejecuta las pruebas unitarias"
	@echo "    make clean  – Elimina los binarios"
	@echo ""