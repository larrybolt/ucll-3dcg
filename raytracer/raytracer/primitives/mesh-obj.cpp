#include "primitives/mesh-obj.h"
#include <fstream>
#include <sstream>
#include "logging.h"
#include "easylogging++.h"
#include "primitives/triangle-primitive.h"
#include "primitives/union-primitive.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;
using namespace std;

std::vector<std::shared_ptr<Hit>> raytracer::primitives::ObjMesh::find_all_hits(const math::Ray & ray) const
{
	LOG(INFO) << "find_all_hits";
	// Instantiate empty list of hits
	std::vector<std::shared_ptr<Hit>> hits;

	// Iterate over every triangle in the mesh
	for (const Primitive triangle : m_triangles)
	{
		// Initialize a hit object
		Hit hit;

		// If there's been a hit with the triangle
		if (triangle->find_first_positive_hit(ray, &hit))
		{
			// Add the first positive hit to our list of hits
			hits.push_back(std::make_shared<Hit>(hit));
		}
	}
	std::sort(hits.begin(), hits.end(), [](std::shared_ptr<Hit> a, std::shared_ptr<Hit> b) -> bool {
		return a->t < b->t;
	});
	LOG(INFO) << "found all mesh hits";
	return hits;
}

math::Box raytracer::primitives::ObjMesh::bounding_box() const
{
	// If there are no triangles (e.g when the mesh file wasn't found), return a box with 0 volume
	if (m_triangles.size() == 0) return math::Box(math::Interval<double>(0, 0), math::Interval<double>(0, 0), math::Interval<double>(0, 0));

	// Create bounding box for first triangle in triangles list
	math::Box bb = m_triangles.at(0)->bounding_box();

	// Iterate over every triangle in the mesh
	for (int i = 1; i < m_triangles.size(); i++)
	{
		// Merge the bounding box with the new triangle's bounding box
		bb = bb.merge(m_triangles.at(i)->bounding_box());
	}
	return bb;
}

std::vector<Primitive> raytracer::primitives::ObjMesh::read_mesh(const std::string& path) const
{
	LOG(INFO) << "Reading mesh";

	std::vector<Primitive> triangles;

	std::ifstream obj(path);

	// Check if file exists
	if (!obj.is_open())
	{
		// File does not exitst
		LOG(INFO) << "Could not open file at location " << path;
		return triangles;
	}

	// Initialize list of vertices
	std::vector<Point3D> vertices;

	std::string line;

	// Read the .obj file
	while (std::getline(obj, line))
	{
		std::istringstream iss(line);
		std::string method;

		// Extract the type of data from the line
		iss >> method;

		// Checks if the data on the line represents a vertex
		if (method == "v")
		{
			double x, y, z;

			// Extract the x, y and z coordinates from the line
			iss >> x >> y >> z;

			LOG(INFO) << "New vertex (" << x << ", " << y << ", " << z << ")";

			// Create a Point3D from the coordinates
			Point3D p(x, y, z);

			// Add the point to the list of vertices
			vertices.push_back(p);
		}

		// Checks if the data on the line represents a set of triangles
		else if (method == "f")
		{
			int a, b, c;
			char s;

			// Read the set of triangles from the polygon line with the index of the vertices seperated by a '/'
			while ((iss >> a >> s >> b >> s >> c) && s == '/')
			{
				LOG(INFO) << "New triangle (v" << a << ", v" << b << ", v" << c << ")";

				// Create a triangle from the corresponding vertices (index -1 because they start at 1) and add it to the polygon list
				triangles.push_back(triangle(vertices[a - 1], vertices[b - 1], vertices[b - 1]));
			}
		}
	}
	LOG(INFO) << "Finished reading mesh, " << triangles.size() << " triangles found";

	// Return the list of triangles
	return triangles;
}

std::shared_ptr<raytracer::primitives::ObjMesh> raytracer::primitives::obj_mesh(std::string path)
{
	return std::make_shared<raytracer::primitives::ObjMesh>(path);
}

Primitive raytracer::primitives::mesh(std::string path)
{
	return make_union(obj_mesh(path)->m_triangles);
}
