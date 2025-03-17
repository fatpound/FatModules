module;

export module FatPound.Util.Gfx.FullScreenQuad;

import std;

export namespace fatpound::util::gfx
{
    struct FullScreenQuad final
    {
        struct alignas(32) Vertex final
        {
            float x;
            float y;
            float z;

            float u;
            float v;
        };

        static auto GenerateVertices() -> ::std::vector<Vertex>
        {
            return ::std::vector<Vertex>
            {
                Vertex{ .x = -1.0F, .y =  1.0F,  .z = 0.5F,  .u = 0.0F,  .v = 0.0F },
                Vertex{ .x =  1.0F, .y =  1.0F,  .z = 0.5F,  .u = 1.0F,  .v = 0.0F },
                Vertex{ .x =  1.0F, .y = -1.0F,  .z = 0.5F,  .u = 1.0F,  .v = 1.0F },
                Vertex{ .x = -1.0F, .y =  1.0F,  .z = 0.5F,  .u = 0.0F,  .v = 0.0F },
                Vertex{ .x =  1.0F, .y = -1.0F,  .z = 0.5F,  .u = 1.0F,  .v = 1.0F },
                Vertex{ .x = -1.0F, .y = -1.0F,  .z = 0.5F,  .u = 0.0F,  .v = 1.0F }
            };
        }
    };
}

module : private;
