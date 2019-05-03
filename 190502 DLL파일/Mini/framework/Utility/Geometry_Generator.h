#pragma once

template <typename T> class Geometry;

class Geometry_Generator final
{
public:
    static void CreateQuad(Geometry<struct VertexColor>& geometry);
    static void CreateQuad(Geometry<struct VertexTexture>& geometry);

};