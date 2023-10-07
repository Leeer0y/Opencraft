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
	Camera(glm::vec3 pos, glm::vec3 dir);
	void SetProjection(Shader* shader, float fov, float aspect, float near, float far);
	void CalculateViewMatrix(Shader* shader);
	void SetPosition(glm::vec3 pos);
	void SetDir(glm::vec3 front); // normilizes a direction vector

	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	glm::vec3 GetUp();


private:
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;

	glm::mat4 m_projection;
	glm::mat4 m_view = glm::mat4(1.0f);
};


#endif // !CAMERA_H

