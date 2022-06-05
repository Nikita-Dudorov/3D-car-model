#include "scene.hpp"

using namespace cgp;

void scene_structure::initialize()
{
	GLuint const shader_lights = opengl_load_shader("shaders/mesh_lights/vert.glsl", "shaders/mesh_lights/frag.glsl");
	mesh_drawable::default_shader = shader_lights; // set this shader as the default one for all new shapes declared after this line

	skybox.initialize("assets/skybox/");

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.axis = camera_spherical_coordinates_axis::z;
	environment.camera.look_at({ 2.0f,-2.0f,1.0f }, { 0,0,0 });

	mesh road_mesh = mesh_primitive_quadrangle({ -30*L,L/2,H }, { -30*L,-L/2,H },
		{ 30*L,-L/2,H }, { 30*L,L/2,H }); // mesh of size 60L * L 
	road_mesh.uv = { {0,1*60}, {1*1,1*60}, {1*1,0}, {0,0} }; //1 * 40 * 1 textures per mesh
	road_mesh.connectivity = { {0,1,2}, {0,2,3} };
	GLuint const road_texture = opengl_load_texture_image("assets/road/road.jpg",
		GL_CLAMP_TO_BORDER,
		GL_REPEAT);
	road.initialize(road_mesh, "road");
	road.texture = road_texture;

	mesh grass_mesh = mesh_primitive_quadrangle({ -30*L,15*L,H }, { -30*L,-15*L,H },
		{30*L,-15*L,H }, { 30*L,15*L,H }); // mesh of size 60L * 30L 
	grass_mesh.uv = { {0,2*60}, {2*30,2*60}, {2*30,0}, {0,0} }; //2 * 60 * 30 textures per mesh
	grass_mesh.connectivity = { {0,1,2}, {0,2,3} };
	GLuint const grass_texture = opengl_load_texture_image("assets/road/grass.jpg",
		GL_REPEAT,
		GL_REPEAT);
	grass.initialize(grass_mesh, "grass");
	grass.texture = grass_texture;

	mesh lamp_mesh = mesh_load_file_obj("assets/road/lamp.obj");
	lamp.initialize(lamp_mesh, "lamp");
	lamp.transform.scaling = car_scale * 0.025f;
	lamp.texture = opengl_load_texture_image("assets/road/lamp_texture.jpg");

	//light_drawable.initialize(shader_lights);
	for (int k = 0; k < environment.spotlight_color.size(); ++k)
	{
		environment.spotlight_color[k] = {1.0f, 1.0f, 0.0f}; //yellow light
	}

	create_car(mobile, car_scale);
}


void scene_structure::display()
{
	draw(skybox, environment);

	velocity = { 150 * car_scale * gui.speed,0,0 };
	environment.light = environment.camera.position();

	float t_p = timer.t;
	while (t_p > (L/2)/norm(velocity)) //period L/2
		t_p -= (L/2)/norm(velocity);
	grass.transform.translation = { - norm(velocity) * t_p, 15*L + L/2, 0 };
	draw(grass, environment);
	grass.transform.translation = { -norm(velocity) * t_p, -15*L - L/2, 0 };
	draw(grass, environment);

	t_p = timer.t;
	while (t_p > L/norm(velocity))  //period L
		t_p -= L/norm(velocity);
	road.transform.translation = { -norm(velocity) * t_p, 0, 0 };
	draw(road, environment);

	int parity = 0;
	t_p = timer.t;
	while (t_p > (5*L)/norm(velocity)) // period 5L
	{
		t_p -= (5*L)/norm(velocity);
		parity += 1;
	}
	parity = (parity % 2 == 0) ? 1 : -1; //to change light positions
	for (int k = -6; k <= 6; ++k) // 6 + 1 + 6 lamps
	{
		lamp.transform.translation = { 5*k*L - norm(velocity) * t_p, 0.6*L, -H };
		lamp.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, -Pi / 2) *
			rotation_transform::from_axis_angle({ 1,0,0 }, Pi / 2);
		draw(lamp, environment);

		lamp.transform.translation = { 5*k*L - norm(velocity) * t_p, -0.6*L, -H };
		lamp.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2) *
			rotation_transform::from_axis_angle({ 1,0,0 }, Pi / 2);
		draw(lamp, environment);
	}
	for (int k = 0; k < environment.spotlight_position.size(); ++k) //light positions
	{
		int k_parity = (k % 2 == 0) ? 1 : -1;
		environment.spotlight_position[k] = {5 * (k - 2) * L - norm(velocity) * t_p, k_parity * parity * (0.4 * L), -H * 5.5};
	}

	//draw(light_drawable, environment);
	t_p = timer.t;
	timer.update();
	dt = timer.t - t_p;
	display_car(t_p);
	//draw(global_frame, environment);
}

