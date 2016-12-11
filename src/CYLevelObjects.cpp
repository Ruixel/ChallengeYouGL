#include "CYLevelObjects.h"

using namespace CYLevelLoader;

namespace CYLevelLoader
{
    std::vector<std::string>* properties = new std::vector<std::string>();
}

void CYLevelLoader::addNewObject(const std::string& obj_name, std::vector<std::string>* obj_properties,
                                  std::vector<polygon>* polys)
{
    properties = obj_properties;
    if (obj_name == "Floor")
    {
        if (properties->at(9) == "2")
            return;

        addFloor(ptof(0),  ptof(1),  ptof(2), ptof(3), ptof(4), ptof(5), ptof(6), ptof(7),
                 ptoi(11), ptos(8), ptos(10), polys);

    }

    if (obj_name == "Plat")
    {
        float p_height = ptoi(5) + ((ptoi(4) - 1.f) / 4) + 0.001f;

        int size       = ptoi(2);
        switch (size)
        {
            case 3:  size = 4; break;
            case 4:  size = 8; break;
            default: size = size;
        }

        int x_min      = ptof(0) - size*5;
        int x_max      = ptof(0) + size*5;
        int y_min      = ptof(1) - size*5;
        int y_max      = ptof(1) + size*5;

        addHorizontalQuad(x_min, y_max, x_max, y_max, x_max, y_min, x_min, y_min, p_height, 0, ptos(3), polys);
        addHorizontalQuad(x_min, y_min, x_max, y_min, x_max, y_max, x_min, y_max, p_height, 0, ptos(3), polys);
    }

    if (obj_name == "DiaPlat")
    {
        float p_height = ptof(5) + ((ptoi(4) - 1.f) / 4) + 0.001f;

        int size       = ptoi(2);
        switch (size)
        {
            case 3:  size = 4; break;
            case 4:  size = 8; break;
            default: size = size;
        }

        size *= 5;

        int x_min      = stoi(properties->at(0)) - size;
        int x_max      = stoi(properties->at(0)) + size;
        int y_min      = stoi(properties->at(1)) - size;
        int y_max      = stoi(properties->at(1)) + size;

        addHorizontalQuad(x_min+size, y_max, x_max, y_max-size, x_max-size, y_min, x_min, y_min+size, p_height, 0, ptos(3), polys);
        addHorizontalQuad(x_min, y_min+size, x_max-size, y_min, x_max, y_max-size, x_min+size, y_max, p_height, 0, ptos(3), polys);
    }

    if (obj_name == "TriPlat")
    {
        float p_height = ptof(6) + ((ptoi(5) - 1.f) / 4) + 0.001f;

        int size       = ptoi(2);
        switch (size)
        {
            case 3:  size = 4; break;
            case 4:  size = 8; break;
            default: size = size;
        }

        size *= 5;

        int first_tri, second_tri;
        switch(ptoi(4))
        {
            case 1: first_tri = 1; second_tri = 2; break;
            case 2: first_tri = 3; second_tri = 4; break;
            case 3: first_tri = 2; second_tri = 1; break;
            case 4: first_tri = 4; second_tri = 3; break;
        }

        int x_min      = ptoi(0) - size;
        int x_max      = ptoi(0) + size;
        int y_min      = ptoi(1) - size;
        int y_max      = ptoi(1) + size;

        addHorizontalQuad(x_min, y_max, x_max, y_max, x_max, y_min, x_min, y_min, p_height, first_tri,  ptos(3), polys);
        addHorizontalQuad(x_min, y_min, x_max, y_min, x_max, y_max, x_min, y_max, p_height, second_tri, ptos(3), polys);
    }

    if (obj_name == "Ramp")
    {
        float min_height = ptof(4);
        float max_height = (ptof(4)+1);

        int x_1          = ptof(0);
        int y_1          = ptof(1);

        sf::Vector2f length, width;
        int direction    = ptoi(2);
        switch (direction)
        {
            // Vertical & Horizontal Ramps
            case 1: width  = {10, 0};
                    length = {0, 20};
                    x_1    -= 5;
                    break;
            case 2: width  = {10, 0};
                    length = {0, -20};
                    x_1    -= 5;
                    break;
            case 3: width  = {0, 10};
                    length = {-20, 0};
                    x_1    += 20;
                    y_1    -= 5;
                    break;
            case 4: width  = {0, 10};
                    length = {20, 0};
                    x_1    -= 20;
                    y_1    -= 5;
                    break;

            // Diagonal Ramps
            case 5: width  = {10, -10};
                    length = {-15, 15};
                    x_1    += 10;
                    y_1    += 5;
                    break;
            case 6: width  = {10, 10};
                    length = {-15, -15};
                    x_1    += 10;
                    y_1    -= 5;
                    break;
            case 7: width  = {-10, 10};
                    length = {15, -15};
                    x_1    -= 10;
                    y_1    -= 5;
                    break;
            case 8: width  = {10, 10};
                    length = {15, 15};
                    x_1    -= 20;
                    y_1    -= 5;
                    break;
        }

        addRamp(x_1, y_1, width, length, min_height, max_height, false, ptos(3), polys);
        addRamp(x_1, y_1, width, length, min_height, max_height, true, ptos(3), polys);
    }

    if (obj_name == "walls")
    {
        float height = ptof(7);
        float height_max, height_min;

        switch(stoi(properties->at(6)))
        {
            case 2:  height_max = height + 3/4.f;  height_min = height; break;
            case 3:  height_max = height + 2/4.f;  height_min = height; break;
            case 4:  height_max = height + 1/4.f;  height_min = height; break;

            case 5:  height_max = height + 2/4.f;  height_min = height + 1/4.f; break;
            case 6:  height_max = height + 3/4.f;  height_min = height + 2/4.f; break;
            case 7:  height_max = height + 4/4.f;  height_min = height + 3/4.f; break;

            case 8:  height_max = height + 4/4.f;  height_min = height + 2/4.f; break;
            case 9:  height_max = height + 4/4.f;  height_min = height + 1/4.f; break;
            case 10: height_max = height + 3/4.f;  height_min = height + 1/4.f; break;

            default: height_max = height + 4/4.f;  height_min = height; break;
        }

        float x_1 = ptof(2);
        float x_2 = x_1 + ptof(0);
        float y_1 = ptof(3);
        float y_2 = y_1 + ptof(1);

        addVerticalQuad(x_1, y_1, x_2, y_2, height_min, height_max, 0, true, ptos(4), polys);
        addVerticalQuad(x_1, y_1, x_2, y_2, height_min, height_max, 0, false, ptos(5), polys);
    }

    if (obj_name == "TriWall")
    {
        float height_min = ptof(5);
        float height_max = height_min + 1.f;


        float x_1 = ptof(0);
        float y_1 = ptof(1);
        float x_2, y_2;

        int dir = ptoi(4);
        switch (dir)
        {
            case 1: x_2 = x_1;  y_2 = y_1 + 20;     break;
            case 2: x_2 = x_1;  y_2 = y_1 - 20;     break;
            case 3: x_2 = x_1 + 20;  y_2 = y_1;     break;
            case 4: x_2 = x_1 - 20;  y_2 = y_1;     break;

            case 5: x_2 = x_1 + 15;  y_2 = y_1 - 15;     break;
            case 6: x_2 = x_1 + 15;  y_2 = y_1 + 15;     break;
            case 7: x_2 = x_1 - 15;  y_2 = y_1 + 15;     break;
            case 8: x_2 = x_1 - 15;  y_2 = y_1 - 15;     break;
        }

        if (ptoi(2) == 1)
        {
            addVerticalQuad(x_1, y_1, x_2, y_2, height_min, height_max, 4, true, ptos(3), polys);
            addVerticalQuad(x_1, y_1, x_2, y_2, height_min, height_max, 3, false, ptos(3), polys);
        } else {
            addVerticalQuad(x_1, y_1, x_2, y_2, height_min, height_max, 2, true, ptos(3), polys);
            addVerticalQuad(x_1, y_1, x_2, y_2, height_min, height_max, 1, false, ptos(3), polys);
        }
    }

    if (obj_name == "Pillar")
    {
        float height = ptof(6);
        float height_max, height_min;

        switch(ptoi(5))
        {
            case 2:  height_max = height + 3/4.f;  height_min = height; break;
            case 3:  height_max = height + 2/4.f;  height_min = height; break;
            case 4:  height_max = height + 1/4.f;  height_min = height; break;

            case 5:  height_max = height + 2/4.f;  height_min = height + 1/4.f; break;
            case 6:  height_max = height + 3/4.f;  height_min = height + 2/4.f; break;
            case 7:  height_max = height + 4/4.f;  height_min = height + 3/4.f; break;

            case 8:  height_max = height + 4/4.f;  height_min = height + 2/4.f; break;
            case 9:  height_max = height + 4/4.f;  height_min = height + 1/4.f; break;
            case 10: height_max = height + 3/4.f;  height_min = height + 1/4.f; break;

            default: height_max = height + 4/4.f;  height_min = height; break;
        }

        height_max -= 0.001f;
        height_min += 0.001f;

        float size = ptof(4);
        switch ((int)size)
        {
            case 1: size = 0.25f; break;
            case 2: size = 0.50f; break;
            case 3: size = 1.00f; break;
            case 4: size = 1.50f; break;
            case 5: size = 2.00f; break;
        }

        float x = ptof(0);
        float y = ptof(1);
        float x_1 = x - size;
        float x_2 = x + size;
        float y_1 = y - size;
        float y_2 = y + size;

        // WALLS
        addVerticalQuad(x_2, y_1, x_2, y_2, height_min, height_max, 0, true, ptos(3), polys);
        addVerticalQuad(x_1, y_2, x_1, y_1, height_min, height_max, 0, true, ptos(3), polys);
        addVerticalQuad(x_1, y_1, x_2, y_1, height_min, height_max, 0, true, ptos(3), polys);
        addVerticalQuad(x_2, y_2, x_1, y_2, height_min, height_max, 0, true, ptos(3), polys);

        // Top & Bottom
        addHorizontalQuad(x_2, y_2, x_1, y_2, x_1, y_1, x_2, y_1, height_min , 0, ptos(3), polys);
        addHorizontalQuad(x_2, y_1, x_1, y_1, x_1, y_2, x_2, y_2, height_max, 0, ptos(3), polys);
    }
}

