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

			// Initialize list of vertices, that define a polygon
			std::vector<Point3D> polygon;

			// Add the found vertices a to the list with polygon vertices, b and c are irrelevant for our reader
			while ((iss >> a >> s >> b >> s >> c) && s == '/')
			{
				// Vertices in .obj files start at one, so -1 to find the right vertex from our own list
				Point3D v(vertices[a - 1]);
				polygon.push_back(v);
			}

			// Check how many vertices are in the polygon
			int count = polygon.size();
			LOG(INFO) << "New polygon with " << count << " vertices";

			// Divide the polygon into triangles, assuming they are counter-clockwise and only consists of 3 to 6 vertices
			if (count >= 3)
			{
				triangles.push_back(triangle(polygon[0], polygon[1], polygon[2]));
				LOG(INFO) << "New triangle";
			}
			if (count >= 4)
			{
				triangles.push_back(triangle(polygon[2], polygon[3], polygon[0]));
				LOG(INFO) << "New triangle";
			}
			if (count >= 5)
			{
				triangles.push_back(triangle(polygon[3], polygon[4], polygon[0]));
				LOG(INFO) << "New triangle";
			}
			if (count >= 6)
			{
				triangles.push_back(triangle(polygon[4], polygon[5], polygon[0]));
				LOG(INFO) << "New triangle";
			}
		}
	}

	LOG(INFO) << "Finished reading mesh, " << triangles.size() << " triangles found out of " << vertices.size() << " vertices";

	// Return the list of triangles
	return triangles;
}

Primitive raytracer::primitives::mesh_obj(const std::string& path)
{
	Primitive mesh = make_union(read_mesh(path));
	return mesh;
}