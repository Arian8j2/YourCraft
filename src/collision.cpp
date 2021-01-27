#include "collision.h"

bool CCollision::DoesCollide(glm::vec3 A, int ASize, glm::vec3 B, int BSize){
    return (A.x - ASize <= B.x + BSize && A.x + ASize >= B.x - BSize) &&
           (A.y - ASize <= B.y + BSize && A.y + ASize >= B.y - BSize) &&
           (A.z - ASize <= B.z + BSize && A.z + ASize >= B.z - BSize);
}