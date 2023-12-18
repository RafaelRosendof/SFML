#!/bin/bash

echo "Creating the compilation"

run="clang++ teste.cpp Hero.cpp Enemy.cpp Rocket.cpp -o teste"
flags="-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio"

echo "$run $flags"

compile=true

if [ "$compile" == "true" ]; then
    echo "Building"
    $run $flags

    if [ $? -eq 0 ]; then
        echo "Compiling"
        echo "running"

        road="./teste"
        echo "Executing $road"
        $road
    else
        echo "Deu algo de errado"
    fi

else
    echo "volte e veja o código"

fi 