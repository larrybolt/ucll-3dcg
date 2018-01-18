#include "primitives/mesh-obj-reader.h"
#include "primitives/triangle-primitive.h"
#include "primitives/union-primitive.h"
#include <fstream>
#include <sstream>
#include "logging.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace std;
using namespace math;

std::vector<Primitive> read_mesh(const std::string& path)
{
	LOG(INFO) << "Reading mesh";

	LOG(INFO) << "Attempting to open file at " << path;

	std::ifstream obj;

	// Open the file from the given path
	obj.open(path, ios::in);

	if (!obj.is_open())
	{
		LOG(INFO) << "Could not open file";
		return std::vector<Primitive>();
	}

	LOG(INFO) << "File opened";

	// Initialize list of vertices
	std::vector<Point3D> vertices;

	// Initialize list of triangles
	std::vector<Primitive> triangles;

	std::string line;

	// Read each line of the .obj file
	while (std::getline(obj, line))
	{
		LOG(INFO) << "New line";

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

				// Create a triangle from the corresponding vertices (index -1 because they start at 1 in .obj files) and add it to the triangles list
				triangles.push_back(triangle(vertices[a - 1], vertices[b - 1], vertices[b - 1]));
			}
		}
		else
		{
			LOG(INFO) << "Ignored this line";
		}
	}

	LOG(INFO) << "Finished reading mesh, " << triangles.size() << " triangles found";

	// Return the list of triangles
	return triangles;
}

Primitive raytracer::primitives::mesh_obj(const std::string& path)
{
	Primitive mesh = make_union(read_mesh(path));
	return mesh;
}