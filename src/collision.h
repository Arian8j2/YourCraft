#include <glm/glm.hpp>

class CCollision{
public:
    static bool InterestBox(glm::vec3& A, glm::vec3& ASize, glm::vec3& B, glm::vec3& BSize);
    static bool InterestPoint(glm::vec3& A, glm::vec3& B, glm::vec3& BSize);

    static float Distance(glm::vec3& A, glm::vec3& B);
};