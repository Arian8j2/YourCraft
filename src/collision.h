#include <glm/glm.hpp>

class CCollision{
public:
    static bool InterestBox(glm::vec3 A, float ASize, glm::vec3 B, float BSize);
    static bool InterestPoint(glm::vec3 A, glm::vec3 B, float BSize);

    static float Distance(glm::vec3& A, glm::vec3& B);
};