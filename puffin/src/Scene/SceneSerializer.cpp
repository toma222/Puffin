
#include "SceneSerializer.h"
#include "Entity.h"
#include "Components.h"

#include "Core/FileSystem.h"

#include "json/json.hpp"

#include <fstream>
#include <iostream>
#include <memory>

namespace puffin
{

    SceneSerializer::SceneSerializer(const Ref<Scene> &scene)
        : m_Scene(scene)
    {
    }

    static void SerializeEntity(nlohmann::json &parser, Entity entity)
    {
        // ID
        parser["ID"] = {(uint64_t)entity.GetUUID()};

        // TAG
        parser["Tag"] = {entity.GetName().c_str()};

        // Transform
        components::Transform &t = entity.GetComponent<components::Transform>();
        parser["Transform"] = {t.m_rect->x, t.m_rect->y, t.m_rect->w, t.m_rect->h};

        // Image
        if (entity.HasComponent<components::Image>())
        {
            components::Image &image = entity.GetComponent<components::Image>();
            parser["Image"] = {image.m_path.c_str(), 0, 0, 0};
        }

        // Scripts
        if (entity.HasComponent<components::Script>())
        {
            components::Script &script = entity.GetComponent<components::Script>();
            parser["LocalScript"] = {script.m_path.c_str(), script.m_scriptInstance->m_moduleName.c_str()};
        }
    }

    void SceneSerializer::SerializeScene(const std::string &filepath)
    {
        PN_CORE_INFO("Serializing Scene");
        nlohmann::json parser;

        for (auto [key, e] : m_Scene->m_entities)
        {
            nlohmann::json entityParser;
            Entity entity(m_Scene.get(), e);
            SerializeEntity(entityParser, entity);

            parser[entity.GetName()] = entityParser;
        }

        // Write to the file
        std::ofstream o(filepath.c_str());
        o << std::setw(4) << parser << std::endl;
        PN_CORE_INFO("Finished Serializing the scene");
    }

    bool SceneSerializer::Deserialize(const std::string &filepath)
    {
        PN_CORE_INFO("Serializing Scene");
        std::ifstream i(filepath.c_str());
        nlohmann::json o;
        i >> o;

        for (auto &[key, value] : o.items())
        {
            Entity e = m_Scene->AddEntity(key.c_str());

            for (auto &[component, data] : value.items())
            {
                if (component == "Transform")
                {
                    components::Transform &t = e.GetComponent<components::Transform>();
                    t.m_rect->x = data[0];
                    t.m_rect->y = data[1];
                    t.m_rect->w = data[2];
                    t.m_rect->h = data[3];
                }

                if (component == "Image")
                {
                    e.AddComponent<puffin::components::Image>(data[0]);
                }

                if (component == "LocalScript")
                {
                    e.AddComponent<puffin::components::Script>(
                        GetPathFromLocal(data[0]), data[1]);
                }
            }
        }

        PN_CORE_INFO("Finished Serializing the scene");

        return true;
    }
} // namespace puffin
