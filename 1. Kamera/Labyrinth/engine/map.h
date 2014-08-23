#ifndef MAP_H
#define MAP_H

namespace engine
{
    class Map
    {
    private:
        bool _loaded;

    public:
        Map();

        bool load(const char *filePath);

    };
}

#endif // MAP_H
