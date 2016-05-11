#include "LightFactory.hpp"
namespace Larp
{
    std::vector<UniqueDirectional> LightFactory::_directional_lights;
    std::vector<UniquePoint> LightFactory::_point_lights;
    std::vector<UniqueSpot> LightFactory::_spot_lights;

    const size_t LightFactory::_max_directional_lights = 1;
    const size_t LightFactory::_max_point_lights = 9;
    const size_t LightFactory::_max_spot_lights = 0;

    DirectionalLightPtr LightFactory::create_directional_light(glm::vec3 direction)
    {
        if (_directional_lights.size() >= _max_directional_lights)
        {
            THROW_RUNTIME_ERROR("Only " << _max_directional_lights << " directional light(s) allowed");
        }

        _directional_lights.push_back(UniqueDirectional(new DirectionalLight(direction.x, direction.y, direction.z)));
        return _directional_lights.back().get();
    }

    DirectionalLightPtr LightFactory::create_directional_light(GLfloat x, GLfloat y, GLfloat z)
    {
        if (_directional_lights.size() >= _max_directional_lights)
        {
            THROW_RUNTIME_ERROR("Only " << _max_directional_lights << " directional light(s) allowed");
        }

        _directional_lights.push_back(UniqueDirectional(new DirectionalLight(x, y, z)));
        return _directional_lights.back().get();
    }

    PointLightPtr LightFactory::create_point_light(glm::vec3 position)
    {
        if (_point_lights.size() >= _max_point_lights)
        {
            THROW_RUNTIME_ERROR("Only " << _max_point_lights << " point light(s) allowed");
        }

        _point_lights.push_back(UniquePoint(new PointLight(position.x, position.y, position.z)));
        return _point_lights.back().get();
    }

    PointLightPtr LightFactory::create_point_light(GLfloat x, GLfloat y, GLfloat z)
    {
        if (_point_lights.size() >= _max_point_lights)
        {
            THROW_RUNTIME_ERROR("Only " << _max_point_lights << " point light(s) allowed");
        }

        _point_lights.push_back(UniquePoint(new PointLight(x, y, z)));
        return _point_lights.back().get();
    }

    SpotLightPtr LightFactory::create_spot_light(glm::vec3 position)
    {
        if (_spot_lights.size() >= _max_spot_lights)
        {
            THROW_RUNTIME_ERROR("Only " << _max_spot_lights << " spot light(s) allowed");
        }

        _spot_lights.push_back(UniqueSpot(new SpotLight(position.x, position.y, position.z)));
        return _spot_lights.back().get();
    }

    SpotLightPtr LightFactory::create_spot_light(GLfloat x, GLfloat y, GLfloat z)
    {
        if (_spot_lights.size() >= _max_spot_lights)
        {
            THROW_RUNTIME_ERROR("Only " << _max_spot_lights << " spot light(s) allowed");
        }

        _spot_lights.push_back(UniqueSpot(new SpotLight(x, y, z)));
        return _spot_lights.back().get();
    }

    void LightFactory::remove_light(DirectionalLightPtr light)
    {
        auto func = [light] (UniqueDirectional& l) -> bool
        {
            return light == l.get();
        };

        auto it = std::find_if(_directional_lights.begin(), _directional_lights.end(), func);
        if (it == _directional_lights.end())
        {
            PRINT_ERROR("Directional light not found");
        }
        else
        {
            it->reset(nullptr);
            _directional_lights.erase(it);
        }
    }

    void LightFactory::remove_light(PointLightPtr light)
    {
        auto func = [light] (UniquePoint& l) -> bool
        {
            return light == l.get();
        };

        auto it = std::find_if(_point_lights.begin(), _point_lights.end(), func);
        if (it == _point_lights.end())
        {
            PRINT_ERROR("Point light not found");
        }
        else
        {
            it->reset(nullptr);
            _point_lights.erase(it);
        }
    }

    void LightFactory::remove_light(SpotLightPtr light)
    {
        auto func = [light] (UniqueSpot& l) -> bool
        {
            return light == l.get();
        };

        auto it = std::find_if(_spot_lights.begin(), _spot_lights.end(), func);
        if (it == _spot_lights.end())
        {
            PRINT_ERROR("Spot light not found");
        }
        else
        {
            it->reset(nullptr);
            _spot_lights.erase(it);
        }
    }
}