void scene_structure::display_car(float t)
{
	if (gui.left_right == true && complete_movement == true)
		complete_movement = false;
	if(gui.left_right==true)
		timer_move_car += dt;
	trajectory = {0,-L/5 * std::cos(timer_move_car*(3.5*gui.speed)),0};
	if (std::abs(trajectory.y) > L/5*(1-0.001) &&
		std::sin(timer_move_car * (3.5 * gui.speed)) * trajectory.y > 0 &&
		gui.left_right == true) //wheather the movement if finished
	{
		//allignment of the car at the end of movement
		if (trajectory.y < 0)
		{
			timer_move_car = 0;
			trajectory = { 0,-L/5,0 };
		}
		else
		{
			timer_move_car = Pi/(3.5*gui.speed);
			trajectory = { 0,L/5,0 };
		}
		gui.left_right = false;
		complete_movement = true;
	}

	float wheel_angle = Pi / 9 * std::sin(timer_move_car*(3.5*gui.speed));
	float wheel_frequency = norm(velocity) * t / (R_wheel * car_scale);
	mobile["car"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, wheel_angle);
	mobile["car"].transform.translation = trajectory;

	mobile["engine"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, th);

	mobile["crankshaft"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		(Pi / 2 - alpha) + (wheel_frequency / fw_w));

	mobile["rod1"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		-(wheel_frequency / fw_w) + std::asin(std::sin(-(wheel_frequency / fw_w)) * r_R));
	mobile["rod4"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		-(wheel_frequency / fw_w) + std::asin(std::sin(-(wheel_frequency / fw_w)) * r_R));

	mobile["rod2"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		Pi + 2 * alpha - (wheel_frequency / fw_w) + std::asin(std::sin(2 * alpha - (wheel_frequency / fw_w)) * r_R));
	mobile["rod3"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		Pi + 2 * alpha - (wheel_frequency / fw_w) + std::asin(std::sin(2 * alpha - (wheel_frequency / fw_w)) * r_R));

	mobile["piston1"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		std::asin(std::sin((wheel_frequency / fw_w)) * r_R));
	mobile["piston4"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		std::asin(std::sin((wheel_frequency / fw_w)) * r_R));

	mobile["piston2"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		std::asin(std::sin(-2 * alpha + (wheel_frequency / fw_w)) * r_R));
	mobile["piston3"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		std::asin(std::sin(-2 * alpha + (wheel_frequency / fw_w)) * r_R));

	mobile["fw_gear"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 },
		-wheel_frequency);

	mobile["bevel_gear2"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 },
		wheel_frequency);

	mobile["wheel3"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, wheel_angle) *
		rotation_transform::from_axis_angle({ 0,1,0 }, wheel_frequency);
	mobile["wheel4"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, wheel_angle) *
		rotation_transform::from_axis_angle({ 0,1,0 }, wheel_frequency);

	mobile.update_local_to_global_coordinates();

	if (gui.display_transparent) //to display tranmission
	{
		for (int i = 2; i < mobile.elements.size(); ++i)
		{
			draw(mobile.elements[i], environment);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(false);

		draw(mobile.elements[1], environment);
		draw(mobile.elements[0], environment);

		glDepthMask(true);
		glDisable(GL_BLEND);
	}
	else
		draw(mobile, environment);
}

void scene_structure::display_gui()
{
	ImGui::Checkbox("Transmission", &gui.display_transparent);
	ImGui::Checkbox("left-right", &gui.left_right);
	ImGui::SliderFloat("speed", &gui.speed, 0.01f, 1);
}
