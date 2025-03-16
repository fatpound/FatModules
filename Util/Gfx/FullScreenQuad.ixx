module;

export module FatPound.Util.Gfx.FullScreenQuad;

import std;

export namespace fatpound::util::gfx
{
    struct FullScreenQuad final
    {
        struct Vertex final
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
                Vertex{ -1.0f,  1.0f,  0.5f,  0.0f,  0.0f },
                Vertex{  1.0f,  1.0f,  0.5f,  1.0f,  0.0f },
                Vertex{  1.0f, -1.0f,  0.5f,  1.0f,  1.0f },
                Vertex{ -1.0f,  1.0f,  0.5f,  0.0f,  0.0f },
                Vertex{  1.0f, -1.0f,  0.5f,  1.0f,  1.0f },
                Vertex{ -1.0f, -1.0f,  0.5f,  0.0f,  1.0f }
            };
        }
    };
}

module : private;
