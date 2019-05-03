#include "Framework.h"
#include "Geometry_Generator.h"

void Geometry_Generator::CreateQuad(Geometry<VertexColor>& geometry)
{
    geometry.AddVertex(VertexColor({ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }));
    geometry.AddVertex(VertexColor({ -0.5f, +0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }));
    geometry.AddVertex(VertexColor({ +0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }));
    geometry.AddVertex(VertexColor({ +0.5f, +0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }));

    geometry.AddIndex(0); geometry.AddIndex(1); geometry.AddIndex(2);
    geometry.AddIndex(2); geometry.AddIndex(1); geometry.AddIndex(3);
}

void Geometry_Generator::CreateQuad(Geometry<VertexTexture>& geometry)
{
    geometry.AddVertex(VertexTexture({ -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f }));
    geometry.AddVertex(VertexTexture({ -0.5f, +0.5f, 0.0f }, { 0.0f, 0.0f }));
    geometry.AddVertex(VertexTexture({ +0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }));
    geometry.AddVertex(VertexTexture({ +0.5f, +0.5f, 0.0f }, { 1.0f, 0.0f }));

    geometry.AddIndex(0); geometry.AddIndex(1); geometry.AddIndex(2);
    geometry.AddIndex(2); geometry.AddIndex(1); geometry.AddIndex(3);
}