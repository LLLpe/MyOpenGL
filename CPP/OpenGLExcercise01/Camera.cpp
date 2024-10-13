#include "Camera.h"

//namespace glm
//{
	Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
	{
		Positon = position;
		WorldUp = worldup;
		//Z正方向
		CameraZ = normalize(position - target);
		Right = normalize(cross(WorldUp, CameraZ));
		Up = normalize(cross(CameraZ, Right));

	}

	Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
	{
		Positon = position;
		WorldUp = worldup;
		Pitch = pitch;
		Yaw = yaw;
		//计算出摄像机拍摄方向的欧拉角
		CameraZ.x = sin(Yaw) * cos(Pitch);
		CameraZ.y = sin(Pitch);
		CameraZ.z = cos(Yaw) * cos(Pitch);
		//取反得到此时摄像机的Z轴向量
		CameraZ = -CameraZ;
		Right = normalize(cross(WorldUp, CameraZ));
		Up = normalize(cross(CameraZ, Right));
	}

	glm::mat4 Camera::GetViewMatrix() {
		return lookAt(Positon, Positon - CameraZ , WorldUp);
	}

	void Camera::ProcessMouseMovement(float xoffset, float yoffset)
	{

		float sensitivity = 0.001;
		Pitch += yoffset * sensitivity;
		Yaw -= xoffset * sensitivity;


		UpdateCameraVectors();
	}
	void Camera::UpdateCameraVectors() 
	{
		if (Pitch > glm::radians(45.0f))
			Pitch = glm::radians(45.0f);
		if (Pitch < glm::radians(-45.0f))
			Pitch = glm::radians(-45.0f);
		//计算出摄像机拍摄方向的欧拉角
		CameraZ.x = sin(Yaw) * cos(Pitch);
		CameraZ.y = sin(Pitch);
		CameraZ.z = cos(Yaw) * cos(Pitch);
		//取反得到此时摄像机的Z轴向量
		CameraZ = -CameraZ;
		Right = normalize(cross(WorldUp, CameraZ));
		Up = normalize(cross(CameraZ, Right));
	}

	void Camera::UpdateCameraPos() {
		Positon -= CameraZ * speedZ * 0.1f;
		Positon += Right * speedR * 0.1f;
	}
//}