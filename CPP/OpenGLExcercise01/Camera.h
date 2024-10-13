#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


//namespace glm
//{
	class Camera
	{
	public:
		Camera(glm::vec3 position, glm::vec3 target , glm::vec3 worldup);
		Camera(glm::vec3 position, float pitch , float yaw , glm::vec3 worldup);

		glm::vec3 Positon;
		glm::vec3 CameraZ;
		glm::vec3 Right;
		glm::vec3 Up;
		glm::vec3 WorldUp;
		float Pitch;
		float Yaw;
		float offsetX = 0.01f;
		float offsetY = 0.01f;
		float speedZ = 0;
		float speedR = 0;

		glm::mat4 GetViewMatrix();
		void ProcessMouseMovement(float deltaX, float deltaY);
		void UpdateCameraPos();

	private:
		void UpdateCameraVectors();

	};
//}

