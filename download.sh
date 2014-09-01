#!/bin/sh
if [ ! -d "game" ]; then
    mkdir game
    cd game
    wget --referer="http://www.suomipelit.fi/pelit/20/Volcano+2" www.suomipelit.fi/pelit/lataa/26
    unzip 26
    rm 26
    mv SOUNDS sounds
    for i in * sounds/*
    do
        if [ "$i" != "sounds" -a "$i" != "file_id.diz" ]; then
            mv $i $(echo $i|tr [A-Z] [a-z])
        fi 
    done
    rm *.exe *.zip
    echo "Volcano2 downloaded."
else
    echo "Volcano2 already downloaded."
fi
