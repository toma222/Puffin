
#include "puffin/core/Base.h"
#include "puffin/events/Event.h"
#include "puffin/events/MouseEvent.h"
#include "Graphics.h"
#include "puffin/core/Logging.h"
#include <glm/glm.hpp>

// Default Values
#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 2.5f
#define SENSITIVITY 0.1f
#define ZOOM 45.0f

namespace PN
{
    namespace graphics
    {
        class PUFFIN_API PerspectiveCamera
        {
        private:
            glm::vec3 m_position;
            glm::vec3 m_front;
            glm::vec3 m_up;
            glm::vec3 m_right;
            glm::vec3 m_worldUp;

            float m_moveSpeed;
            float m_rotateSpeed;

            glm::vec2 m_windowSize;

            float m_yaw;
            float m_pitch;
            float m_zoom;

        public:
            PerspectiveCamera(glm::vec2 windowSize, glm::vec3 position, glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float zoom = ZOOM)
            {
                PN_CORE_INFO("Creating perspective camera");

                m_position = position;
                m_windowSize = windowSize;

                m_worldUp = worldUp;
                m_front = glm::vec3(0, 0, -1);

                // printf("%f %f %f", m_worldUp.x, m_worldUp.y, m_worldUp.z);

                m_yaw = YAW;
                m_pitch = PITCH;
                m_zoom = ZOOM;

                UpdateCameraVectors();
            }

            bool OnMouseMoveEvent(MouseEvent *event);
            void OnEvent(Event *event);

            glm::mat4 GetCameraProjectionMatrix();
            void UpdateCameraVectors();

            void Translate(glm::vec3 moveBy);
            void Roatate(glm::vec3 rotateBy);
        };
    } // namespace graphics

} // namespace PN
