#include "map.h"

#include <iostream>
#include <fstream>


namespace engine
{
    Map::Map()
    {

    }

    bool Map::load(const char *filePath)
    {
        std::ifstream file(filePath);

        if(file.is_open())
        {
            int columnsCount, rowsCount;

            file >> columnsCount;
            file >> rowsCount;

            char **map = new char*[rowsCount];

            for(int i = 0; i < rowsCount; ++i)
            {
                char *row = new char[columnsCount];

                for(int j = 0; j < columnsCount; ++j)
                    file >> row[i * columnsCount + j];

                map[i] = row;
            }

            for(int i = 0; i < rowsCount; ++i)
            {
                for(int j = 1; j < columnsCount; ++j)
                {

                }
            }

            file.close();
            return true;
        }

        return false;
    }
}
