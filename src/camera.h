#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"


class Camera {
public:
	float cameraSpeed;

	Camera(glm::vec3 pos, glm::vec3 dir);
	void SetProjection(Shader* shader, float fov, float aspect, float near, float far);
	void CalculateViewMatrix(Shader* shader);

private:
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;

	glm::mat4 m_projection;
	glm::mat4 m_view = glm::mat4(1.0f);
};


#endif // !CAMERA_H

