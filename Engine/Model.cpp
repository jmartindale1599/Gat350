#include "Model.h"

#include "Math/Transform.h"

#include "Core/Logger.h"

#include "Core/File.h"

#include <sstream>

#include <iostream>

namespace neu {

	Model::Model(const std::string filename){

		Load(filename);
		
		m_radius = calcRadius();

	}

	bool Model::Create(std::string filename, ...){

		if (!Load(filename)) {

			LOG("Error could not read file %s", filename.c_str());

			return false;
		}

		return true;
	
	}

	void Model::Draw(Renderer& renderer, const Vector2& position, float angle, float scale) {

		//color.r = neu::random(256);

		//color.g = neu::random(256);

		//color.b = neu::random(256);

		//color.r = 255;

		//draw model

		for (int i = 0; i < m_points.size() - 1; i++) {

			neu::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;

			neu::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);

		}

	}

	void Model::Draw(Renderer& renderer, const Transform& transform){

		Matrix3x3 mx = transform.matrix;

		for (int i = 0; i < m_points.size() - 1; i++) {

			neu::Vector2 p1 = mx * m_points[i];

			neu::Vector2 p2 = mx * m_points[i + 1];

			renderer.DrawLine(p1, p2, m_color);

		}

	}

	bool Model::Load(const std::string& filename){

		std::string buffer;

		if (!neu::ReadFile(filename, buffer)) {

			LOG("Error could not read file %s", filename.c_str());

			return false;

		}

		//read color

		std::istringstream stream(buffer);

		stream >> m_color;

		//get points

		std::string line;

		std::getline(stream, line);

		size_t numPoints = std::stoi(line);

		//read points

		for (size_t i = 0; i < numPoints; i++) {

			Vector2 point;

			stream >> point;

			m_points.push_back(point);

		}

		return true;

	}

	float Model::calcRadius(){

		float radius = 0;

		//finds the largest length (radius)

		for (auto point : m_points) {

			if (point.Legnth() > radius) radius = point.Legnth();

		}

		return radius;
	
	}

}
