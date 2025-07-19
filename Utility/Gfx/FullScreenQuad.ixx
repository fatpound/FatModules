module;

export module FatPound.Utility.Gfx.FullScreenQuad;

import std;

export namespace fatpound::utility::gfx
{
    struct FullScreenQuad final
    {
        struct alignas(32) Vertex
        {
            float x;
            float y;
            float z;

            float u;
            float v;
        };

        static constexpr auto S_GenerateVertices() -> std::vector<Vertex>
        {
            return
            {
                Vertex{ .x = -1.0F, .y =  1.0F, .z = 0.5F, .u = 0.0F, .v = 0.0F },
                Vertex{ .x =  1.0F, .y =  1.0F, .z = 0.5F, .u = 1.0F, .v = 0.0F },
                Vertex{ .x =  1.0F, .y = -1.0F, .z = 0.5F, .u = 1.0F, .v = 1.0F },
                Vertex{ .x = -1.0F, .y =  1.0F, .z = 0.5F, .u = 0.0F, .v = 0.0F },
                Vertex{ .x =  1.0F, .y = -1.0F, .z = 0.5F, .u = 1.0F, .v = 1.0F },
                Vertex{ .x = -1.0F, .y = -1.0F, .z = 0.5F, .u = 0.0F, .v = 1.0F }
            };
        }
    };
}

// module : private;
