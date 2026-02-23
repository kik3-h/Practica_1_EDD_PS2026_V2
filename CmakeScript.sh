#!/bin/bash
echo "======================================="
echo "   COMPILADOR PRACTICA 1 EN C++"
echo "     EDD PS2026 - USAC CUNOC"
echo "======================================="
echo "Ingrese el nombre del ejecutable:"
read EXECUTABLE_NAME

if [ -z "$EXECUTABLE_NAME" ]; then
    echo "Nombre no puede estar vacío. Usando 'UNO' por defecto."
    EXECUTABLE_NAME="UNO"
fi

if [ ! -d "build" ]; then
    echo "Creando carpeta build..."
    mkdir build
fi

if [ ! -d "bin" ]; then
    echo "Creando carpeta bin..."
    mkdir bin
fi

echo ""
echo "Configurando proyecto con CMake..."
cmake -B build -S . -DPROJECT_NAME=${EXECUTABLE_NAME}

if [ $? -ne 0 ]; then
    echo "ERROR: Falló la configuración de CMake."
    exit 1
fi

echo ""
echo "Compilando..."
cmake --build build

if [ $? -ne 0 ]; then
    echo "ERROR: Falló la compilación."
    exit 1
fi

echo "======================================="
echo "Compilación terminada."
echo "Ejecutable generado en: bin/${EXECUTABLE_NAME}"
echo "======================================="
echo ""
echo "Para ejecutar el juego:"
echo "  ./bin/${EXECUTABLE_NAME}"
echo ""
echo "Para ejecutar las pruebas:"
echo "  ./bin/test_stack"
echo ""