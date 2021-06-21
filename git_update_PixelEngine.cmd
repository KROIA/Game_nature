@rem git submodule update --init --recursive 

cd extern\PixelEngine
rem git checkout Development
git pull
git submodule update --init --recursive 
pause