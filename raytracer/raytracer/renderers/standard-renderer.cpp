#include "renderers/standard-renderer.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::renderers;


namespace
{
    class StandardRenderer : public raytracer::renderers::_private_::RendererImplementation
    {
    public:
        StandardRenderer(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler)
            : RendererImplementation(horizontal_size, vertical_size, sampler, ray_tracer, scheduler)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const override
        {
            TIMED_FUNC(timer);

            // Create a [0,1] x [0,1] window.
            Rectangle2D window(Point2D(0, 1), Vector2D(1, 0), Vector2D(0, -1));

            // Divide this window in small rectangles (which represent pixels)
            Rasterizer window_rasterizer(window, m_horizontal_size, m_vertical_size);

            // Create a bitmap of the same size
            auto result = std::make_shared<Bitmap>(m_horizontal_size, m_vertical_size);
            Bitmap& bitmap = *result;

            // Repeat for each pixel
            for_each_pixel([&](Position2D pixel_coordinates) {
                // Determine the color of the pixel
                Color c = render_pixel(window_rasterizer, pixel_coordinates, scene);

                // Assign color to bitmap
                bitmap[pixel_coordinates] = c;
            });

            return result;
        }

    private:
        /// <summary>
        /// Renders a single pixel.
        /// </summary>
        /// <param name="window_rasterizer">
        /// Rasterizer that splits the window into X by Y pixels.
        /// </param>
        /// <param name="position">
        /// Pixel coordinates.
        /// </param>
        /// <param name="scene">
        /// Scene.
        /// </param>
        /// <returns>
        /// Color of the pixel.
        /// <returns>
        Color render_pixel(const math::Rasterizer& window_rasterizer, const Position2D& position, const Scene& scene) const
        {
            // Find which part of the [0, 1] x [0, 1] corresponds to the pixel at the given position
            math::Rectangle2D pixel_rectangle = window_rasterizer[position];

            // Initialize color to black
            imaging::Color c = imaging::colors::black();

            // Count number of samples taken
            int sample_count = 0;

            // Let sampler determine how many samples we take in pixel_rectangle
            auto samples = m_sampler->sample(pixel_rectangle);

            m_sampler->sample(pixel_rectangle, [this, &c, &sample_count, &scene](const Point2D& sample_position) {
                scene.camera->enumerate_rays(sample_position, [this, &c, &sample_count, &scene](const Ray& ray) {
                    c += m_ray_tracer->trace(scene, ray).color;
                    ++sample_count;
                });
            });

            return c / sample_count;
        }

        unsigned m_thread_count;
    };
}

Renderer raytracer::renderers::standard(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler)
{
    return Renderer(std::make_shared<StandardRenderer>(horizontal_size, vertical_size, sampler, ray_tracer, scheduler));
}
