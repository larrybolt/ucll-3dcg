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

namespace raytracer
{
	class MeshObj : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:

		MeshObj(const std::string& path)
			: m_triangles(read_mesh(path))
		{}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			LOG(INFO) << "Find all hits";
			// Instantiate empty list of hits
			std::vector<std::shared_ptr<Hit>> hits;

			// Iterate over every triangle in the mesh
			for (auto triangle : m_triangles)
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

			LOG(INFO) << "Found all hits";
			return hits;
		}

		Box bounding_box() const override
		{
			// If there are no triangles (e.g when the mesh file wasn't found), return a box with 0 volume
			if (m_triangles.size() == 0) return math::Box(math::Interval<double>(0, 0), math::Interval<double>(0, 0), math::Interval<double>(0, 0));

			// Create bounding box for first triangle in triangles list
			math::Box bb = m_triangles.at(0)->bounding_box();

			// Iterate over every triangle in the mesh
			for (int i = 1; i < m_triangles.size(); i++)
			{
				// Merge the existing bounding box with the new triangle's bounding box
				bb = bb.merge(m_triangles.at(i)->bounding_box());
			}
			return bb;
		}

		std::vector<Primitive> read_mesh(const std::string& path) const
		{
			LOG(INFO) << "Reading mesh";

			LOG(INFO) << "Attempting to open file at " << path;

			std::ifstream obj;

			obj.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			// Open the file from the given path
			try {
				obj.open(path, ios::in);
			}
			catch (std::ifstream::failure::exception e) {
				LOG(INFO) << "Exception when opening file \n" << e.what();
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

			LOG(INFO) << "Reached end of file";

			obj.close();

			LOG(INFO) << "Finished reading mesh, " << triangles.size() << " triangles found";

			// Return the list of triangles
			return triangles;
		}

	private:
		std::vector<Primitive> m_triangles;
	};
}

Primitive raytracer::primitives::mesh(const std::string& path)
{
	return Primitive(std::make_shared<MeshObj>(path));
}