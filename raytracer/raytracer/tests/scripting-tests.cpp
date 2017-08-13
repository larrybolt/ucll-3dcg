#ifndef EXCLUDE_SCRIPTING
#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/scripting.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/approx.h"
#include "imaging/color.h"
#include "raytracers/scene.h"
#include <sstream>

using namespace raytracer::scripting;


//TEST_CASE("[Scripting] Creation of a vector", "[Scripting]")
//{
//    auto result = evaluate<math::Vector3D>("vec(1,2,3)");
//
//    REQUIRE(result == math::approx(math::Vector3D(1, 2, 3)));
//}
//
//TEST_CASE("[Scripting] Creation of a point", "[Scripting]")
//{
//    auto result = evaluate<math::Point3D>("pos(1,2,3)");
//
//    REQUIRE(result == math::approx(math::Point3D(1, 2, 3)));
//}
//
//TEST_CASE("[Scripting] Vector addition", "[Scripting]")
//{
//    auto result = evaluate<math::Vector3D>("vec(1,2,3) + vec(4,5,6)");
//
//    REQUIRE(result == math::approx(math::Vector3D(5, 7, 9)));
//}
//
//TEST_CASE("[Scripting] Vector + Point", "[Scripting]")
//{
//    auto result = evaluate<math::Point3D>("pos(1,2,3) + vec(4,5,6)");
//
//    REQUIRE(result == math::approx(math::Point3D(5, 7, 9)));
//}
//
//TEST_CASE("[Scripting] Point + Vector", "[Scripting]")
//{
//    auto result = evaluate<math::Point3D>("vec(1,2,3) + pos(4,5,6)");
//
//    REQUIRE(result == math::approx(math::Point3D(5, 7, 9)));
//}
//
//TEST_CASE("[Scripting] colors.black()", "[Scripting]")
//{
//    auto result = evaluate<imaging::Color>("Colors.black()");
//
//    REQUIRE(result == math::approx(imaging::colors::black()));
//}
//
//TEST_CASE("[Scripting] colors.white()", "[Scripting]")
//{
//    auto result = evaluate<imaging::Color>("Colors.white()");
//
//    REQUIRE(result == math::approx(imaging::colors::white()));
//}
//
//TEST_CASE("[Scripting] colors.red()", "[Scripting]")
//{
//    auto result = evaluate<imaging::Color>("Colors.red()");
//
//    REQUIRE(result == math::approx(imaging::colors::red()));
//}
//
//TEST_CASE("[Scripting] colors.blue() * 0.5", "[Scripting]")
//{
//    auto result = evaluate<imaging::Color>("Colors.blue() * 0.5");
//
//    REQUIRE(result == math::approx(imaging::colors::blue() * 0.5));
//}
//
//TEST_CASE("[Scripting] Creating perspective camera", "[Scripting]")
//{
//    auto result = evaluate<raytracer::Camera>(R"(
//        var camera = Cameras.perspective(pos(0,0,5), pos(0,0,0), vec(0,1,0), 1, 1)
//        camera
//    )");
//
//    REQUIRE(!!result);
//}
//
//TEST_CASE("[Scripting] Creating perspective camera using argument map", "[Scripting]")
//{
//    auto result = evaluate<raytracer::Camera>(R"(
//        Cameras.perspective(["eye": pos(0,0,5), "look_at": pos(0,0,0), "up": vec(0,1,0), "distance": 1, "aspect_ratio": 1])
//    )");
//
//    REQUIRE(!!result);
//}



TEST_CASE("[Scripting] Pipeline creation", "[Scripting]")
{
    evaluate<void>(R"(
        var camera     = Cameras.perspective(pos(0,0,5), pos(0,0,0), vec(0,1,0), 1, 1)
        var material   = Materials.uniform( Colors.white() * 0.2,
                                            Colors.white() * 0.8,
                                            Colors.white(),
                                            20,
                                            0.2,
                                            0,
                                            0 )
        var root       = decorate( material, sphere() )
        var lights     = [ Lights.omnidirectional(pos(0,5,0), Colors.white()) ]
        var scene      = create_scene(camera, root, lights )
        var ray_tracer = Raytracers.binary()
        var renderer   = Renderers.standard(50, 50, Samplers.single(), ray_tracer)
        pipeline(scene, [ Pipeline.renderer(renderer)
                        , Pipeline.null_bitmap_consumer() ])
    )");
}


