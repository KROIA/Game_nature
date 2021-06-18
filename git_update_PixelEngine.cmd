@rem git submodule update --init --recursive 

cd extern\PixelEngine
@rem git checkout master
git pull
git submodule update --init --recursive 
pause