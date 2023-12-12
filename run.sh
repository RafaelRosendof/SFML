#!/bin/bash 

echo "Running the Program"

run="clang++ sfml.cpp Hero.cpp Enemy.cpp Rocket.cpp -o sfml"
flags="-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio"

echo "$run $flags"

compile=true

if [ "$compile" == "true" ]; then
    echo "Compilando"
    $run $flags

    if [ $? -eq 0 ]; then
        echo "Deu certo"
        echo "Executando"

        road="./sfml"
        echo "Running $road"
        $road
    else
        echo "Compilação deu Erro"

    fi
else
    echo "Compilando pulou e deu algo a mais"
fi





