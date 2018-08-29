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
#include "primitives/bounding-box.h"
Primitive raytracer::primitives::mesh_obj(const std::string& path)
{
	Primitive mesh = optimize_mesh(read_mesh(path));
	return mesh;

//	Primitive mesh = make_union(read_mesh(path));
	//Primitive x=primitives::bounding_box_accelerator(mesh);

	
	//return x;
	//return mesh;
}
//Box make_box_left(Primitive p) {
//	
//	auto box = p->bounding_box();
//	auto x = box.x();
//	auto y = box.y();
//	auto z = box.z();
//
//	auto z1 = interval<double>(z.lower, z.center());
//
//	auto box_left = Box(x, y, z1);
//
//	return box_left;
//}
//
//Box make_box_right(Primitive p) {
//	auto box = p->bounding_box();
//	auto x = box.x();
//	auto y = box.y();
//	auto z = box.z();
//
//	auto z1 = interval<double>(z.center(), z.upper);
//
//	auto box_right = Box(x, y, z1);
//
//	
//
//	return box_right;
//}
bool sort_vector(std::shared_ptr<Hit> hit1, std::shared_ptr<Hit> hit2) {
	return hit1->t < hit2->t;
}
namespace
{
	class meshOptimize :public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:

		meshOptimize(std::vector<Primitive>& v, int n) : vector(v), n(n), box(Box::empty())
		{
			
					fixSneller(v);
			
		}


		vector<shared_ptr<Hit>> find_all_hits(const Ray& ray) const override {
			std::vector<std::shared_ptr<Hit>> hits;
			if (box.is_hit_by(ray)) {
				if (n == 1) {
					for (auto p : vector) {
						Hit hit;
						if (p->find_first_positive_hit(ray, &hit)) {
							hits.push_back(make_shared<Hit>(hit));
						}
					}
				}
				for (auto hit : left_primitive->find_all_hits(ray))
				{
					hits.push_back(hit);
				}
				for (auto hit : right_primitive->find_all_hits(ray))
				{
					hits.push_back(hit);
				}
			}


			std::sort(hits.begin(), hits.end(), sort_vector);


			return hits;
		}
		Box bounding_box() const override
		{
			return box;
		}


	protected:
		
		void fixSneller(vector<Primitive> v) {

			if (v.size() == 0) {
				
				n = 1;
				return;
			}


			if (n == 0) {
				return;
			}

			Box uiterste = Box::empty();
			for (auto primitive : v) {
				uiterste = primitive->bounding_box().merge(uiterste);
			}
			auto x = uiterste.x();
			auto y = uiterste.y();
			auto z = uiterste.z();
			double xMin = x.lower;
			double xCenter = x.center();
			double xMax = x.upper;
			double yMin = y.lower;
			double yCenter = y.center();
			double yMax = y.upper;
			double zMin = z.lower;
			double zCenter = z.center();
			double zMax = z.upper;
			
			std::vector<Primitive> boxkelinks;
			std::vector<Primitive> boxkerechts;
			Box links = Box::empty();
			Box rechts = Box::empty();
			if (xMax - xMin >= yMax - yMin && xMax - xMin >= zMax - zMin) {
				links = Box(interval(xMin, xCenter), y, z);
				rechts = Box(interval(xCenter, xMax), y, z);
				for (auto p : v) {
					if (p->bounding_box().x().lower >= xMin && p->bounding_box().x().upper <= xCenter) {
						boxkelinks.push_back(p);
					}
					
					else {
						boxkerechts.push_back(p);
					}



				}
			}
			else if (yMax - yMin >= zMax - zMin) {
				links = Box(x, interval(yMin, yCenter), z);
				rechts = Box(x, interval(yCenter, yMax), z);
				for (auto p : v) {
					if (p->bounding_box().y().lower >= yMin && p->bounding_box().y().upper <= yCenter) {
						boxkelinks.push_back(p);
					}
					
					else {
						boxkerechts.push_back(p);
					}



				}
			}
			else {
				links = Box(x, y, interval(zMin, zCenter));
				rechts = Box(x, y, interval(zCenter, zMax));
				for (auto p : v) {
					if (p->bounding_box().z().lower >= zMin && p->bounding_box().z().upper <= zCenter) {
						boxkelinks.push_back(p);
					}
					
					else {
						boxkerechts.push_back(p);
					}



				}

			}

			box = uiterste;
			left_primitive = Primitive(make_shared<meshOptimize>(boxkelinks, n - 1));
			right_primitive = Primitive(make_shared<meshOptimize>(boxkerechts, n - 1));
		}

	private:
		//1e keer alle triangles opslaan voor hits te vinden, in constructor altijd de kleinere lijst meegeven
		vector<Primitive> vector;
		int n;
		Box box;
		Primitive left_primitive;
		Primitive right_primitive;
		//auto z1 = interval<double>(z.lower, z.center());
		//auto z2 = interval<double>(z.center(), z.upper);





	};
};
Primitive raytracer::primitives::optimize_mesh(vector<Primitive>& triangles)
{
	return Primitive(make_shared<meshOptimize>(triangles, 30));
}
//
//
//
//
//			for (auto &i : v) {
//				//als de triangle zijn middelpunt in de linkse box zit, deze in de lijst van de linkse objecten steken steken
//				if (box_left.contains(i->bounding_box().center())) {
//					boxkelinks.push_back(i);
//				}
//				else {
//					boxkerechts.push_back(i);
//				}
//			}
//			auto boxkelinks_box = make_union(boxkelinks);
//			auto boxkelinks_primitive = primitives::bounding_box_accelerator(boxkelinks_box);
//
//			auto boxkerechts_box = make_union(boxkerechts);
//			auto boxkerechts_primitive = primitives::bounding_box_accelerator(boxkerechts_box);
//
//			//loop
//			/*if (box_left.contains(t)) {
//				boxkelinks.push_back(t);
//
//			}
//			else {
//				boxkerechts.push_back(t);
//			}*/
//			//end_loop
//
//
//			//	for(triangles in lijst<triangles>){
//			//		if(box_left.contains(
//			//
//			//
//			//if(bounding_box_accelerator(triangles).find_all_hits==NULL){
//
//		//	}
//
//		}
//	}
//}