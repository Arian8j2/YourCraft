#include "player.h"

CPlayer::CPlayer(CGameContext* pGameContext): m_pGameContext(pGameContext){
    m_Camera.m_Pos = glm::vec3(0.0f, 0.0f, 3.0f);
    m_Camera.m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_Camera.m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    
    glm::vec3 Right = glm::normalize(glm::cross(m_Camera.m_Front, m_Camera.m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_Camera.m_Up = glm::normalize(glm::cross(Right, m_Camera.m_Front));
}

void CPlayer::UpdateView(){
    m_View = glm::lookAt(m_Camera.m_Pos, m_Camera.m_Pos + m_Camera.m_Front, m_Camera.m_Up);
}

void CPlayer::HandleInputs(){
    GLFWwindow* pWindow = m_pGameContext->GetWindow();

    if(glfwGetKey(pWindow, GLFW_KEY_A)){
        m_Camera.m_Pos.x -= 0.1f;
    }

    if(glfwGetKey(pWindow, GLFW_KEY_D)){
        m_Camera.m_Pos.x += 0.1f;
    }

    if(glfwGetKey(pWindow, GLFW_KEY_W)){
        m_Camera.m_Pos.z -= 0.1f;
    }

    if(glfwGetKey(pWindow, GLFW_KEY_S)){
        m_Camera.m_Pos.z += 0.1f;
    }
}

void CPlayer::HandleMouseMovement(double X, double Y){
    static double s_LastX = X;
    static double s_LastY = Y;
  
    float XOffset = X - s_LastX;
    float YOffset = s_LastY - Y;

    s_LastX = X;
    s_LastY = Y;

    XOffset *= (float) MOUSE_SENSITIVITY * 0.001f;
    YOffset *= (float) MOUSE_SENSITIVITY * 0.001f;

    static float s_Yaw = -90.0f;
    static float s_Pitch = 0.0f;

    s_Yaw += XOffset;
    s_Pitch += YOffset;

    if(s_Pitch > 89.0f)
        s_Pitch = 89.0f;
    if(s_Pitch < -89.0f)
        s_Pitch = -89.0f;

    glm::vec3 Direction;
    Direction.x = cos(glm::radians(s_Yaw)) * cos(glm::radians(s_Pitch));
    Direction.y = sin(glm::radians(s_Pitch));
    Direction.z = sin(glm::radians(s_Yaw)) * cos(glm::radians(s_Pitch));
    m_Camera.m_Front = glm::normalize(Direction);
}