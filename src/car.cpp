#include "car.hpp"

using namespace cgp;

void create_car(hierarchy_mesh_drawable& hierarchy, float car_scale)
{
	//the car will be assembled in this hierarchy

	//all meshes mading up the car
	mesh_drawable car;
	mesh_drawable wheel1;
	mesh_drawable wheel2;
	mesh_drawable wheel3;
	mesh_drawable wheel4;
	mesh_drawable engine;
	mesh_drawable crankshaft;
	mesh_drawable rod1;
	mesh_drawable rod2;
	mesh_drawable rod3;
	mesh_drawable rod4;
	mesh_drawable piston1;
	mesh_drawable piston2;
	mesh_drawable piston3;
	mesh_drawable piston4;
	mesh_drawable flywheel;
	mesh_drawable fw_gear;
	mesh_drawable main_shaft1;
	mesh_drawable main_shaft2;
	mesh_drawable main_shaft3;
	mesh_drawable main_shaft4;
	mesh_drawable main_shaft5;
	mesh_drawable main_shaft6;
	mesh_drawable main_shaft7;
	mesh_drawable main_shaft8;
	mesh_drawable wheel_shaft1;
	mesh_drawable wheel_shaft2;
	mesh_drawable wheel_shaft3;
	mesh_drawable wheel_shaft4;
	mesh_drawable wheel_shaft5;
	mesh_drawable wheel_shaft6;
	mesh_drawable wheel_shaft7;
	mesh_drawable wheel_shaft8;
	mesh_drawable bevel_gear1;
	mesh_drawable bevel_gear2;

	//color for car details
	vec3 car_color = { 1.0f, 1.0f, 1.0f };
	vec3 metal_color = { 0.8f, 0.8f, 0.8f };
	vec3 tire_color = { 0.5f, 0.5f, 0.5f };
	shading_parameters_phong::phong_parameters car_shading = { 0.35f,0.35f,0.35f,0.3f };
	shading_parameters_phong::phong_parameters metal_shading = { 0.3f,0.3f,0.3f,0.1f };
	float alpha_transparency = 0.25f;

	//textures of car
	GLuint const car_texture = opengl_load_texture_image("assets/car/car_tex.jpg",
		GL_CLAMP_TO_BORDER,
		GL_CLAMP_TO_BORDER);
	GLuint const tire_texture1 = opengl_load_texture_image("assets/wheel/tire_tread1.jpg",
		GL_REPEAT,
		GL_CLAMP_TO_BORDER);
	GLuint const tire_texture2 = opengl_load_texture_image("assets/wheel/tire_tread2.jpg",
		GL_REPEAT,
		GL_CLAMP_TO_BORDER);

	//mesh initialising
	mesh car_mesh = mesh_load_file_obj("assets/car/car.obj");
	car.initialize(car_mesh, "car");
	car.transform.scaling = 13.0f;
	car.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, -Pi / 2) *
		rotation_transform::from_axis_angle({ 1,0,0 }, Pi / 2);
	car.shading.color = car_color;
	car.shading.phong = car_shading;
	car.shading.alpha = alpha_transparency;
	car.texture = car_texture;

	mesh wheel_mesh = mesh_load_file_obj("assets/wheel/wheel.obj");
	wheel1.initialize(wheel_mesh, "wheel1");
	wheel1.transform.scaling = 5.0f;
	wheel1.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi / 2);
	wheel2.initialize(wheel_mesh, "wheel2");
	wheel2.transform.scaling = 5.0f;
	wheel2.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi) *
		rotation_transform::from_axis_angle({ 1,0,0 }, -Pi / 2);
	wheel3.initialize(wheel_mesh, "wheel3");
	wheel3.transform.scaling = 5.0f;
	wheel3.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -Pi / 2);
	wheel4.initialize(wheel_mesh, "wheel4");
	wheel4.transform.scaling = 5.0f;
	wheel4.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi) *
		rotation_transform::from_axis_angle({ 1,0,0 }, -Pi / 2);
	wheel1.shading.color = tire_color;
	wheel2.shading.color = tire_color;
	wheel3.shading.color = tire_color;
	wheel4.shading.color = tire_color;
	wheel1.texture = tire_texture1;
	wheel2.texture = tire_texture2;
	wheel3.texture = tire_texture1;
	wheel4.texture = tire_texture2;

	mesh engine_mesh = mesh_load_file_obj("assets/engine/v4_engine_vert.obj");
	engine.initialize(engine_mesh, "engine");
	engine.transform.scaling = 0.135f;
	engine.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2) *
		rotation_transform::from_axis_angle({ 1,0,0 }, Pi / 2);
	engine.transform.translation = { -1.856f, -1.856f, -0.722f };
	engine.shading.color = metal_color;
	engine.shading.phong = metal_shading;
	engine.shading.alpha = alpha_transparency;

	mesh crankshaft_mesh = mesh_load_file_obj("assets/engine/v4_crankshaft.obj");
	crankshaft.initialize(crankshaft_mesh, "crankshaft");
	crankshaft.transform.scaling = 0.01f;
	crankshaft.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, Pi / 2);
	crankshaft.transform.translation = { 0, -0.7f, 0.8f };
	crankshaft.shading.color = metal_color;
	crankshaft.shading.phong = metal_shading;

	mesh rod_mesh = mesh_load_file_obj("assets/engine/rod.obj");
	rod1.initialize(rod_mesh, "rod1");
	rod1.transform.scaling = 0.015f;
	rod1.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, -Pi / 2);
	rod1.transform.translation = { 0.124f, -0.124f, 1.814f };
	rod2.initialize(rod_mesh, "rod2");
	rod2.transform.scaling = 0.015f;
	rod2.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, -Pi / 2);
	rod2.transform.translation = { 0.124f, -0.124f, 1.814f };
	rod3.initialize(rod_mesh, "rod3");
	rod3.transform.scaling = 0.015f;
	rod3.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, -Pi / 2);
	rod3.transform.translation = { 0.124f, -0.124f, 1.814f };
	rod4.initialize(rod_mesh, "rod4");
	rod4.transform.scaling = 0.015f;
	rod4.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, -Pi / 2);
	rod4.transform.translation = { 0.124f, -0.124f, 1.814f };
	rod1.shading.color = metal_color;
	rod1.shading.phong = metal_shading;
	rod2.shading.color = metal_color;
	rod2.shading.phong = metal_shading;
	rod3.shading.color = metal_color;
	rod3.shading.phong = metal_shading;
	rod4.shading.color = metal_color;
	rod4.shading.phong = metal_shading;


	mesh piston_mesh = mesh_load_file_obj("assets/engine/piston.obj");
	piston1.initialize(piston_mesh, "piston1");
	piston1.transform.scaling = 0.012f;
	piston2.initialize(piston_mesh, "piston2");
	piston2.transform.scaling = 0.012f;
	piston3.initialize(piston_mesh, "piston3");
	piston3.transform.scaling = 0.012f;
	piston4.initialize(piston_mesh, "piston4");
	piston4.transform.scaling = 0.012f;
	piston1.shading.color = metal_color;
	piston1.shading.phong = metal_shading;
	piston2.shading.color = metal_color;
	piston2.shading.phong = metal_shading;
	piston3.shading.color = metal_color;
	piston3.shading.phong = metal_shading;
	piston4.shading.color = metal_color;
	piston4.shading.phong = metal_shading;

	mesh flywheel_mesh = mesh_load_file_obj("assets/engine/flywheel.obj");
	flywheel.initialize(flywheel_mesh, "flywheel");
	flywheel.transform.scaling = 0.22f;
	flywheel.shading.color = metal_color;
	flywheel.shading.phong = metal_shading;

	mesh fw_gear_mesh = mesh_load_file_obj("assets/engine/fw_gear.obj");
	fw_gear.initialize(fw_gear_mesh, "fw_gear");
	fw_gear.transform.scaling = 0.3f;
	fw_gear.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, -Pi / 2);
	fw_gear.shading.color = metal_color;
	fw_gear.shading.phong = metal_shading;

	mesh shaft_mesh = mesh_load_file_obj("assets/engine/shaft.obj");
	main_shaft1.initialize(shaft_mesh, "main_shaft1");
	main_shaft1.transform.scaling = 0.3f;
	main_shaft2.initialize(shaft_mesh, "main_shaft2");
	main_shaft2.transform.scaling = 0.3f;
	main_shaft3.initialize(shaft_mesh, "main_shaft3");
	main_shaft3.transform.scaling = 0.3f;
	main_shaft4.initialize(shaft_mesh, "main_shaft4");
	main_shaft4.transform.scaling = 0.3f;
	main_shaft5.initialize(shaft_mesh, "main_shaft5");
	main_shaft5.transform.scaling = 0.3f;
	main_shaft6.initialize(shaft_mesh, "main_shaft6");
	main_shaft6.transform.scaling = 0.3f;
	main_shaft7.initialize(shaft_mesh, "main_shaft7");
	main_shaft7.transform.scaling = 0.3f;
	main_shaft8.initialize(shaft_mesh, "main_shaft8");
	main_shaft8.transform.scaling = 0.3f;
	main_shaft1.shading.color = metal_color;
	main_shaft1.shading.phong = metal_shading;
	main_shaft2.shading.color = metal_color;
	main_shaft2.shading.phong = metal_shading;
	main_shaft3.shading.color = metal_color;
	main_shaft3.shading.phong = metal_shading;
	main_shaft4.shading.color = metal_color;
	main_shaft4.shading.phong = metal_shading;
	main_shaft5.shading.color = metal_color;
	main_shaft5.shading.phong = metal_shading;
	main_shaft6.shading.color = metal_color;
	main_shaft6.shading.phong = metal_shading;
	main_shaft7.shading.color = metal_color;
	main_shaft7.shading.phong = metal_shading;
	main_shaft8.shading.color = metal_color;
	main_shaft8.shading.phong = metal_shading;

	wheel_shaft1.initialize(shaft_mesh, "wheel_shaft1");
	wheel_shaft1.transform.scaling = 0.15f;
	wheel_shaft1.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);
	wheel_shaft2.initialize(shaft_mesh, "wheel_shaft2");
	wheel_shaft2.transform.scaling = 0.15f;
	wheel_shaft2.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);
	wheel_shaft3.initialize(shaft_mesh, "wheel_shaft3");
	wheel_shaft3.transform.scaling = 0.15f;
	wheel_shaft3.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);
	wheel_shaft4.initialize(shaft_mesh, "wheel_shaft4");
	wheel_shaft4.transform.scaling = 0.15f;
	wheel_shaft4.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);
	wheel_shaft5.initialize(shaft_mesh, "wheel_shaft5");
	wheel_shaft5.transform.scaling = 0.15f;
	wheel_shaft5.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);
	wheel_shaft6.initialize(shaft_mesh, "wheel_shaft6");
	wheel_shaft6.transform.scaling = 0.15f;
	wheel_shaft6.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);
	wheel_shaft7.initialize(shaft_mesh, "wheel_shaft7");
	wheel_shaft7.transform.scaling = 0.15f;
	wheel_shaft7.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);
	wheel_shaft8.initialize(shaft_mesh, "wheel_shaft8");
	wheel_shaft8.transform.scaling = 0.15f;
	wheel_shaft8.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);
	wheel_shaft1.shading.color = metal_color;
	wheel_shaft1.shading.phong = metal_shading;
	wheel_shaft2.shading.color = metal_color;
	wheel_shaft2.shading.phong = metal_shading;
	wheel_shaft3.shading.color = metal_color;
	wheel_shaft3.shading.phong = metal_shading;
	wheel_shaft4.shading.color = metal_color;
	wheel_shaft4.shading.phong = metal_shading;
	wheel_shaft5.shading.color = metal_color;
	wheel_shaft5.shading.phong = metal_shading;
	wheel_shaft6.shading.color = metal_color;
	wheel_shaft6.shading.phong = metal_shading;
	wheel_shaft7.shading.color = metal_color;
	wheel_shaft7.shading.phong = metal_shading;
	wheel_shaft8.shading.color = metal_color;
	wheel_shaft8.shading.phong = metal_shading;

	mesh bevel_gear_mesh = mesh_load_file_obj("assets/engine/bevel_gear.obj");
	bevel_gear1.initialize(bevel_gear_mesh, "bevel_gear1");
	bevel_gear1.transform.scaling = 0.02f;
	bevel_gear1.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, -Pi / 2);
	bevel_gear1.transform.translation = { 0.0f,-0.144f,-0.454f };
	bevel_gear1.shading.color = metal_color;
	bevel_gear1.shading.phong = metal_shading;

	bevel_gear2.initialize(bevel_gear_mesh, "bevel_gear2");
	bevel_gear2.transform.scaling = 0.02f;
	bevel_gear2.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, Pi / 2);
	bevel_gear2.transform.translation = { -0.454f,0.0f,-0.144f };
	bevel_gear2.shading.color = metal_color;
	bevel_gear2.shading.phong = metal_shading;

	//assembling all meshes in hierarchy to build the car
	hierarchy.add(car);
	hierarchy.add(engine, "car", { 9.619f,0.0f,-1.553f });
	hierarchy.add(crankshaft, "engine", { -2.965f,0.0f,-0.567f });
	hierarchy.add(rod1, "crankshaft", { 1.840f,0.0f,0.454f });
	hierarchy.add(rod2, "crankshaft", { 2.490f,0.0f,-0.464f });
	hierarchy.add(rod3, "crankshaft", { 3.460f,0.0f,-0.464f });
	hierarchy.add(rod4, "crankshaft", { 4.090f,0.0f,0.454f });
	hierarchy.add(piston1, "rod1", { 0.0f,0.0f,1.625f });
	hierarchy.add(piston2, "rod2", { 0.0f,0.0f,1.625f });
	hierarchy.add(piston3, "rod3", { 0.0f,0.0f,1.625f });
	hierarchy.add(piston4, "rod4", { 0.0f,0.0f,1.625f });
	hierarchy.add(flywheel, "crankshaft", { 4.765f,0.0f,0.0f });
	hierarchy.add(fw_gear, "engine", { 1.856f,0.0f,-2.165f });
	hierarchy.add(main_shaft1, "fw_gear", { -2.732f,0.0f,0.0f });
	hierarchy.add(main_shaft2, "main_shaft1", { -2.732f,0.0f,0.0f });
	hierarchy.add(main_shaft3, "main_shaft2", { -2.732f,0.0f,0.0f });
	hierarchy.add(main_shaft4, "main_shaft3", { -2.732f,0.0f,0.0f });
	hierarchy.add(main_shaft5, "main_shaft4", { -2.732f,0.0f,0.0f });
	hierarchy.add(main_shaft6, "main_shaft5", { -2.732f,0.0f,0.0f });
	hierarchy.add(main_shaft7, "main_shaft6", { -2.732f,0.0f,0.0f });
	hierarchy.add(main_shaft8, "main_shaft7", { -1.649f,0.0f,0.0f });
	hierarchy.add(bevel_gear1, "main_shaft8", { 0.144f,0.0f,0.0f });
	hierarchy.add(bevel_gear2, "engine", { -19.175f,0.550f,-2.165f });
	hierarchy.add(wheel_shaft1, "bevel_gear2", { 0.0f,-1.546f,0.0f });
	hierarchy.add(wheel_shaft2, "wheel_shaft1", { 0.0f,-1.450f,0.0f });
	hierarchy.add(wheel_shaft3, "wheel_shaft2", { 0.0f,-1.450f,0.0f });
	hierarchy.add(wheel_shaft4, "wheel_shaft3", { 0.0f,-1.450f,0.0f });
	hierarchy.add(wheel_shaft5, "wheel_shaft1", { 0.0f,1.450f,0.0f });
	hierarchy.add(wheel_shaft6, "wheel_shaft5", { 0.0f,1.450f,0.0f });
	hierarchy.add(wheel_shaft7, "wheel_shaft6", { 0.0f,1.450f,0.0f });
	hierarchy.add(wheel_shaft8, "wheel_shaft7", { 0.0f,1.450f / 2,0.0f });
	//hierarchy.add(wheel1, "car", {-9.591f,-5.361f,-3.299f});
	//hierarchy.add(wheel2, "car", { -9.591f,5.361f,-3.299f });
	hierarchy.add(wheel1, "wheel_shaft4", { 0.0f,0.0f,0.0f });
	hierarchy.add(wheel2, "wheel_shaft8", { 0.0f,1.290f,0.0f });
	hierarchy.add(wheel3, "car", { 10.091f,-5.361f,-3.299f });
	hierarchy.add(wheel4, "car", { 10.091f,5.361f,-3.299f });

	hierarchy["car"].transform.scaling = car_scale;
	return;
}