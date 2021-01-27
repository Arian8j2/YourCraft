#include <glm/glm.hpp>

class CCollision{
public:
    static bool DoesCollide(glm::vec3 A, int ASize, glm::vec3 B, int BSize);
};