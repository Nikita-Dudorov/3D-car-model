#pragma once


#include "cgp/cgp.hpp"
#include "multiple_lights.hpp" 
#include "car.hpp"

// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_transparent = false;
	bool left_right = false;
	float R = 20;
	float h = 0;
	float speed = 0.5;
	float x = 0;
	float y = 0; 
	float z = 0;
};

struct scene_structure {

	cgp::mesh_drawable global_frame;          // The standard global frame
	//cgp::scene_environment_basic_camera_spherical_coords environment; // Standard environment controler
	scene_environment_with_multiple_lights environment;
	//light_shape_drawable light_drawable;

	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	gui_parameters gui;                        // Standard GUI element storage

	// Timer used for the animation
	cgp::timer_basic timer;
	bool complete_movement = false;
	float dt=0;
	float timer_move_car = 0;

	cgp::hierarchy_mesh_drawable mobile; //for car
	const float car_scale = 0.1f;
	cgp::vec3 trajectory; //car trajectory
	cgp::vec3 velocity; //car velocity

	cgp::mesh_drawable road;
	cgp::mesh_drawable grass;
	cgp::mesh_drawable lamp;
	const float L = 60*car_scale;
	const float H = -5.755f*car_scale;

	cgp::skybox_drawable skybox;


	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
	void display_car(float t); // display car

};





