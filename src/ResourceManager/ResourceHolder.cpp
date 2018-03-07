#include "ResourceHolder.h"

ResourceHolder &ResourceHolder::get()
{
    static ResourceHolder holder;
    return holder;
}

ResourceHolder::ResourceHolder()
    : fonts("fonts", "ttf")
    , textures("textures", "png")
    , soundBuffers("sfx", "ogg")
{
}