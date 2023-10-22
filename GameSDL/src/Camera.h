#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
class Camera
{
	public:
		Camera();
		~Camera();
		glm::mat4 getViewMatrix() { return view; };
		glm::vec3 getCameraPosition() { return camera_pos; };
		void updatePitchYaw(const float x_offset, const float y_offset);
		void updateCameraPosition(glm::vec2 dir);

	private:
		void calculateViewMatrx();
		void calculateCameraTarget();
		void calculateCameraDirection();
		void calculateRightVector();
		void calculateCameraUpVector();

		glm::vec3 camera_pos;
		glm::vec3 camera_target;
		glm::vec3 camera_direction;
		glm::vec3 camera_right;
		glm::vec3 camera_up;
		glm::mat4 view;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		float pitch = 0;
		float yaw = -90;
};

#endif // CAMERA_H
