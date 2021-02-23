#include "collision.h"

bool CCollision::InterestBox(glm::vec3& A, glm::vec3& ASize, glm::vec3& B, glm::vec3& BSize){
    return (A.x - ASize.x <= B.x + BSize.x && A.x + ASize.x >= B.x - BSize.x) &&
           (A.y - ASize.y <= B.y + BSize.y && A.y + ASize.y >= B.y - BSize.y) &&
           (A.z - ASize.z <= B.z + BSize.z && A.z + ASize.z >= B.z - BSize.z);
}

bool CCollision::InterestPoint(glm::vec3& A, glm::vec3& B, glm::vec3& BSize){
    return (A.x >= B.x - BSize.x && A.x <= B.x + BSize.x) &&
           (A.y >= B.y - BSize.y && A.y <= B.y + BSize.y) &&
           (A.z >= B.z - BSize.z && A.z <= B.z + BSize.z);
}

float CCollision::Distance(glm::vec3& A, glm::vec3& B){
    return sqrtf(pow(A.x - B.x, 2) + pow(A.y - B.y, 2) + pow(A.z - B.z, 2));
}