#include "Camera.h"

Camera::Camera()
{
    camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
    calculateViewMatrx();
}

Camera::~Camera()
{

}

void Camera::updatePitchYaw(const float x_offset, const float y_offset)
{
    yaw += x_offset * 0.1;
    pitch += y_offset * 0.1;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    calculateViewMatrx();
    std::cout << pitch << ", " << yaw << std::endl;
}

void Camera::updateCameraPosition(glm::vec2 dir)
{
    camera_pos += dir.x  * camera_direction * 0.05f;
    camera_pos += dir.y  * glm::normalize(glm::cross(camera_direction, camera_up)) * 0.05f;
    calculateViewMatrx();
    std::cout << camera_pos.x << ", " << camera_pos.z << std::endl;
}

void Camera::calculateViewMatrx()
{
    calculateCameraTarget();
    calculateCameraDirection();
    calculateRightVector();
    calculateCameraUpVector();

    view = glm::lookAt(camera_pos, camera_pos + camera_direction, camera_up);
}

void Camera::calculateCameraTarget()
{
    camera_target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_target.y = sin(glm::radians(pitch));
    camera_target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_target = glm::normalize(camera_target);
}

void Camera::calculateCameraDirection()
{
    camera_direction = glm::normalize(camera_pos - camera_target);
}

void Camera::calculateRightVector()
{
    camera_right = glm::normalize(glm::cross(up, camera_direction));
}

void Camera::calculateCameraUpVector()
{
    camera_up = glm::cross(camera_direction, camera_right);
}
