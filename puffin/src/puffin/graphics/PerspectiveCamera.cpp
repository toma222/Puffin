
#include "puffin/core/Base.h"
#include "puffin/events/Event.h"
#include "Graphics.h"
#include "puffin/core/Logging.h"
#include "PerspectiveCamera.h"
#include "puffin/events/Event.h"
#include "puffin/events/MouseEvent.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PN
{
    namespace graphics
    {
        void PerspectiveCamera::Translate(glm::vec3 moveBy)
        {
            m_position += m_right * moveBy.x;
            m_position += m_front * moveBy.y;
            m_position += m_up * moveBy.z;

            UpdateCameraVectors();
        }

        glm::mat4 PerspectiveCamera::GetCameraProjectionMatrix()
        {
            glm::mat4 proj = glm::perspective(glm::radians(m_zoom), (float)m_windowSize.y / (float)m_windowSize.x, 0.1f, 100.0f);
            glm::mat4 look = glm::lookAt(m_position, m_position + m_front, m_up);
            glm::mat4 model = glm::mat4(1.0f);

            return proj * look;
        }

        void PerspectiveCamera::UpdateCameraVectors()
        {
            // Calculates the front vector
            glm::vec3 front;
            front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
            front.y = sin(glm::radians(m_pitch));
            front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
            m_front = glm::normalize(front);

            // also re-calculate the Right and Up vector
            m_right = glm::normalize(glm::cross(m_front, m_worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            m_up = glm::normalize(glm::cross(m_right, m_front));
        }

        bool PerspectiveCamera::OnMouseMoveEvent(MouseEvent *event)
        {
            printf("Mouse event %i   %i", event->GetMouseX(), event->GetMouseY());

            return true;
        }

        void PerspectiveCamera::OnEvent(Event *event)
        {
            EventDispatcher *dispatch = new EventDispatcher(event);

            // Check if the event is a mouse event
            if (event->GetEventType() == MOUSEMOVE)
            {
                // dispatch->Dispatch<MouseEvent>(OnMouseMoveEvent);
            }
        }
    } // namespace graphics

} // namespace PN
