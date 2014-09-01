#!/bin/sh
if [ ! -d "game" ]; then
    mkdir game
    cd game
    wget --referer="http://www.suomipelit.fi/pelit/20/Volcano+2" www.suomipelit.fi/pelit/lataa/26
    unzip 26
    rm 26
    echo "Volcano2 downloaded."
else
    echo "Volcano2 already downloaded."
fi
