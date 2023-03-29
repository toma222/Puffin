
#include "Scene/Components.h"
#include "Collision.h"
#include "Scene/Entity.h"

#include <functional>
#include <cstdint>

// Holds the code for the physics model
namespace puffin
{
    class DeltaTime
	{
	public:
		DeltaTime();
		DeltaTime(uint64_t uuid);
		DeltaTime(const DeltaTime&) = default;

		operator uint64_t() const { return m_time; }
	private:
		uint64_t m_time;
	};
}

namespace puffin
{
    class Model
    {
    public:
        std::function<void(Entity)> m_CalculateLoadsFunction;

        // ! implement this with the std::function loading and stuff
        void AttachLoadFunction()
        {

        }
    };

    // ! put these in a static class
    void UpdateBodyEuler(Entity body, DeltaTime time);
    void CalculateLoads(Entity body, DeltaTime time);

} // namespace puffin
