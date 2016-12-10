#include "WorldSpawn.h"

WorldSpawn::WorldSpawn(const char* levelPath, StaticShader& sh, Camera* camera)
//:   Entity(Loader::loadToVAO(v, i, t, v), Loader::loadTexture("iceman.jpg"))
:   shader(&sh)
,   m_camera(camera)
{
    CYLevelLoader::level_textures = &this->level_textures;
    level_objs = CYLevelLoader::loadFromFile(levelPath);
}

/*void WorldSpawn::createStruct(const std::string& obj_name, std::vector<std::string>* properties)
{
    if (obj_name == "Floor")
    {
        if (properties->at(9) == "2")
            return;

        float f_height = stof(properties->at(11))*HEIGHT;

        polygon f1, f2;
        f1.vertex[0]  = glm::vec3((stof(properties->at(0))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(1)) - 200)  / WORLD_SIZE);
        f1.vertex[1]  = glm::vec3((stof(properties->at(2))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(3)) - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((stof(properties->at(4))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(5)) - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((stof(properties->at(6))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(7)) - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(8))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(8));
        } else {
            f1.textureID = level_textures.getPlatformTexture(stoi(properties->at(8)));
        }

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);

        if ((properties->at(10))[0] == 'c') {
            f2.textureID = CY_COLOR;
            f2.colors    = extractColor(properties->at(10));
        } else {
            f2.textureID = level_textures.getPlatformTexture(stoi(properties->at(10)));
        }

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "Plat")
    {
        float p_height = stof(properties->at(5))*HEIGHT + ((stof(properties->at(4)) - 1.f) / 4)*HEIGHT;

        int size       = stoi(properties->at(2));
        switch (size)
        {
            case 3:  size = 4; break;
            case 4:  size = 8; break;
            default: size = size;
        }

        int x_min      = stoi(properties->at(0)) - size*5;
        int x_max      = stoi(properties->at(0)) + size*5;
        int y_min      = stoi(properties->at(1)) - size*5;
        int y_max      = stoi(properties->at(1)) + size*5;

        polygon f1, f2;
        f1.vertex[0]  = glm::vec3((x_min   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_max - 200)  / WORLD_SIZE);
        f1.vertex[1]  = glm::vec3((x_max   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_max - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_max   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_min - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_min   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_min - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(3))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(3));
            f2.colors    = f1.colors;
        } else {
            f1.textureID = level_textures.getPlatformTexture(stoi(properties->at(3)));
        }

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "DiaPlat")
    {
        float p_height = stof(properties->at(5))*HEIGHT + ((stof(properties->at(4)) - 1.f) / 4)*HEIGHT;

        int size       = stoi(properties->at(2));
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

        polygon f1, f2;
        f1.vertex[0]  = glm::vec3((x_min+size - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_max      - 200)  / WORLD_SIZE);
        f1.vertex[1]  = glm::vec3((x_max      - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_max-size - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_max-size - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_min      - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_min      - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_min+size - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(3))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(3));
            f2.colors    = f1.colors;
        } else {
            f1.textureID = level_textures.getPlatformTexture(stoi(properties->at(3)));
        }

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "TriPlat")
    {
        float p_height = stof(properties->at(6))*HEIGHT + ((stof(properties->at(5)) - 1.f) / 4)*HEIGHT;

        int size       = stoi(properties->at(2));
        switch (size)
        {
            case 3:  size = 4; break;
            case 4:  size = 8; break;
            default: size = size;
        }

        int x_min      = stoi(properties->at(0)) - size*5;
        int x_max      = stoi(properties->at(0)) + size*5;
        int y_min      = stoi(properties->at(1)) - size*5;
        int y_max      = stoi(properties->at(1)) + size*5;

        polygon f1, f2;
        f1.vertex[0]  = glm::vec3((x_min   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_max - 200)  / WORLD_SIZE);
        f1.vertex[1]  = glm::vec3((x_max   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_max - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_max   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_min - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_min   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_min - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        int tri = stoi(properties->at(4));
        switch(tri)
        {
            case 1: f1.triwall = 1; f2.triwall = 2; break;
            case 2: f1.triwall = 3; f2.triwall = 4; break;
            case 3: f1.triwall = 2; f2.triwall = 1; break;
            case 4: f1.triwall = 4; f2.triwall = 3; break;
        }

        if ((properties->at(3))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(3));
            f2.colors    = f1.colors;
        } else {
            f1.textureID = level_textures.getPlatformTexture(stoi(properties->at(3)));
        }

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "Ramp")
    {
        polygon f1, f2;

        float min_height = stof(properties->at(4))*HEIGHT;
        float max_height = (stof(properties->at(4))+1)*HEIGHT;

        int x_1          = stoi(properties->at(0));
        int y_1          = stoi(properties->at(1));

        sf::Vector2f length, width;
        int direction    = stoi(properties->at(2));
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

        f1.vertical    = true;
        f1.v_length    = sqrt(pow(length.x, 2) + pow(length.y, 2));

        f1.vertex[1]  = glm::vec3((x_1 + length.x            - 200)  / WORLD_SIZE, max_height, (y_1                      - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_1 + width.x + length.x  - 200)  / WORLD_SIZE, max_height, (y_1 + width.y            - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_1 + width.x             - 200)  / WORLD_SIZE, min_height, (y_1 + width.y + length.y - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x_1                       - 200)  / WORLD_SIZE, min_height, (y_1 + length.y           - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(3))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(3));
            f2.colors    = f1.colors;
        } else {
            f1.textureID = level_textures.getPlatformTexture(stoi(properties->at(3)));
        }

        f1.is_ramp = true;
        f2.is_ramp = true;

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;
        f2.vertical   = true;
        f2.v_length   = f1.v_length;

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "walls")
    {
        polygon f1, f2;
        float height = stof(properties->at(7));
        float height_max, height_min;

        //std::cout << "Z_IND: " << stoi(properties->at(6)) << std::endl;

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
            case 10:  height_max = height + 3/4.f;  height_min = height + 1/4.f; break;

            default: height_max = height + 4/4.f;  height_min = height; break;
        }

        height_max *= HEIGHT; height_min *= HEIGHT;

        int x_1 = stof(properties->at(2));
        int x_2 = x_1 + stof(properties->at(0));
        int y_1 = stof(properties->at(3));
        int y_2 = y_1 + stof(properties->at(1));

        f1.vertical    = true;
        f1.v_length    = sqrt(pow(x_2-x_1, 2) + pow(y_2-y_1, 2));
        f1.v_x = x_1;

        f1.vertex[1]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max, (y_1 - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min, (y_1 - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(4))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(4));
        } else {
            f1.textureID = level_textures.getWallTexture(stoi(properties->at(4)));
        }

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;
        f2.vertical   = true;
        f2.v_length   = f1.v_length;
        f2.v_x        = x_1;

        if ((properties->at(5))[0] == 'c') {
            f2.textureID = CY_COLOR;
            f2.colors    = extractColor(properties->at(5));
        } else {
            f2.textureID = level_textures.getWallTexture(stoi(properties->at(5)));
        }

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "Pillar")
    {
        polygon f1, f2, f3, f4, f5, f6;
        float height = stof(properties->at(6));
        float height_max, height_min;

        switch(stoi(properties->at(5)))
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

        height_max *= HEIGHT; height_min *= HEIGHT;

        float size = stof(properties->at(4));
        switch ((int)size)
        {
            case 1: size = 0.25f; break;
            case 2: size = 0.50f; break;
            case 3: size = 1.00f; break;
            case 4: size = 1.50f; break;
            case 5: size = 2.00f; break;
        }

        int x = stof(properties->at(0));
        int y = stof(properties->at(1));
        float x_1 = x - size;
        float x_2 = x + size;
        float y_1 = y - size;
        float y_2 = y + size;

        // VERTICAL WALLS
        f1.vertex[1]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max, (y_1 - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min, (y_1 - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);
        f1.vertical   = true;
        f1.v_length   = size * 2;
        f1.v_x        = 0.91f;

        f2.vertex[1]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max, (y_2 - 200)  / WORLD_SIZE);
        f2.vertex[2]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max, (y_1 - 200)  / WORLD_SIZE);
        f2.vertex[3]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min, (y_1 - 200)  / WORLD_SIZE);
        f2.vertex[0]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min, (y_2 - 200)  / WORLD_SIZE);
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.vertical   = true;
        f2.v_length   = size * 2;
        f2.v_x        = 0.91f;

        f3.vertex[1]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max, (y_1 - 200)  / WORLD_SIZE);
        f3.vertex[2]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max, (y_1 - 200)  / WORLD_SIZE);
        f3.vertex[3]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min, (y_1 - 200)  / WORLD_SIZE);
        f3.vertex[0]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min, (y_1 - 200)  / WORLD_SIZE);
        f3.normal     = glm::cross(f3.vertex[2] - f3.vertex[1], f3.vertex[3] - f3.vertex[1]);
        f3.vertical   = true;
        f3.v_length   = size * 2;
        f3.v_x        = 0.91f;

        f4.vertex[1]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max, (y_2 - 200)  / WORLD_SIZE);
        f4.vertex[2]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max, (y_2 - 200)  / WORLD_SIZE);
        f4.vertex[3]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min, (y_2 - 200)  / WORLD_SIZE);
        f4.vertex[0]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min, (y_2 - 200)  / WORLD_SIZE);
        f4.normal     = glm::cross(f4.vertex[2] - f4.vertex[1], f4.vertex[3] - f4.vertex[1]);
        f4.vertical   = true;
        f4.v_length   = size * 2;
        f4.v_x        = 0.91f;

        // HORIZONTAL PLATS
        f5.vertex[0]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min+(0.001*HEIGHT), (y_2 - 200)  / WORLD_SIZE);
        f5.vertex[1]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min+(0.001*HEIGHT), (y_2 - 200)  / WORLD_SIZE);
        f5.vertex[2]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min+(0.001*HEIGHT), (y_1 - 200)  / WORLD_SIZE);
        f5.vertex[3]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min+(0.001*HEIGHT), (y_1 - 200)  / WORLD_SIZE);
        f5.normal     = glm::cross(f5.vertex[2] - f5.vertex[1], f5.vertex[3] - f5.vertex[1]);

        f6.vertex[0]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max-(0.001*HEIGHT), (y_1 - 200)  / WORLD_SIZE);
        f6.vertex[1]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max-(0.001*HEIGHT), (y_1 - 200)  / WORLD_SIZE);
        f6.vertex[2]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max-(0.001*HEIGHT), (y_2 - 200)  / WORLD_SIZE);
        f6.vertex[3]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max-(0.001*HEIGHT), (y_2 - 200)  / WORLD_SIZE);
        f6.normal     = glm::cross(f6.vertex[2] - f6.vertex[1], f6.vertex[3] - f6.vertex[1]);

        // Texture all polygons at once
        if ((properties->at(3))[0] == 'c') {
            f1.textureID = CY_COLOR; f2.textureID = CY_COLOR;
            f3.textureID = CY_COLOR; f4.textureID = CY_COLOR;
            f5.textureID = CY_COLOR; f6.textureID = CY_COLOR;

            f1.colors = extractColor(properties->at(3));
            f2.colors = f1.colors;   f3.colors = f1.colors;   f4.colors = f1.colors;
            f5.colors = f1.colors;   f6.colors = f1.colors;
        } else {
            f1.textureID = level_textures.getWallTexture(stoi(properties->at(3)));
            f2.textureID = f1.textureID;    f3.textureID = f1.textureID;    f4.textureID = f1.textureID;
            f5.textureID = f1.textureID;    f6.textureID = f1.textureID;
        }

        polys.push_back(f1); polys.push_back(f2);
        polys.push_back(f3); polys.push_back(f4);
        polys.push_back(f5); polys.push_back(f6);
    }

    if (obj_name == "TriWall")
    {
        polygon f1, f2;
        float height = stof(properties->at(5));
        float height_max = height       *HEIGHT;
        float height_min = (height + 1) *HEIGHT;

        int x_1 = stof(properties->at(0));
        int y_1 = stof(properties->at(1));
        int x_2, y_2;

        int dir = stoi(properties->at(4));
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

        if (stoi(properties->at(2)) == 1) {
            f1.triwall = 1; f2.triwall = 2;
        } else {
            f1.triwall = 3; f2.triwall = 4;
        }

        f1.vertical    = true;
        f1.v_length    = sqrt(pow(x_2-x_1, 2) + pow(y_2-y_1, 2));
        f1.v_x = x_1;

        f1.vertex[1]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max, (y_1 - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min, (y_1 - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(3))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(3));
            f2.colors    = f1.colors;
        } else {
            f1.textureID = level_textures.getWallTexture(stoi(properties->at(3)));
        }

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;
        f2.vertical   = true;
        f2.v_length   = f1.v_length;
        f2.v_x        = x_1;

        f2.textureID = f1.textureID;

        polys.push_back(f1);
        polys.push_back(f2);
    }
}*/

void WorldSpawn::draw()
{
    shader->loadTransformationMatrix(transformationMatrix);

    glActiveTexture(GL_TEXTURE0);

    texture_id previous_texture = CY_UNASSIGNED;
    for (auto& chunk : level_objs.chunks)
    {
        level_textures.bindTexture(chunk.textureID);

        glBindVertexArray(chunk.meshID->getVaoID());
        glDrawElements(GL_TRIANGLES, chunk.meshID->getVertexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }


    /*previous_texture = CY_UNASSIGNED;
    for (auto& poly : trans_polys)
    {
        if (poly.textureID != previous_texture)
        {
            level_textures.bindTexture(poly.textureID);
            previous_texture = poly.textureID;
        }

        glBindVertexArray(poly.meshID->getVaoID());
        glDrawElements(GL_TRIANGLES, poly.meshID->getVertexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }*/
}

void WorldSpawn::update(const float dt)
{
    this->position  = glm::vec3(0, -.6f, 0);
    this->scale     = 100.0f;

    createTransformationMatrix();
}
