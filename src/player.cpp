#include "player.h"
#include <algorithm>

CPlayer::CPlayer(CGameContext* pGameContext): m_pGameContext(pGameContext){
    m_Camera.m_Pos = glm::vec3(0.0f, 1.5f, 3.0f);
    m_Camera.m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_Camera.m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_Camera.m_Right = glm::normalize(glm::cross(m_Camera.m_Front, m_Camera.m_WorldUp));
    m_Camera.m_Up = glm::normalize(glm::cross(m_Camera.m_Right, m_Camera.m_Front));
}

void CPlayer::UpdateView(){
    m_View = glm::lookAt(m_Camera.m_Pos, m_Camera.m_Pos + m_Camera.m_Front, m_Camera.m_Up);    
}

void CPlayer::HandleInputs(float DeltaTime){
    GLFWwindow* pWindow = m_pGameContext->GetWindow();
    float Boost = 1.0f;

    if(glfwGetKey(pWindow, GLFW_KEY_LEFT_SHIFT))
        Boost = 4.0f;
    else
        Boost = 1.0f;

    if(glfwGetKey(pWindow, GLFW_KEY_A)){
        m_Camera.m_Pos -= m_Camera.m_Right * (SPEED / 100.0f * DeltaTime) * Boost;
    }

    if(glfwGetKey(pWindow, GLFW_KEY_D)){
        m_Camera.m_Pos += m_Camera.m_Right * (SPEED / 100.0f * DeltaTime) * Boost;
    }

    if(glfwGetKey(pWindow, GLFW_KEY_W)){
        float Y = m_Camera.m_Pos.y;
        m_Camera.m_Pos += m_Camera.m_Front * (SPEED / 100.0f * DeltaTime) * Boost;
        m_Camera.m_Pos.y = Y;
    }

    if(glfwGetKey(pWindow, GLFW_KEY_S)){
        float Y = m_Camera.m_Pos.y;
        m_Camera.m_Pos -= m_Camera.m_Front * (SPEED / 100.0f * DeltaTime) * Boost;
        m_Camera.m_Pos.y = Y;
    }

    // mouse
    static float s_LastLeftClick = 0;

    if(s_LastLeftClick < glfwGetTime() && glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_1) && m_DoesSelected){
        for(int i=0; i < m_pGameContext->m_aBlockInfos.size(); i++){
            if(m_pGameContext->m_aBlockInfos[i].m_Pos == m_SelectedBlock){
                m_pGameContext->m_aBlockInfos.erase(m_pGameContext->m_aBlockInfos.begin() + i);
                break;
            }
        }

        s_LastLeftClick = glfwGetTime() + 0.2f;
    }
}

void CPlayer::HandleMouseMovement(double X, double Y){
    static double s_LastX = X;
    static double s_LastY = Y;
    static float s_MouseSens = m_pGameContext->GetSettingValue("mouse_sens").GetInt();
  
    float XOffset = X - s_LastX;
    float YOffset = s_LastY - Y;

    s_LastX = X;
    s_LastY = Y;

    XOffset *= (float) s_MouseSens * 0.001f;
    YOffset *= (float) s_MouseSens * 0.001f;

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

    m_Camera.m_Right = glm::normalize(glm::cross(m_Camera.m_Front, m_Camera.m_WorldUp));
    m_Camera.m_Up = glm::normalize(glm::cross(m_Camera.m_Right, m_Camera.m_Front));
}