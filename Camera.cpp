#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {

        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraPosition - cameraTarget);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraUpDirection, this->cameraFrontDirection));
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {

        return glm::lookAt(this->cameraPosition, this->cameraTarget, this->cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {

        switch (direction) {
        case MOVE_FORWARD:
            this->cameraPosition += this->cameraFrontDirection * speed;
            break;
        case MOVE_BACKWARD:
            this->cameraPosition -= this->cameraFrontDirection * speed;
            break;
        case MOVE_LEFT:
            this->cameraPosition -= this->cameraRightDirection * speed;
            break;
        case MOVE_RIGHT:
            this->cameraPosition += this->cameraRightDirection * speed;
            break;
        }

        //cameraFrontDirection = glm::normalize(cameraPosition - cameraTarget);
        this->cameraTarget = this->cameraFrontDirection + this->cameraPosition;
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraUpDirection, this->cameraFrontDirection));
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        this->cameraFrontDirection = glm::normalize(direction);
        this->cameraTarget = this->cameraFrontDirection + this->cameraPosition;
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraUpDirection, this->cameraFrontDirection));
    }
}