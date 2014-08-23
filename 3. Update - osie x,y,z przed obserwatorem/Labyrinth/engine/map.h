#ifndef MAP_H
#define MAP_H

#include "vector3d.h"

#include <stdint.h>
#include <GL/gl.h>


namespace engine
{
	struct Wall
	{
		Vector3D a, b, c, d;
	};

    class Map
    {
    private:
		bool _loaded;
		bool _created;

		GLuint _id;

		double _wallWidth, _wallHeight;

		Wall **_walls;
		uint32_t _wallsCount;

		Wall *calculateVertivalWall(double x, double z);
		Wall *calculateHorizontalWall(double x, double z);
		Wall *calculateFlor(double x, double z);

    public:
        Map();

        bool load(const char *filePath);
		bool create();
		bool use();

    };
}

#endif // MAP_H
