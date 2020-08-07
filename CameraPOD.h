#pragma once


enum class CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

namespace globals
{
	// settings for a 'flight' view camera system
	float const YAW{ -90.0f };
	float const PITCH{ 0.0f };
	float const SPEED{ 2.5f };
	float const SENSITIVITY{ 0.1f };
	float const ZOOM{ 45.0f };
}