//TEST_CASE("[Scripting] Pipeline creation test", "[Scripting]")
//{
//    evaluate<void>(R"(
//
//        var ray_tracer = Raytracers.binary()
//        var renderer   = Renderers.standard(50, 50, Samplers.single(), ray_tracer)
//
//        def scene_at(now) {
//            var camera     = Cameras.perspective(pos(0,0,5), pos(0,0,0), vec(0,1,0), 1, 1)
//            var material   = Materials.uniform( Colors.white() * 0.2,
//                                                Colors.white() * 0.8,
//                                                Colors.white(),
//                                                20,
//                                                0.2,
//                                                0,
//                                                0 )
//            var root       = decorate( material, sphere() )
//            var lights     = [ Lights.omnidirectional(pos(0,5,0), Colors.white()) ]
//
//            create_scene(camera, root, lights)
//        }
//
//        pipeline(scene_animation(scene_at, seconds(1)), [ Pipeline.animation(1), Pipeline.renderer(renderer), Pipeline.null_bitmap_consumer() ])
//    )");
//}

//
//TEST_CASE("[Scripting] Animation pipeline", "[Scripting]")
//{
//    evaluate<void>(R"(
//        def scene_at(now) {
//            var animation   = Animations.circular( pos(0, 0, 5),
//                                                   pos(0, 0, 0),
//                                                   vec(0, 1, 0),
//                                                   interval( degrees(0), degrees(360) ),
//                                                   seconds(1) )
//
//            var camera     = Cameras.perspective(pos(0,0,5), pos(0,0,0), vec(0,1,0), 1, 1)
//            var material   = Materials.uniform( Colors.white() * 0.2,
//                                                Colors.white() * 0.8,
//                                                Colors.white(),
//                                                20,
//                                                0.2,
//                                                0,
//                                                0 )
//            var root       = decorate( material, translate( animation[now] - pos(0,0,0), sphere() ) )
//            var lights     = [ Lights.omnidirectional(pos(0,5,0), Colors.white()) ]
//
//            create_scene(camera, root, lights)
//        }
//
//        var raytracer   = Raytracers.v6()
//        var renderer    = Renderers.standard(50, 50, Samplers.multijittered(2), raytracer)
//
//        var anim = scene_animation(scene_at, seconds(1))
//
//        pipeline( anim,
//                  [ Pipeline.animation(1),
//                    Pipeline.renderer(renderer),
//                    Pipeline.null_bitmap_consumer() ] )
//    )");
//}

TEST_CASE("[Scripting] Animation pipeline", "[Scripting]")
{
    evaluate<void>(R"(
        def scene_at(now)
        {
            var camera = Cameras.perspective(["eye":pos(0, 0, 5),
                "look_at" : pos(0, 0, 0),
                "up" : vec(0, 1, 0),
                "distance" : 1,
                "aspect_ratio" : 1])

                var white = Materials.uniform(["ambient":Colors.white() * 0.1,
                    "diffuse" : Colors.white() * 0.8,
                    "specular" : Colors.white(),
                    "specular_exponent" : 20,
                    "reflectivity" : 0,
                    "transparency" : 0,
                    "refractive_index" : 0])

                var animation = Animations.circular(pos(0, 0, 2.5),
                    pos(0, 0, 0),
                    vec(0, 1, 0),
                    interval(degrees(0), degrees(360)),
                    seconds(1))

                var root = decorate(white, translate(animation[now] - pos(0, 0, 0), sphere()))
                var lights = [Lights.omnidirectional(pos(0, 5, 5), Colors.white())]

                return create_scene(camera, root, lights)
        }

        var anim = scene_animation(scene_at, seconds(1))

        var raytracer = Raytracers.v6()

        var renderer = Renderers.split_depth(["width":500,
            "height" : 500,
            "sampler" : Samplers.single(),
            "ray_tracer" : raytracer,
            "split_thickness" : 0.1,
            "split_depth" : 5.0])
    )");
}

#endif
#endif
