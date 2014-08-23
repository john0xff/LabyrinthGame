#include "map.h"

#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <vector>

namespace engine
{
	Wall *Map::calculateVertivalWall(double x, double z)
	{
		Wall *wall = new Wall();

		wall->a.x = x;
		wall->a.y = 0.0;
		wall->a.z = z;

		wall->b.x = x - this->_wallWidth;
		wall->b.y = 0.0;
		wall->b.z = z;

		wall->c.x = x - this->_wallWidth;
		wall->c.y = this->_wallHeight;
		wall->c.z = z;

		wall->d.x = x;
		wall->d.y = this->_wallHeight;
		wall->d.z = z;

		return wall;
	}

	Wall *Map::calculateHorizontalWall(double x, double z)
	{
		Wall *wall = new Wall();

		wall->a.x = x;
		wall->a.y = 0.0;
		wall->a.z = z;

		wall->b.x = x;
		wall->b.y = 0.0;
		wall->b.z = z + this->_wallWidth;

		wall->c.x = x;
		wall->c.y = this->_wallHeight;
		wall->c.z = z + this->_wallWidth;

		wall->d.x = x;
		wall->d.y = this->_wallHeight;
		wall->d.z = z;

		return wall;
	}

	Wall *Map::calculateFlor(double x, double z)
	{
		Wall *flor = new Wall();

		flor->a.x = x;
		flor->a.y = 0.0;
		flor->a.z = z;

		flor->b.x = x;
		flor->b.y = 0.0;
		flor->b.z = z + this->_wallWidth;

		flor->c.x = x + this->_wallWidth;
		flor->c.y = 0.0;
		flor->c.z = z + this->_wallWidth;

		flor->d.x = x + this->_wallWidth;
		flor->d.y = 0.0;
		flor->d.z = z;

		return flor;
	}

	Map::Map()
	{
		this->_loaded = false;
		this->_created = false;

		this->_wallWidth = 4.0;
		this->_wallHeight = 4.0;

		this->_walls = NULL;
		this->_wallsCount = 0;
    }

    bool Map::load(const char *filePath)
    {
		if(this->_loaded)
			return false;

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
					file >> row[j];

                map[i] = row;
            }

			std::vector<Wall*> walls;

			double z = 0.0;

			for(int i = 0; i < rowsCount; ++i)
			{
				double x = this->_wallWidth;

				for(int j = 1; j < columnsCount; ++j)
				{
					if(map[i][j - 1] != map[i][j])
						walls.push_back(this->calculateHorizontalWall(x, z));

					x += this->_wallWidth;
				}

				z += this->_wallWidth;
			}

			z = this->_wallWidth;

			for(int i = 1; i < rowsCount; ++i)
			{
				double x = this->_wallWidth;

				for(int j = 0; j < columnsCount; ++j)
				{
					if(map[i - 1][j] != map[i][j])
						walls.push_back(this->calculateVertivalWall(x, z));

					x += this->_wallWidth;
				}

				z += this->_wallWidth;
			}

			z = 0.0;

			for(int i = 0; i < rowsCount; ++i)
			{
				double x = 0.0;

				for(int j = 0; j < columnsCount; ++j)
				{
					if(map[i][j] == '0')
						walls.push_back(this->calculateFlor(x, z));

					x += this->_wallWidth;
				}

				z += this->_wallWidth;
			}

			this->_wallsCount = walls.size();
			this->_walls = new Wall*[this->_wallsCount];

			for(uint32_t i = 0; i < this->_wallsCount; ++i)
				this->_walls[i] = walls[i];

            file.close();
			this->_loaded = true;

            return true;
        }

		return false;
	}

	bool Map::create()
	{
		if(this->_loaded && this->_created == false)
		{
			this->_id = glGenLists(2);
			glNewList(this->_id, GL_COMPILE);

			for(uint32_t i = 0; i < this->_wallsCount; ++i)
			{
				Wall *wall = this->_walls[i];

				glBegin(GL_TRIANGLE_STRIP);

				glColor3d(0.0, 1.0, 0.0);
				glVertex3d(wall->b.x, wall->b.y, wall->b.z);

				glColor3d(0.0, 0.0, 1.0);
				glVertex3d(wall->c.x, wall->c.y, wall->c.z);

				glColor3d(1.0, 0.0, 0.0);
				glVertex3d(wall->a.x, wall->a.y, wall->a.z);

				glColor3d(1.0, 0.0, 1.0);
				glVertex3d(wall->d.x, wall->d.y, wall->d.z);

				glEnd();
			}

			glEndList();

			this->_created = true;
			return true;
		}

		return false;
	}

	bool Map::use()
	{
		if(this->_created)
		{
			glCallList(this->_id);
			return true;
		}

		return false;
	}
}
