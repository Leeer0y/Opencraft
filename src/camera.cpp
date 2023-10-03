#include "camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 dir) {
	m_cameraPos = pos;
	m_cameraFront = dir;

	// defualt values
	m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::SetProjection(Shader* shader, float fov, float aspect, float near, float far) {
	m_projection = glm::perspective(glm::radians(fov), aspect, near, far);
	shader->setMat4("projection", m_projection);
}

void Camera::CalculateViewMatrix(Shader* shader) {
	m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	shader->setMat4("view", m_view);
}

void Camera::SetPosition(glm::vec3 pos) {
	m_cameraPos = pos;
}

glm::vec3 Camera::GetPosition() {
	return m_cameraPos;
}

glm::vec3 Camera::GetFront() {
	return m_cameraFront;
}

glm::vec3 Camera::GetUp() {
	return m_cameraUp;
}


