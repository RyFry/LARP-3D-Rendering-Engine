#include "LightFactory.hpp"
namespace Larp
{
    std::vector<UniqueDirectional> LightFactory::s_directional_lights;
    std::vector<UniquePoint> LightFactory::s_point_lights;
    std::vector<UniqueSpot> LightFactory::s_spot_lights;

    const size_t LightFactory::sc_max_directional_lights = 1;
    const size_t LightFactory::sc_max_point_lights = 9;
    const size_t LightFactory::sc_max_spot_lights = 0;

    DirectionalLight* LightFactory::create_directional_light(glm::vec3 direction)
    {
        if (s_directional_lights.size() >= sc_max_directional_lights)
        {
            THROW_RUNTIME_ERROR("Only " << sc_max_directional_lights << " directional light(s) allowed");
        }

        s_directional_lights.push_back(UniqueDirectional(new DirectionalLight(direction.x, direction.y, direction.z)));
        return s_directional_lights.back().get();
    }

    DirectionalLight* LightFactory::create_directional_light(GLfloat x, GLfloat y, GLfloat z)
    {
        if (s_directional_lights.size() >= sc_max_directional_lights)
        {
            THROW_RUNTIME_ERROR("Only " << sc_max_directional_lights << " directional light(s) allowed");
        }

        s_directional_lights.push_back(UniqueDirectional(new DirectionalLight(x, y, z)));
        return s_directional_lights.back().get();
    }

    PointLight* LightFactory::create_point_light(glm::vec3 position)
    {
        if (s_point_lights.size() >= sc_max_point_lights)
        {
            THROW_RUNTIME_ERROR("Only " << sc_max_point_lights << " point light(s) allowed");
        }

        s_point_lights.push_back(UniquePoint(new PointLight(position.x, position.y, position.z)));
        return s_point_lights.back().get();
    }

    PointLight* LightFactory::create_point_light(GLfloat x, GLfloat y, GLfloat z)
    {
        if (s_point_lights.size() >= sc_max_point_lights)
        {
            THROW_RUNTIME_ERROR("Only " << sc_max_point_lights << " point light(s) allowed");
        }

        s_point_lights.push_back(UniquePoint(new PointLight(x, y, z)));
        return s_point_lights.back().get();
    }

    SpotLight* LightFactory::create_spot_light(glm::vec3 position)
    {
        if (s_spot_lights.size() >= sc_max_spot_lights)
        {
            THROW_RUNTIME_ERROR("Only " << sc_max_spot_lights << " spot light(s) allowed");
        }

        s_spot_lights.push_back(UniqueSpot(new SpotLight(position.x, position.y, position.z)));
        return s_spot_lights.back().get();
    }

    SpotLight* LightFactory::create_spot_light(GLfloat x, GLfloat y, GLfloat z)
    {
        if (s_spot_lights.size() >= sc_max_spot_lights)
        {
            THROW_RUNTIME_ERROR("Only " << sc_max_spot_lights << " spot light(s) allowed");
        }

        s_spot_lights.push_back(UniqueSpot(new SpotLight(x, y, z)));
        return s_spot_lights.back().get();
    }

    void LightFactory::remove_light(DirectionalLight* light)
    {
        auto func = [light] (UniqueDirectional& l) -> bool
        {
            return light == l.get();
        };

        auto it = std::find_if(s_directional_lights.begin(), s_directional_lights.end(), func);
        if (it == s_directional_lights.end())
        {
            PRINT_ERROR("Directional light not found");
        }
        else
        {
            it->reset(nullptr);
            s_directional_lights.erase(it);
        }
    }

    void LightFactory::remove_light(PointLight* light)
    {
        auto func = [light] (UniquePoint& l) -> bool
        {
            return light == l.get();
        };

        auto it = std::find_if(s_point_lights.begin(), s_point_lights.end(), func);
        if (it == s_point_lights.end())
        {
            PRINT_ERROR("Point light not found");
        }
        else
        {
            it->reset(nullptr);
            s_point_lights.erase(it);
        }
    }

    void LightFactory::remove_light(SpotLight* light)
    {
        auto func = [light] (UniqueSpot& l) -> bool
        {
            return light == l.get();
        };

        auto it = std::find_if(s_spot_lights.begin(), s_spot_lights.end(), func);
        if (it == s_spot_lights.end())
        {
            PRINT_ERROR("Spot light not found");
        }
        else
        {
            it->reset(nullptr);
            s_spot_lights.erase(it);
        }
    }
}
