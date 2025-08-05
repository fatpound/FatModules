module;

export module FatPound.Win32.D3D11.FullScreenQuad;

import std;

export namespace fatpound::win32::d3d11
{
    struct FullScreenQuad
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
                Vertex{.x = -1.0F, .y =  1.0F, .z = 0.5F, .u = 0.0F, .v = 0.0F },
                Vertex{.x =  3.0F, .y =  1.0F, .z = 0.5F, .u = 2.0F, .v = 0.0F },
                Vertex{.x = -1.0F, .y = -3.0F, .z = 0.5F, .u = 0.0F, .v = 2.0F }
            };
        }
    };
}

// module : private;
