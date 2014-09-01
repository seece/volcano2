#!/bin/sh
if [ ! -d "game" ]; then
    mkdir game
    cd game
    wget --referer="http://www.suomipelit.fi/pelit/20/Volcano+2" www.suomipelit.fi/pelit/lataa/26
    if [ "" == "$(echo "a32cf406d50a784b9ab0a2b023b9ed3e  26"| md5sum -c --quiet -)" ]; then
        unzip 26
        rm 26
        mv SOUNDS sounds
        for i in * sounds/*
        do
            if [ "$i" != "sounds" -a "$i" != "file_id.diz" ]; then
                mv $i $(echo $i|tr [A-Z] [a-z])
            fi 
        done
        rm *.exe *.zip *.txt
        echo "Volcano2 downloaded."
    else 
        echo "Download failed. Please try again."
        cd ..
        rm -rf game
    fi 
else
    echo "Volcano2 already downloaded."
fi
