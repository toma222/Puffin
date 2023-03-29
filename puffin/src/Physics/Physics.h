
#include "Scene/Components.h"

// Holds the code for the physics model
class Model
{
public:
    Model();
    ~Model();

    void CalculateLoads() { return; };
};

namespace puffin
{
    void UpdateBodyEuler();
    void CalculateBasicLoads();
    
} // namespace puffin
