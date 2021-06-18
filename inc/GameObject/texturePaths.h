#ifndef TEXTUREPATHS_H
#define TEXTUREPATHS_H

#include "string"

using std::string;

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
};
#endif // TEXTUREPATHS_H
