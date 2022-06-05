#pragma once

#include "cgp/cgp.hpp"


void create_car(cgp::hierarchy_mesh_drawable& hierarchy, float car_scale);

//engine parameters
const float r_R = 0.253f; //crankshaft to rod ratio
const float alpha = cgp::Pi / 2; //piston angle
const float fw_w = 2.4f; //flywheel to wheel ratio
const float th = 0.023f; //rotation of engine in car
//car parameters
const float R_wheel = 2.474f; //wheel radius
//lights parameters
const cgp::vec3 light1_position = { 12.835f + 2.0f, 4.485f, -0.773f };
const cgp::vec3 light2_position = { 12.835f + 2.0f, -4.485f, -0.773f };
const cgp::vec3 light3_position = { -14.072f - 2.0f, 4.227f, 0.619f };
const cgp::vec3 light4_position = { -14.072f - 2.0f, -4.227f, 0.619f };
