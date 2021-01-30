#include "collision.h"

bool CCollision::InterestBox(glm::vec3 A, float ASize, glm::vec3 B, float BSize){
    return (A.x - ASize <= B.x + BSize && A.x + ASize >= B.x - BSize) &&
           (A.y - ASize <= B.y + BSize && A.y + ASize >= B.y - BSize) &&
           (A.z - ASize <= B.z + BSize && A.z + ASize >= B.z - BSize);
}

bool CCollision::InterestPoint(glm::vec3 A, glm::vec3 B, float BSize){
    return (A.x >= B.x - BSize && A.x <= B.x + BSize) &&
           (A.y >= B.y - BSize && A.y <= B.y + BSize) &&
           (A.z >= B.z - BSize && A.z <= B.z + BSize);
}

float CCollision::Distance(glm::vec3& A, glm::vec3& B){
    return sqrtf(pow(A.x - B.x, 2) + pow(A.y - B.y, 2) + pow(A.z - B.z, 2));
}