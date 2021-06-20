#ifndef TEXTUREPATHS_H
#define TEXTUREPATHS_H

#include "string"
#include "vector"

using std::string;
using std::vector;

namespace TexturePath
{
    const string textureBasePath = "..\\textures\\minecraft\\textures";
    const string fileEnding = ".png";
    const string tearainMap = textureBasePath+"\\terain\\map"+fileEnding;
    namespace Block
    {
        const string textureBaseBlockPath = textureBasePath + "\\block";

        const string grass  = textureBaseBlockPath+"\\grass_block_top"+fileEnding;
        const string dirt   = textureBaseBlockPath+"\\coarse_dirt"+fileEnding;
        const string stone  = textureBaseBlockPath+"\\stone"+fileEnding;
        const string sand   = textureBaseBlockPath+"\\sand"+fileEnding;
        const string water  = textureBaseBlockPath+"\\water\\water_0"+fileEnding;
    };

    namespace Animal {
        const string textureBaseAnimalPath = textureBasePath + "\\animal";

        const vector<string> sheep = {textureBaseAnimalPath + "\\Sheep\\sheep_0"+fileEnding,
                                      textureBaseAnimalPath + "\\Sheep\\sheep_1"+fileEnding,
                                      textureBaseAnimalPath + "\\Sheep\\sheep_2"+fileEnding,
                                      textureBaseAnimalPath + "\\Sheep\\sheep_3"+fileEnding,
                                      textureBaseAnimalPath + "\\Sheep\\sheep_4"+fileEnding,
                                      textureBaseAnimalPath + "\\Sheep\\sheep_5"+fileEnding,
                                      textureBaseAnimalPath + "\\Sheep\\sheep_6"+fileEnding,
                                      textureBaseAnimalPath + "\\Sheep\\sheep_7"+fileEnding};

    }

    namespace Plant {
        const string textureBasePlantsPath = textureBasePath + "\\plant";

        const vector<string> grass = {textureBasePlantsPath+"\\grass\\grass0"+fileEnding,
                                      textureBasePlantsPath+"\\grass\\grass1"+fileEnding,
                                      textureBasePlantsPath+"\\grass\\grass2"+fileEnding,
                                      textureBasePlantsPath+"\\grass\\grass3"+fileEnding,
                                      textureBasePlantsPath+"\\grass\\grass4"+fileEnding,
                                      textureBasePlantsPath+"\\grass\\grass5"+fileEnding,
                                      textureBasePlantsPath+"\\grass\\grass6"+fileEnding};

        const vector<string> flower  = {textureBasePlantsPath+"\\flower\\allium"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\blue_orchid"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\cornflower"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\flower_dandelion2"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\flower_dandelion3"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\flower_paeonia"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\lilac_top"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\oxeye_daisy"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\oxeye_daisy3"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\pink_tulip"+fileEnding,
                                       textureBasePlantsPath+"\\flower\\poppy"+fileEnding,};
    }
};
#endif // TEXTUREPATHS_H
