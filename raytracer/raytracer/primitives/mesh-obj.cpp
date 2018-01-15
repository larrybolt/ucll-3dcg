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

namespace
{
	class MeshObj : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		MeshObj(const string& path)
			: m_path(path) {}

		bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
		{
			return create_mesh(m_path)->find_first_positive_hit(ray, hit);
		}
		
		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			return create_mesh(m_path)->find_all_hits(ray);
		}

		Box bounding_box() const override
		{
			return create_mesh(m_path)->bounding_box();
		}

	protected:

		// Creates a mesh primitive from a .obj file
		Primitive create_mesh(const string& path) const
		{
			// Initialize primitive
			Primitive mesh;

			ifstream obj(path);

			// Check if file exists
			if (!obj.is_open())
			{
				// File does not exitst
				LOG(INFO) << "Could not open file at location " << path;
				return mesh;
			}

			// Initialize list of vertices
			std::vector<Point3D> vertices;

			// Initialize list of polygons
			std::vector<Primitive> polygons;

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

					// Create a Point3D from the coordinates
					Point3D p(x, y, z);

					// Add the point to the list of vertices
					vertices.push_back(p);
				}

				// Checks if the data on the line represents a set of triangles
				else if (method == "f")
				{
					std::vector<Primitive> polygon;
					int a, b, c;
					char s;

					// Read the set of triangles from the polygon line with the index of the vertices seperated by a '/'
					while ((iss >> a >> s >> b >> s >> c) && s == '/')
					{
						// Create a triangle from the corresponding vertices (index -1 because they start at 1) and add it to the polygon list
						polygon.push_back(triangle(vertices[a-1], vertices[b-1], vertices[b-1]));
					}

					// Union all triangles into a polygon
					Primitive un = make_union(polygon);

					// Add the polygon to the list of polygons
					polygons.push_back(un);
				}
			}
			// return a union primitive of all polygons
			return make_union(polygons);
		}		

	private:
		string m_path;
	};
}

Primitive raytracer::primitives::objMesh(const std::string& path)
{
	return Primitive(std::make_shared<MeshObj>(path));
}
