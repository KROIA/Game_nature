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

        const string grass = textureBasePlantsPath+"\\grass\\grass_1"+fileEnding;
    }
};
#endif // TEXTUREPATHS_H
