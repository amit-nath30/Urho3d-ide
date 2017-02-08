#include "runtimehandles.h"

#include <cmath>

#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/IndexBuffer.h>

#include <Urho3D/Container/Ptr.h>



Urho3D::Context* RuntimeHandles::context_ = nullptr;
Urho3D::Camera* RuntimeHandles::camera_ = nullptr;
Urho3D::Graphics* RuntimeHandles::graphics_ = nullptr;

Urho3D::Matrix3x4 RuntimeHandles::view_ = Urho3D::Matrix3x4::IDENTITY;
Urho3D::Matrix4 RuntimeHandles::projection_ = Urho3D::Matrix4::IDENTITY;

Urho3D::ShaderVariation* RuntimeHandles::vs = nullptr;
Urho3D::ShaderVariation* RuntimeHandles::ps = nullptr;

Urho3D::Color RuntimeHandles::XColor = Urho3D::Color(0.73f, 0.27f, 0.18f, 1.0f);
Urho3D::Color RuntimeHandles::XColorTransparent = Urho3D::Color(0.73f, 0.27f, 0.18f, 0.5f);
Urho3D::Color RuntimeHandles::YColor = Urho3D::Color(0.55f, 0.8f, 0.3f, 1.0f);
Urho3D::Color RuntimeHandles::YColorTransparent = Urho3D::Color(0.55f, 0.8f, 0.3f, 0.5f);
Urho3D::Color RuntimeHandles::ZColor = Urho3D::Color(0.22f, 0.45f, 0.96f, 1.0f);
Urho3D::Color RuntimeHandles::ZColorTransparent = Urho3D::Color(0.22f, 0.45f, 0.96f, 0.5f);
Urho3D::Color RuntimeHandles::AltColor = Urho3D::Color(0.75f, 0.75f, 0.75f, 0.96f);
Urho3D::Color RuntimeHandles::SelectionColor = Urho3D::Color(0.94f, 0.93f, 0.25f, 0.5f);
Urho3D::Color RuntimeHandles::BoundsColor = Urho3D::Color::GREEN;
Urho3D::Color RuntimeHandles::RaysColor = Urho3D::Color(1.0f, 1.0f, 1.0f, 0.19f);

Urho3D::Geometry* RuntimeHandles::Arrows = nullptr;
Urho3D::Geometry* RuntimeHandles::SelectionArrowY = nullptr;
Urho3D::Geometry* RuntimeHandles::SelectionArrowX = nullptr;
Urho3D::Geometry* RuntimeHandles::SelectionArrowZ = nullptr;

Urho3D::Geometry* RuntimeHandles::SelectionCube = nullptr;
Urho3D::Geometry* RuntimeHandles::CubeX = nullptr;
Urho3D::Geometry* RuntimeHandles::CubeY = nullptr;
Urho3D::Geometry* RuntimeHandles::CubeZ = nullptr;
Urho3D::Geometry* RuntimeHandles::CubeUniform = nullptr;

Urho3D::Geometry* RuntimeHandles::SceneGizmoSelectedAxis = nullptr;
Urho3D::Geometry* RuntimeHandles::SceneGizmoXAxis = nullptr;
Urho3D::Geometry* RuntimeHandles::SceneGizmoYAxis = nullptr;
Urho3D::Geometry* RuntimeHandles::SceneGizmoZAxis = nullptr;
Urho3D::Geometry* RuntimeHandles::SceneGizmoCube = nullptr;
Urho3D::Geometry* RuntimeHandles::SceneGizmoSelectedCube = nullptr;
Urho3D::Geometry* RuntimeHandles::SceneGizmoQuad = nullptr;



void RuntimeHandles::Initialize(Urho3D::Context *context, Urho3D::Graphics *graphics, Urho3D::Camera* camera)
{
    context_    = context;
    graphics_   = graphics;
    camera_     = camera;

    view_           = camera_->GetView();
    projection_     = camera_->GetProjection();

    vs = graphics_->GetShader(Urho3D::VS, "Basic", "VERTEXCOLOR");
    ps = graphics_->GetShader(Urho3D::PS, "Basic", "VERTEXCOLOR");

    /*LinesMaterial = new Material(Shader.Find("Battlehub/RTHandles/VertexColor"));
    LinesMaterial.color = Urho3D::Color::WHITE;

    LinesMaterialZTest = new Material(Shader.Find("Battlehub/RTHandles/VertexColor"));
    LinesMaterialZTest.color = Urho3D::Color::WHITE;
    LinesMaterialZTest.SetFloat("_ZTest", (float)UnityEngine.Rendering.CompareFunction.LessEqual);

    LinesClipMaterial = new Material(Shader.Find("Battlehub/RTHandles/VertexColorClip"));
    LinesClipMaterial.color = Urho3D::Color::WHITE;

    LinesBillboardMaterial = new Material(Shader.Find("Battlehub/RTHandles/VertexColorBillboard"));
    LinesBillboardMaterial.color = Urho3D::Color::WHITE;

    ShapesMaterial = new Material(Shader.Find("Battlehub/RTHandles/Shape"));
    ShapesMaterial.color = Urho3D::Color::WHITE;

    ShapesMaterialZTest = new Material(Shader.Find("Battlehub/RTHandles/Shape"));
    ShapesMaterialZTest.color = new Urho3D::Color(1, 1, 1, 0);
    ShapesMaterialZTest.SetFloat("_ZTest", (float)UnityEngine.Rendering.CompareFunction.LessEqual);
    ShapesMaterialZTest.SetFloat("_ZWrite", 1.0f);

    ShapesMaterialZTestOffset = new Material(Shader.Find("Battlehub/RTHandles/Shape"));
    ShapesMaterialZTestOffset.color = new Urho3D::Color(1, 1, 1, 1);
    ShapesMaterialZTestOffset.SetFloat("_ZTest", (float)UnityEngine.Rendering.CompareFunction.LessEqual);
    ShapesMaterialZTestOffset.SetFloat("_ZWrite", 1.0f);
    ShapesMaterialZTestOffset.SetFloat("_OFactors", -1.0f);
    ShapesMaterialZTestOffset.SetFloat("_OUnits", -1.0f);

    ShapesMaterialZTest2 = new Material(Shader.Find("Battlehub/RTHandles/Shape"));
    ShapesMaterialZTest2.color = new Urho3D::Color(1, 1, 1, 0);
    ShapesMaterialZTest2.SetFloat("_ZTest", (float)UnityEngine.Rendering.CompareFunction.LessEqual);
    ShapesMaterialZTest2.SetFloat("_ZWrite", 1.0f);

    ShapesMaterialZTest3 = new Material(Shader.Find("Battlehub/RTHandles/Shape"));
    ShapesMaterialZTest3.color = new Urho3D::Color(1, 1, 1, 0);
    ShapesMaterialZTest3.SetFloat("_ZTest", (float)UnityEngine.Rendering.CompareFunction.LessEqual);
    ShapesMaterialZTest3.SetFloat("_ZWrite", 1.0f);

    ShapesMaterialZTest4 = new Material(Shader.Find("Battlehub/RTHandles/Shape"));
    ShapesMaterialZTest4.color = new Urho3D::Color(1, 1, 1, 0);
    ShapesMaterialZTest4.SetFloat("_ZTest", (float)UnityEngine.Rendering.CompareFunction.LessEqual);
    ShapesMaterialZTest4.SetFloat("_ZWrite", 1.0f);

    XMaterial = new Material(Shader.Find("Battlehub/RTHandles/Billboard"));
    XMaterial.color = Urho3D::Color::WHITE;
    XMaterial.mainTexture = Resources.Load<Texture>("Battlehub.RuntimeHandles.x");
    YMaterial = new Material(Shader.Find("Battlehub/RTHandles/Billboard"));
    YMaterial.color = Urho3D::Color::WHITE;
    YMaterial.mainTexture = Resources.Load<Texture>("Battlehub.RuntimeHandles.y");
    ZMaterial = new Material(Shader.Find("Battlehub/RTHandles/Billboard"));
    ZMaterial.color = Urho3D::Color::WHITE;
    ZMaterial.mainTexture = Resources.Load<Texture>("Battlehub.RuntimeHandles.z");

    GridMaterial = new Material(Shader.Find("Battlehub/RTHandles/Grid"));
    GridMaterial.color = Urho3D::Color::WHITE;
    GridMaterial.SetFloat("_ZTest", (float)UnityEngine.Rendering.CompareFunction.Never); */


    Urho3D::Matrix3x4 transform = Urho3D::Matrix3x4(Urho3D::Vector3::UP * HandleScale, Urho3D::Quaternion::identity, Urho3D::Vector3::ONE);

    SelectionArrowY = CreateConeMesh(SelectionColor, transform, HandleScale);

    transform = Urho3D::Matrix3x4(Urho3D::Vector3::RIGHT * HandleScale, Urho3D::Quaternion(-90, Urho3D::Vector3::FORWARD), Urho3D::Vector3::ONE);
    SelectionArrowX = CreateConeMesh(SelectionColor, transform, HandleScale);

    transform = Urho3D::Matrix3x4(Urho3D::Vector3::FORWARD * HandleScale, Urho3D::Quaternion(90, Urho3D::Vector3::RIGHT), Urho3D::Vector3::ONE);
    SelectionArrowZ = CreateConeMesh(SelectionColor, transform, HandleScale);

    //yArrow.mesh = CreateConeMesh(YColor, HandleScale);
    //xArrow.mesh = CreateConeMesh(XColor, HandleScale);
    //zArrow.mesh = CreateConeMesh(ZColor, HandleScale);


    transform = Urho3D::Matrix3x4(Urho3D::Vector3::UP * HandleScale, Urho3D::Quaternion::identity, Urho3D::Vector3::ONE);
    Arrows = CreateConeMesh(YColor, transform, HandleScale);

    transform = Urho3D::Matrix3x4(Urho3D::Vector3::RIGHT * HandleScale, Urho3D::Quaternion(-90, Urho3D::Vector3::FORWARD), Urho3D::Vector3::ONE);
    Arrows = CombineVertexBuffer(Arrows, CreateConeMesh(XColor, transform, HandleScale));

    transform = Urho3D::Matrix3x4(Urho3D::Vector3::FORWARD * HandleScale, Urho3D::Quaternion(90, Urho3D::Vector3::RIGHT), Urho3D::Vector3::ONE);
    Arrows = CombineVertexBuffer(Arrows, CreateConeMesh(ZColor, transform, HandleScale));

    SelectionCube = CreateCubeMesh(SelectionColor, Urho3D::Vector3::ZERO, HandleScale, 0.1f, 0.1f, 0.1f);
    CubeX = CreateCubeMesh(XColor, Urho3D::Vector3::ZERO, HandleScale,  0.1f, 0.1f, 0.1f);
    CubeY = CreateCubeMesh(YColor, Urho3D::Vector3::ZERO, HandleScale, 0.1f, 0.1f, 0.1f);
    CubeZ = CreateCubeMesh(ZColor, Urho3D::Vector3::ZERO, HandleScale, 0.1f, 0.1f, 0.1f);
    CubeUniform = CreateCubeMesh(AltColor, Urho3D::Vector3::ZERO, HandleScale, 0.1f, 0.1f, 0.1f);

    SceneGizmoSelectedAxis = CreateSceneGizmoHalfAxis(SelectionColor, Urho3D::Quaternion(90, Urho3D::Vector3::RIGHT));
    SceneGizmoXAxis = CreateSceneGizmoAxis(XColor, AltColor, Urho3D::Quaternion(-90, Urho3D::Vector3::FORWARD));
    SceneGizmoYAxis = CreateSceneGizmoAxis(YColor, AltColor, Urho3D::Quaternion::IDENTITY);
    SceneGizmoZAxis = CreateSceneGizmoAxis(ZColor, AltColor, Urho3D::Quaternion(90, Urho3D::Vector3::RIGHT));
    SceneGizmoCube = CreateCubeMesh(AltColor, Urho3D::Vector3::ZERO, 1);
    SceneGizmoSelectedCube = CreateCubeMesh(SelectionColor, Urho3D::Vector3::ZERO, 1);
    SceneGizmoQuad = CreateQuadMesh();
}

Urho3D::Geometry* RuntimeHandles::CreateQuadMesh(float quadWidth, float cubeHeight)
{
    float vertices[] = {
        //position                                          normal                      uv
        -quadWidth * .5f,  cubeHeight * .5f,    0,          0.0f, 0.0f, 0.0f,           1.0f,   0.0f,
         quadWidth * .5f,  cubeHeight * .5f,    0,          0.0f, 0.0f, 0.0f,           0.0f,   0.0f,
         quadWidth * .5f, -cubeHeight * .5f,    0,          0.0f, 0.0f, 0.0f,           0.0f,   1.0f,
        -quadWidth * .5f, -cubeHeight * .5f,    0,          0.0f, 0.0f, 0.0f,           1.0f,   1.0f
    };

    const unsigned short indexData[] = {
        // Cube Bottom Side Triangles
        3, 1, 0,
        3, 2, 1,
    };

    // Calculate face normals now
    for (unsigned i = 0; i < 6; i += 3)
    {
        Urho3D::Vector3& v1 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[8 * indexData[i]           ]));
        Urho3D::Vector3& v2 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[8 * indexData[i + 1]       ]));
        Urho3D::Vector3& v3 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[8 * indexData[i + 2]       ]));
        Urho3D::Vector3& n1 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[8 * indexData[i]       + 3 ]));
        Urho3D::Vector3& n2 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[8 * indexData[i + 1]   + 3 ]));
        Urho3D::Vector3& n3 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[8 * indexData[i + 2]   + 3 ]));

        Urho3D::Vector3 edge1 = v1 - v2;
        Urho3D::Vector3 edge2 = v1 - v3;
        n1 = n2 = n3 = edge1.CrossProduct(edge2).Normalized();
    }

    Urho3D::VertexBuffer* vb = new Urho3D::VertexBuffer (context_);
    Urho3D::IndexBuffer*  ib = new Urho3D::IndexBuffer  (context_);

    vb->SetSize(4, Urho3D::MASK_POSITION | Urho3D::MASK_NORMAL | Urho3D::MASK_TEXCOORD1);
    vb->SetData(vertices);

    ib->SetSize(4, false);
    ib->SetData(indexData);

    Urho3D::Geometry* quadMesh = new Urho3D::Geometry(context_);
    quadMesh->SetVertexBuffer(0, vb);
    quadMesh->SetIndexBuffer(ib);
    quadMesh->SetDrawRange(Urho3D::TRIANGLE_LIST, 0, 4);
    return quadMesh;
}

Urho3D::Geometry* RuntimeHandles::CreateCubeMesh(Urho3D::Color color, Urho3D::Vector3 center, float scale, float cubeLength, float cubeWidth, float cubeHeight)
{
    cubeHeight *= scale;
    cubeWidth *= scale;
    cubeLength *= scale;

    Urho3D::Vector3 vertice_0 = center + Urho3D::Vector3(-cubeLength * .5f, -cubeWidth * .5f,  cubeHeight * .5f);
    Urho3D::Vector3 vertice_1 = center + Urho3D::Vector3( cubeLength * .5f, -cubeWidth * .5f,  cubeHeight * .5f);
    Urho3D::Vector3 vertice_2 = center + Urho3D::Vector3( cubeLength * .5f, -cubeWidth * .5f, -cubeHeight * .5f);
    Urho3D::Vector3 vertice_3 = center + Urho3D::Vector3(-cubeLength * .5f, -cubeWidth * .5f, -cubeHeight * .5f);
    Urho3D::Vector3 vertice_4 = center + Urho3D::Vector3(-cubeLength * .5f,  cubeWidth * .5f,  cubeHeight * .5f);
    Urho3D::Vector3 vertice_5 = center + Urho3D::Vector3( cubeLength * .5f,  cubeWidth * .5f,  cubeHeight * .5f);
    Urho3D::Vector3 vertice_6 = center + Urho3D::Vector3( cubeLength * .5f,  cubeWidth * .5f, -cubeHeight * .5f);
    Urho3D::Vector3 vertice_7 = center + Urho3D::Vector3(-cubeLength * .5f,  cubeWidth * .5f, -cubeHeight * .5f);

    float vertices[] = {
        //Position                                  Normal              Vertex-Color
        vertice_0.x_, vertice_0.y_, vertice_0.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_1.x_, vertice_1.y_, vertice_1.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_2.x_, vertice_2.y_, vertice_2.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_3.x_, vertice_3.y_, vertice_3.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,

        vertice_7.x_, vertice_7.y_, vertice_7.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_4.x_, vertice_4.y_, vertice_7.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_0.x_, vertice_0.y_, vertice_0.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_3.x_, vertice_3.y_, vertice_3.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,

        vertice_4.x_, vertice_4.y_, vertice_4.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_5.x_, vertice_5.y_, vertice_5.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_1.x_, vertice_1.y_, vertice_1.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_0.x_, vertice_0.y_, vertice_0.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,

        vertice_6.x_, vertice_6.y_, vertice_6.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_7.x_, vertice_7.y_, vertice_7.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_3.x_, vertice_3.y_, vertice_3.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_2.x_, vertice_2.y_, vertice_2.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,

        vertice_5.x_, vertice_5.y_, vertice_5.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_6.x_, vertice_6.y_, vertice_6.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_2.x_, vertice_2.y_, vertice_2.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_1.x_, vertice_1.y_, vertice_1.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,

        vertice_7.x_, vertice_7.y_, vertice_7.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_6.x_, vertice_6.y_, vertice_6.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_5.x_, vertice_5.y_, vertice_5.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
        vertice_4.x_, vertice_4.y_, vertice_4.z_,   0.0f, 0.0f, 0.0f,   color.r_, color.g_, color.b_, color.a_,
    };

    const unsigned short indexData[] = {
        // Cube Bottom Side Triangles
        3, 1, 0,
        3, 2, 1,
        // Cube Left Side Triangles
        3 + 4 * 1, 1 + 4 * 1, 0 + 4 * 1,
        3 + 4 * 1, 2 + 4 * 1, 1 + 4 * 1,
        // Cube Front Side Triangles
        3 + 4 * 2, 1 + 4 * 2, 0 + 4 * 2,
        3 + 4 * 2, 2 + 4 * 2, 1 + 4 * 2,
        // Cube Back Side Triangles
        3 + 4 * 3, 1 + 4 * 3, 0 + 4 * 3,
        3 + 4 * 3, 2 + 4 * 3, 1 + 4 * 3,
        // Cube Rigth Side Triangles
        3 + 4 * 4, 1 + 4 * 4, 0 + 4 * 4,
        3 + 4 * 4, 2 + 4 * 4, 1 + 4 * 4,
        // Cube Top Side Triangles
        3 + 4 * 5, 1 + 4 * 5, 0 + 4 * 5,
        3 + 4 * 5, 2 + 4 * 5, 1 + 4 * 5,
    };

    // Calculate face normals now
    for (unsigned i = 0; i < 36; i += 3)
    {
        Urho3D::Vector3& v1 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i]           ]));
        Urho3D::Vector3& v2 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 1]       ]));
        Urho3D::Vector3& v3 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 2]       ]));
        Urho3D::Vector3& n1 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i]       + 3 ]));
        Urho3D::Vector3& n2 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 1]   + 3 ]));
        Urho3D::Vector3& n3 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 2]   + 3 ]));

        Urho3D::Vector3 edge1 = v1 - v2;
        Urho3D::Vector3 edge2 = v1 - v3;
        n1 = n2 = n3 = edge1.CrossProduct(edge2).Normalized();
    }

    Urho3D::VertexBuffer* vb = new Urho3D::VertexBuffer (context_);
    Urho3D::IndexBuffer*  ib = new Urho3D::IndexBuffer  (context_);

    vb->SetSize(24, Urho3D::MASK_POSITION | Urho3D::MASK_NORMAL | Urho3D::MASK_COLOR);
    vb->SetData(vertices);

    ib->SetSize(24, false);
    ib->SetData(indexData);

    Urho3D::Geometry* cubeMesh = new Urho3D::Geometry(context_);
    cubeMesh->SetVertexBuffer(0, vb);
    cubeMesh->SetIndexBuffer (ib);
    cubeMesh->SetDrawRange(Urho3D::TRIANGLE_LIST, 0, 24);

    return cubeMesh;
}

Urho3D::Geometry* RuntimeHandles::CreateConeMesh(Urho3D::Color color, Urho3D::Matrix3x4 transform, float scale)
{
    int segmentsCount = 12;
    float size = 1.0f / 5;
    size *= scale;

    //for each position 10 float value is needed, 3for position 3for normal 4for color
    float vertices[segmentsCount * 3 * 10 + 1 * 10];
    unsigned short indexData[segmentsCount * 6];

    float radius = size / 2.6f;
    float height = size;
    float deltaAngle = M_PI * 2.0f / segmentsCount;

    float y = -height;

    for (int i = 0; i < segmentsCount; i++)
    {
        float angle = i * deltaAngle;
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;

        Urho3D::Vector3 position    = transform * Urho3D::Vector3(z, y, z);
        Urho3D::Vector3 zero        = transform * Urho3D::Vector3::ZERO;

        int indexOne = i * 10;
        //position
        vertices[indexOne + 0] = position.x_; vertices[indexOne + 1] = position.y_; vertices[indexOne + 2] = position.z_;
        //normal
        vertices[indexOne + 3] = 0.0f; vertices[indexOne + 4] = 0.0f; vertices[indexOne + 5] = 0.0f;
        //color
        vertices[indexOne + 6] = color.r_; vertices[indexOne + 7] = color.g_; vertices[indexOne + 8] = color.b_; vertices[indexOne + 9] = color.a_;


        int indexTwo = segmentsCount * 1 * 10;
        //position
        vertices[indexTwo + indexOne + 0] = zero.x_; vertices[indexTwo + indexOne + 1] = zero.y_; vertices[indexTwo + indexOne + 2] = zero.z_;
        //normal
        vertices[indexTwo + indexOne + 3] = 0.0f; vertices[indexTwo + indexOne + 4] = 0.0f; vertices[indexTwo + indexOne + 5] = 0.0f;
        //color
        vertices[indexTwo + indexOne + 6] = color.r_; vertices[indexTwo + indexOne + 7] = color.g_; vertices[indexTwo + indexOne + 8] = color.b_; vertices[indexTwo + indexOne + 9] = color.a_;


        int indexThree = segmentsCount * 2 * 10;
        //position
        vertices[indexThree + indexOne + 0] = position.x_; vertices[indexThree + indexOne + 1] = position.y_; vertices[indexThree + indexOne + 2] = position.z_;
        //normal
        vertices[indexThree + indexOne + 3] = 0.0f; vertices[indexThree + indexOne + 4] = 0.0f; vertices[indexThree + indexOne + 5] = 0.0f;
        //color
        vertices[indexThree + indexOne + 6] = color.r_; vertices[indexThree + indexOne + 7] = color.g_; vertices[indexThree + indexOne + 8] = color.b_; vertices[indexThree + indexOne + 9] = color.a_;
    }

    Urho3D::Vector3 position    = transform * Urho3D::Vector3(0.0f, -height, 0.0f);
    int index = segmentsCount * 3 * 10;
    //position
    vertices[index + 0] = position.x_; vertices[index + 1] = position.y_; vertices[index + 2] = position.z_;
    //normal
    vertices[index + 3] = 0.0f; vertices[index + 4] = 0.0f; vertices[index + 5] = 0.0f;
    //color
    vertices[index + 6] = color.r_; vertices[index + 7] = color.g_; vertices[index + 8] = color.b_; vertices[index + 9] = color.a_;


    for (int i = 0; i < segmentsCount; i++)
    {
        indexData[i * 6] = i;
        indexData[i * 6 + 1] = segmentsCount + i;
        indexData[i * 6 + 2] = (i + 1) % segmentsCount;

        indexData[i * 6 + 3] = 36; //hard coded array length
        indexData[i * 6 + 4] = 2 * segmentsCount + i;
        indexData[i * 6 + 5] = 2 * segmentsCount + (i + 1) % segmentsCount;
    }

    // Calculate face normals now
    for (unsigned i = 0; i < 72; i += 3)
    {
        Urho3D::Vector3& v1 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i]           ]));
        Urho3D::Vector3& v2 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 1]       ]));
        Urho3D::Vector3& v3 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 2]       ]));
        Urho3D::Vector3& n1 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i]       + 3 ]));
        Urho3D::Vector3& n2 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 1]   + 3 ]));
        Urho3D::Vector3& n3 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 2]   + 3 ]));

        Urho3D::Vector3 edge1 = v1 - v2;
        Urho3D::Vector3 edge2 = v1 - v3;
        n1 = n2 = n3 = edge1.CrossProduct(edge2).Normalized();
    }

    Urho3D::VertexBuffer* vb = new Urho3D::VertexBuffer (context_);
    Urho3D::IndexBuffer*  ib = new Urho3D::IndexBuffer  (context_);

    vb->SetSize(37, Urho3D::MASK_POSITION | Urho3D::MASK_NORMAL | Urho3D::MASK_COLOR);
    vb->SetData(vertices);

    ib->SetSize(37, false);
    ib->SetData(indexData);

    Urho3D::Geometry* cone = new Urho3D::Geometry(context_);
    cone->SetVertexBuffer(0, vb);
    cone->SetIndexBuffer(ib);
    cone->SetDrawRange(Urho3D::TRIANGLE_LIST, 0, 37);

    return cone;
}

/* Urho3D::Geometry* RuntimeHandles::CreateConeMesh(Urho3D::Color color, Urho3D::Matrix3x4 transform, float scale)
{
    int segmentsCount = 12;
    float size = 1.0f / 5;
    size *= scale;

    //for each position 10 float value is needed, 3for position 3for normal 4for color
    float vertices[segmentsCount * 3 * 10 + 1 * 10];
    unsigned short indexData[segmentsCount * 6];

    float radius = size / 2.6f;
    float height = size;
    float deltaAngle = M_PI * 2.0f / segmentsCount;

    float y = -height;

    for (int i = 0; i < segmentsCount; i++)
    {
        float angle = i * deltaAngle;
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;

        int indexOne = i * 10;
        //position
        vertices[indexOne + 0] = x; vertices[indexOne + 1] = y; vertices[indexOne + 2] = z;
        //normal
        vertices[indexOne + 3] = 0.0f; vertices[indexOne + 4] = 0.0f; vertices[indexOne + 5] = 0.0f;
        //color
        vertices[indexOne + 6] = color.r_; vertices[indexOne + 7] = color.g_; vertices[indexOne + 8] = color.b_; vertices[indexOne + 9] = color.a_;


        int indexTwo = segmentsCount * 1 * 10;
        //position
        vertices[indexTwo + indexOne + 0] = 0.0f; vertices[indexTwo + indexOne + 1] = 0.0f; vertices[indexTwo + indexOne + 2] = 0.0f;
        //normal
        vertices[indexTwo + indexOne + 3] = 0.0f; vertices[indexTwo + indexOne + 4] = 0.0f; vertices[indexTwo + indexOne + 5] = 0.0f;
        //color
        vertices[indexTwo + indexOne + 6] = color.r_; vertices[indexTwo + indexOne + 7] = color.g_; vertices[indexTwo + indexOne + 8] = color.b_; vertices[indexTwo + indexOne + 9] = color.a_;


        int indexThree = segmentsCount * 2 * 10;
        //position
        vertices[indexThree + indexOne + 0] = x; vertices[indexThree + indexOne + 1] = y; vertices[indexThree + indexOne + 2] = z;
        //normal
        vertices[indexThree + indexOne + 3] = 0.0f; vertices[indexThree + indexOne + 4] = 0.0f; vertices[indexThree + indexOne + 5] = 0.0f;
        //color
        vertices[indexThree + indexOne + 6] = color.r_; vertices[indexThree + indexOne + 7] = color.g_; vertices[indexThree + indexOne + 8] = color.b_; vertices[indexThree + indexOne + 9] = color.a_;
    }

    int index = segmentsCount * 3 * 10;
    //position
    vertices[index + 0] = 0.0f; vertices[index + 1] = -height; vertices[index + 2] = 0.0f;
    //normal
    vertices[index + 3] = 0.0f; vertices[index + 4] = 0.0f; vertices[index + 5] = 0.0f;
    //color
    vertices[index + 6] = color.r_; vertices[index + 7] = color.g_; vertices[index + 8] = color.b_; vertices[index + 9] = color.a_;


    for (int i = 0; i < segmentsCount; i++)
    {
        indexData[i * 6] = i;
        indexData[i * 6 + 1] = segmentsCount + i;
        indexData[i * 6 + 2] = (i + 1) % segmentsCount;

        indexData[i * 6 + 3] = 36; //hard coded array length
        indexData[i * 6 + 4] = 2 * segmentsCount + i;
        indexData[i * 6 + 5] = 2 * segmentsCount + (i + 1) % segmentsCount;
    }

    // Calculate face normals now
    for (unsigned i = 0; i < 72; i += 3)
    {
        Urho3D::Vector3& v1 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i]           ]));
        Urho3D::Vector3& v2 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 1]       ]));
        Urho3D::Vector3& v3 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 2]       ]));
        Urho3D::Vector3& n1 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i]       + 3 ]));
        Urho3D::Vector3& n2 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 1]   + 3 ]));
        Urho3D::Vector3& n3 = *(reinterpret_cast<Urho3D::Vector3*>(&vertices[10 * indexData[i + 2]   + 3 ]));

        Urho3D::Vector3 edge1 = v1 - v2;
        Urho3D::Vector3 edge2 = v1 - v3;
        n1 = n2 = n3 = edge1.CrossProduct(edge2).Normalized();
    }

    Urho3D::VertexBuffer* vb = new Urho3D::VertexBuffer (context_);
    Urho3D::IndexBuffer*  ib = new Urho3D::IndexBuffer  (context_);

    vb->SetSize(37, Urho3D::MASK_POSITION | Urho3D::MASK_NORMAL | Urho3D::MASK_COLOR);
    vb->SetData(vertices);

    ib->SetSize(37, false);
    ib->SetData(indexData);

    Urho3D::Geometry* cone = new Urho3D::Geometry(context_);
    cone->SetVertexBuffer(0, vb);
    cone->SetIndexBuffer(ib);
    cone->SetDrawRange(Urho3D::TRIANGLE_LIST, 0, 37);

    return cone;
} */

Urho3D::Geometry* RuntimeHandles::CreateSceneGizmoHalfAxis(Urho3D::Color color, Urho3D::Quaternion rotation)
{
    const float scale = 0.1f;
    Urho3D::Matrix3x4 transform = Urho3D::Matrix3x4(Urho3D::Vector3::UP * scale, Urho3D::Quaternion(180, Urho3D::Vector3::RIGHT), Urho3D::Vector3::ONE);

    //CombineInstance cone1Combine = new CombineInstance();
    //cone1Combine.mesh = cone1;
    //cone1Combine.transform = Urho3D::Matrix3x4(Urho3D::Vector3::UP * scale, Urho3D::Quaternion(180, Urho3D::Vector3::RIGHT), Urho3D::Vector3::ONE);

    //Urho3D::Geometry* result = new Urho3D::Geometry(context_);
    //result.CombineMeshes(new[] { cone1Combine }, true);

    //CombineInstance rotateCombine = new CombineInstance();
    //rotateCombine.mesh = result;
    //rotateCombine.transform = Urho3D::Matrix3x4(Urho3D::Vector3::ZERO, rotation, Urho3D::Vector3::ONE);

    //result = new Urho3D::Geometry(context_);
    //result.CombineMeshes(new[] { rotateCombine }, true);
    //result.RecalculateNormals();

    Urho3D::Geometry* result = CreateConeMesh(color, transform, 1);

    transform = Urho3D::Matrix3x4(Urho3D::Vector3::ZERO, rotation, Urho3D::Vector3::ONE);
    result = CombineVertexBuffer(result, CreateConeMesh(color, transform, 1));

    return result;
}

Urho3D::Geometry* RuntimeHandles::CreateSceneGizmoAxis(Urho3D::Color axisColor, Urho3D::Color altColor, Urho3D::Quaternion rotation)
{
    const float scale = 0.1f;
    Urho3D::Matrix3x4 transform = Urho3D::Matrix3x4(Urho3D::Vector3::UP * scale, Urho3D::Quaternion(180, Urho3D::Vector3::RIGHT), Urho3D::Vector3::ONE);
    /*Urho3D::Geometry* cone1 = CreateConeMesh(axisColor, transform, 1);
    Urho3D::Geometry* cone2 = CreateConeMesh(altColor, transform, 1);

    CombineInstance cone1Combine = new CombineInstance();
    cone1Combine.mesh = cone1;
    cone1Combine.transform = Urho3D::Matrix3x4(Urho3D::Vector3::UP * scale, Urho3D::Quaternion(180, Urho3D::Vector3::RIGHT), Urho3D::Vector3::ONE);

    CombineInstance cone2Combine = new CombineInstance();
    cone2Combine.mesh = cone2;
    cone2Combine.transform = Urho3D::Matrix3x4(Urho3D::Vector3::DOWN * scale, Urho3D::Quaternion::IDENTITY, Urho3D::Vector3::ONE);

    Urho3D::Geometry* result = new Urho3D::Geometry(context_);
    result.CombineMeshes(new[] { cone1Combine, cone2Combine }, true);

    CombineInstance rotateCombine = new CombineInstance();
    rotateCombine.mesh = result;
    rotateCombine.transform = Urho3D::Matrix3x4(Urho3D::Vector3::ZERO, rotation, Urho3D::Vector3::ONE);

    result = new Urho3D::Geometry(context_);
    result.CombineMeshes(new[] { rotateCombine }, true);
    result.RecalculateNormals();*/

    Urho3D::Geometry* result = CreateConeMesh(axisColor, transform, 1);
    result = CombineVertexBuffer(result, CreateConeMesh(altColor, transform, 1));



    return result;
}

float RuntimeHandles::GetScreenScale(Urho3D::Vector3 position)
{
    float h = graphics_->GetHeight(); //camera_->pixelHeight;
    if (camera_->IsOrthographic())
    {
        return camera_->GetOrthoSize() * 2.0f / h * 90;
    }

    Urho3D::Node* transform = camera_->GetNode();
    float distance = (position - transform->GetWorldPosition()).DotProduct(transform->GetDirection());
    float scale = 2.0f * distance * tan(camera_->GetFov() * 0.5f * DEG_2_RAD);
    return scale / h * 90;
}

void RuntimeHandles::DoAxes(Urho3D::Vector3 position, Urho3D::Matrix3x4 transform, RuntimeHandleAxis selectedAxis)
{
    Urho3D::Vector3 x = Urho3D::Vector3::RIGHT * HandleScale;
    Urho3D::Vector3 y = Urho3D::Vector3::UP * HandleScale;
    Urho3D::Vector3 z = Urho3D::Vector3::FORWARD * HandleScale;

    x = transform * x;
    y = transform * y;
    z = transform * z;

    Urho3D::Color color;
    Urho3D::VertexBuffer* vb = new Urho3D::VertexBuffer(context_);

    float vertices[30];

    color = selectedAxis != RuntimeHandleAxis::X ? XColor : SelectionColor;
    vertices[0] = position.x_; vertices[1] = position.y_; vertices[2] = position.z_;
    vertices[6] = color.r_; vertices[7] = color.g_; vertices[8] = color.b_; vertices[9] = color.a_;

    vertices[3] = position.x_ + x.x_; vertices[4] = position.y_ + x.y_; vertices[5] = position.z_ + x.z_;
    vertices[6] = color.r_; vertices[7] = color.g_; vertices[8] = color.b_; vertices[9] = color.a_;

    color = selectedAxis != RuntimeHandleAxis::Y ? YColor : SelectionColor;
    vertices[10] = position.x_; vertices[11] = position.y_; vertices[12] = position.z_;
    vertices[16] = color.r_; vertices[17] = color.g_; vertices[18] = color.b_; vertices[19] = color.a_;

    vertices[13] = position.x_ + y.x_; vertices[14] = position.y_ + y.y_; vertices[15] = position.z_ + y.z_;
    vertices[16] = color.r_; vertices[17] = color.g_; vertices[18] = color.b_; vertices[19] = color.a_;

    color = selectedAxis != RuntimeHandleAxis::Z ? ZColor : SelectionColor;
    vertices[20] = position.x_; vertices[21] = position.y_; vertices[22] = position.z_;
    vertices[26] = color.r_; vertices[27] = color.g_; vertices[28] = color.b_; vertices[29] = color.a_;

    vertices[23] = position.x_ + z.x_; vertices[24] = position.y_ + z.y_; vertices[25] = position.z_ + z.z_;
    vertices[26] = color.r_; vertices[27] = color.g_; vertices[28] = color.b_; vertices[29] = color.a_;

    vb->SetSize(6, Urho3D::MASK_POSITION | Urho3D::MASK_COLOR);
    vb->SetData(vertices);

    graphics_->SetVertexBuffer(vb);

    graphics_->SetDepthTest(Urho3D::CMP_ALWAYS);
    graphics_->Draw(Urho3D::LINE_LIST, 0, 6);

}


void RuntimeHandles::DoPositionHandle(Urho3D::Vector3 position, Urho3D::Quaternion rotation,
    RuntimeHandleAxis selectedAxis, bool snapMode)
{
    float screenScale = GetScreenScale(position);

    Urho3D::VertexBuffer* vb;
    Urho3D::Color color;

    Urho3D::Matrix3x4 transform = Urho3D::Matrix3x4(position, rotation, screenScale);

    //LinesMaterial.SetPass(0);

    //GL.Begin(GL.LINES);
    SetGraphicsForDrawing();
    DoAxes(position, transform, selectedAxis);

    const float s = 0.2f;
    Urho3D::Vector3 x = Urho3D::Vector3::RIGHT * s;
    Urho3D::Vector3 y = Urho3D::Vector3::UP * s;
    Urho3D::Vector3 z = Urho3D::Vector3::FORWARD * s;

    if (snapMode)
    {
        float vertices[56];

        SetGraphicsForDrawing(transform);

        if(selectedAxis == RuntimeHandleAxis::Snap)
        {
            color = SelectionColor;
        }
        else
        {
            color = AltColor;
        }

        float s2 = s / 2 * HandleScale;
        Urho3D::Vector3 p0 = Urho3D::Vector3( s2,  s2, 0);
        Urho3D::Vector3 p1 = Urho3D::Vector3( s2, -s2, 0);
        Urho3D::Vector3 p2 = Urho3D::Vector3(-s2, -s2, 0);
        Urho3D::Vector3 p3 = Urho3D::Vector3(-s2,  s2, 0);

        vertices[0] = p0.x_; vertices[1] = p0.x_; vertices[2] = p0.x_;
        vertices[3] = color.r_; vertices[4] = color.g_; vertices[5] = color.b_; vertices[6] = color.a_;

        vertices[7] = p1.x_; vertices[8] = p1.x_; vertices[9] = p1.x_;
        vertices[10] = color.r_; vertices[11] = color.g_; vertices[12] = color.b_; vertices[13] = color.a_;

        vertices[14] = p1.x_; vertices[15] = p1.x_; vertices[16] = p1.x_;
        vertices[17] = color.r_; vertices[18] = color.g_; vertices[19] = color.b_; vertices[20] = color.a_;

        vertices[21] = p2.x_; vertices[22] = p2.x_; vertices[23] = p2.x_;
        vertices[24] = color.r_; vertices[25] = color.g_; vertices[26] = color.b_; vertices[27] = color.a_;

        vertices[28] = p2.x_; vertices[29] = p2.x_; vertices[30] = p2.x_;
        vertices[31] = color.r_; vertices[32] = color.g_; vertices[33] = color.b_; vertices[34] = color.a_;

        vertices[35] = p3.x_; vertices[36] = p3.x_; vertices[37] = p3.x_;
        vertices[38] = color.r_; vertices[39] = color.g_; vertices[40] = color.b_; vertices[41] = color.a_;

        vertices[42] = p3.x_; vertices[43] = p3.x_; vertices[44] = p3.x_;
        vertices[45] = color.r_; vertices[46] = color.g_; vertices[47] = color.b_; vertices[48] = color.a_;

        vertices[49] = p0.x_; vertices[50] = p0.x_; vertices[51] = p0.x_;
        vertices[52] = color.r_; vertices[53] = color.g_; vertices[54] = color.b_; vertices[55] = color.a_;

        vb->SetSize(8, Urho3D::MASK_POSITION | Urho3D::MASK_COLOR);
        vb->SetData(vertices);

        graphics_->SetVertexBuffer(vb);

        graphics_->SetDepthTest(Urho3D::CMP_ALWAYS);
        graphics_->Draw(Urho3D::LINE_LIST, 0, 8);

    }
    else
    {
        Urho3D::Vector3 toCam = camera_->GetNode()->GetWorldPosition() - position;

        float vertices[168];

        float fx = SIGN(toCam.DotProduct(x)) * HandleScale;
        float fy = SIGN(toCam.DotProduct(y)) * HandleScale;
        float fz = SIGN(toCam.DotProduct(z)) * HandleScale;

        x.x_ *= fx;
        y.y_ *= fy;
        z.z_ *= fz;

        Urho3D::Vector3 xy = x + y;
        Urho3D::Vector3 xz = x + z;
        Urho3D::Vector3 yz = y + z;

        x = transform * x;
        y = transform * y;
        z = transform * z;
        xy = transform * xy;
        xz = transform * xz;
        yz = transform * yz;

        color = selectedAxis != RuntimeHandleAxis::XZ ? YColor : SelectionColor;
        vertices[0] = position.x_; vertices[1] = position.y_; vertices[2] = position.z_;
        vertices[3] = color.r_; vertices[4] = color.g_; vertices[5] = color.b_; vertices[6] = color.a_;

        vertices[7] = z.x_; vertices[8] = z.y_; vertices[9] = z.z_;
        vertices[10] = color.r_; vertices[11] = color.g_; vertices[12] = color.b_; vertices[13] = color.a_;

        vertices[14] = z.x_; vertices[15] = z.y_; vertices[16] = z.z_;
        vertices[17] = color.r_; vertices[18] = color.g_; vertices[19] = color.b_; vertices[20] = color.a_;

        vertices[21] = xz.x_; vertices[22] = xz.y_; vertices[23] = xz.z_;
        vertices[24] = color.r_; vertices[25] = color.g_; vertices[26] = color.b_; vertices[27] = color.a_;

        vertices[28] = xz.x_; vertices[29] = xz.y_; vertices[30] = xz.z_;
        vertices[31] = color.r_; vertices[32] = color.g_; vertices[33] = color.b_; vertices[34] = color.a_;

        vertices[35] = x.x_; vertices[36] = x.y_; vertices[37] = x.z_;
        vertices[38] = color.r_; vertices[39] = color.g_; vertices[40] = color.b_; vertices[41] = color.a_;

        vertices[42] = x.x_; vertices[43] = x.y_; vertices[44] = x.z_;
        vertices[45] = color.r_; vertices[46] = color.g_; vertices[47] = color.b_; vertices[48] = color.a_;

        vertices[49] = position.x_; vertices[50] = position.y_; vertices[51] = position.z_;
        vertices[52] = color.r_; vertices[53] = color.g_; vertices[54] = color.b_; vertices[55] = color.a_;

        color = selectedAxis != RuntimeHandleAxis::XY ? ZColor : SelectionColor;
        vertices[56] = position.x_; vertices[57] = position.y_; vertices[58] = position.z_;
        vertices[59] = color.r_; vertices[60] = color.g_; vertices[61] = color.b_; vertices[62] = color.a_;

        vertices[63] = y.x_; vertices[64] = y.y_; vertices[65] = y.z_;
        vertices[66] = color.r_; vertices[67] = color.g_; vertices[68] = color.b_; vertices[69] = color.a_;

        vertices[70] = y.x_; vertices[71] = y.y_; vertices[72] = y.z_;
        vertices[73] = color.r_; vertices[74] = color.g_; vertices[75] = color.b_; vertices[76] = color.a_;

        vertices[77] = xy.x_; vertices[78] = xy.y_; vertices[79] = xy.z_;
        vertices[80] = color.r_; vertices[81] = color.g_; vertices[82] = color.b_; vertices[83] = color.a_;

        vertices[84] = xy.x_; vertices[85] = xy.y_; vertices[86] = xy.z_;
        vertices[87] = color.r_; vertices[88] = color.g_; vertices[89] = color.b_; vertices[90] = color.a_;

        vertices[91] = x.x_; vertices[92] = x.y_; vertices[93] = x.z_;
        vertices[94] = color.r_; vertices[95] = color.g_; vertices[96] = color.b_; vertices[97] = color.a_;

        vertices[98] = x.x_; vertices[99] = x.y_; vertices[100] = x.z_;
        vertices[101] = color.r_; vertices[102] = color.g_; vertices[103] = color.b_; vertices[104] = color.a_;

        vertices[105] = position.x_; vertices[106] = position.y_; vertices[107] = position.z_;
        vertices[108] = color.r_; vertices[109] = color.g_; vertices[110] = color.b_; vertices[111] = color.a_;

        color = selectedAxis != RuntimeHandleAxis::YZ ? XColor : SelectionColor;
        vertices[112] = position.x_; vertices[113] = position.y_; vertices[114] = position.z_;
        vertices[115] = color.r_; vertices[116] = color.g_; vertices[117] = color.b_; vertices[118] = color.a_;

        vertices[119] = y.x_; vertices[120] = y.y_; vertices[121] = y.z_;
        vertices[122] = color.r_; vertices[123] = color.g_; vertices[124] = color.b_; vertices[125] = color.a_;

        vertices[126] = y.x_; vertices[127] = y.y_; vertices[128] = y.z_;
        vertices[129] = color.r_; vertices[130] = color.g_; vertices[131] = color.b_; vertices[132] = color.a_;

        vertices[133] = yz.x_; vertices[134] = yz.y_; vertices[135] = yz.z_;
        vertices[136] = color.r_; vertices[137] = color.g_; vertices[138] = color.b_; vertices[139] = color.a_;

        vertices[140] = yz.x_; vertices[141] = yz.y_; vertices[142] = yz.z_;
        vertices[143] = color.r_; vertices[144] = color.g_; vertices[145] = color.b_; vertices[146] = color.a_;

        vertices[147] = z.x_; vertices[148] = z.y_; vertices[149] = z.z_;
        vertices[150] = color.r_; vertices[151] = color.g_; vertices[152] = color.b_; vertices[153] = color.a_;

        vertices[154] = z.x_; vertices[155] = z.y_; vertices[156] = z.z_;
        vertices[157] = color.r_; vertices[158] = color.g_; vertices[159] = color.b_; vertices[160] = color.a_;

        vertices[161] = position.x_; vertices[162] = position.y_; vertices[163] = position.z_;
        vertices[164] = color.r_; vertices[165] = color.g_; vertices[166] = color.b_; vertices[167] = color.a_;

        vb->SetSize(24, Urho3D::MASK_POSITION | Urho3D::MASK_COLOR);
        vb->SetData(vertices);

        graphics_->SetVertexBuffer(vb);

        graphics_->SetDepthTest(Urho3D::CMP_ALWAYS);
        graphics_->Draw(Urho3D::LINE_LIST, 0, 24);

        float quadVertices[126];

        quadVertices[0] = position.x_; quadVertices[1] = position.y_; quadVertices[2] = position.z_;
        quadVertices[3] = YColorTransparent.r_; quadVertices[4] = YColorTransparent.g_; quadVertices[5] = YColorTransparent.b_; quadVertices[6] = YColorTransparent.a_;

        quadVertices[7] = z.x_; quadVertices[8] = z.y_; quadVertices[9] = z.z_;
        quadVertices[10] = YColorTransparent.r_; quadVertices[11] = YColorTransparent.g_; quadVertices[12] = YColorTransparent.b_; quadVertices[13] = YColorTransparent.a_;

        quadVertices[14] = xz.x_; quadVertices[15] = xz.y_; quadVertices[16] = xz.z_;
        quadVertices[17] = YColorTransparent.r_; quadVertices[18] = YColorTransparent.g_; quadVertices[19] = YColorTransparent.b_; quadVertices[20] = YColorTransparent.a_;

        quadVertices[21] = xz.x_; quadVertices[22] = xz.y_; quadVertices[23] = xz.z_;
        quadVertices[24] = YColorTransparent.r_; quadVertices[25] = YColorTransparent.g_; quadVertices[26] = YColorTransparent.b_; quadVertices[27] = YColorTransparent.a_;

        quadVertices[28] = x.x_; quadVertices[29] = x.y_; quadVertices[30] = x.z_;
        quadVertices[31] = YColorTransparent.r_; quadVertices[32] = YColorTransparent.g_; quadVertices[33] = YColorTransparent.b_; quadVertices[34] = YColorTransparent.a_;

        quadVertices[35] = position.x_; quadVertices[36] = position.y_; quadVertices[37] = position.z_;
        quadVertices[38] = YColorTransparent.r_; quadVertices[39] = YColorTransparent.g_; quadVertices[40] = YColorTransparent.b_; quadVertices[41] = YColorTransparent.a_;


        // ////////////////////////////////////////////////////////////////////
        quadVertices[42] = position.x_; quadVertices[43] = position.y_; quadVertices[44] = position.z_;
        quadVertices[45] = ZColorTransparent.r_; quadVertices[46] = ZColorTransparent.g_; quadVertices[47] = ZColorTransparent.b_; quadVertices[48] = ZColorTransparent.a_;

        quadVertices[49] = y.x_; quadVertices[50] = y.y_; quadVertices[51] = y.z_;
        quadVertices[52] = ZColorTransparent.r_; quadVertices[53] = ZColorTransparent.g_; quadVertices[54] = ZColorTransparent.b_; quadVertices[55] = ZColorTransparent.a_;

        quadVertices[56] = xy.x_; quadVertices[57] = xy.y_; quadVertices[58] = xy.z_;
        quadVertices[59] = ZColorTransparent.r_; quadVertices[60] = ZColorTransparent.g_; quadVertices[61] = ZColorTransparent.b_; quadVertices[62] = ZColorTransparent.a_;

        quadVertices[63] = xy.x_; quadVertices[64] = xy.y_; quadVertices[65] = xy.z_;
        quadVertices[66] = ZColorTransparent.r_; quadVertices[67] = ZColorTransparent.g_; quadVertices[68] = ZColorTransparent.b_; quadVertices[69] = ZColorTransparent.a_;

        quadVertices[70] = x.x_; quadVertices[71] = x.y_; quadVertices[72] = x.z_;
        quadVertices[73] = ZColorTransparent.r_; quadVertices[74] = ZColorTransparent.g_; quadVertices[75] = ZColorTransparent.b_; quadVertices[76] = ZColorTransparent.a_;

        quadVertices[77] = position.x_; quadVertices[78] = position.y_; quadVertices[79] = position.z_;
        quadVertices[80] = ZColorTransparent.r_; quadVertices[81] = ZColorTransparent.g_; quadVertices[82] = ZColorTransparent.b_; quadVertices[83] = ZColorTransparent.a_;


        // ///////////////////////////////////////////////////////////////
        quadVertices[84] = position.x_; quadVertices[85] = position.y_; quadVertices[86] = position.z_;
        quadVertices[87] = XColorTransparent.r_; quadVertices[88] = XColorTransparent.g_; quadVertices[89] = XColorTransparent.b_; quadVertices[90] = XColorTransparent.a_;

        quadVertices[91] = y.x_; quadVertices[92] = y.y_; quadVertices[93] = y.z_;
        quadVertices[94] = XColorTransparent.r_; quadVertices[95] = XColorTransparent.g_; quadVertices[96] = XColorTransparent.b_; quadVertices[97] = XColorTransparent.a_;

        quadVertices[98] = yz.x_; quadVertices[99] = yz.y_; quadVertices[100] = yz.z_;
        quadVertices[101] = XColorTransparent.r_; quadVertices[102] = XColorTransparent.g_; quadVertices[103] = XColorTransparent.b_; quadVertices[104] = XColorTransparent.a_;

        quadVertices[105] = yz.x_; quadVertices[106] = yz.y_; quadVertices[107] = yz.z_;
        quadVertices[108] = XColorTransparent.r_; quadVertices[109] = XColorTransparent.g_; quadVertices[110] = XColorTransparent.b_; quadVertices[111] = XColorTransparent.a_;

        quadVertices[112] = z.x_; quadVertices[113] = z.y_; quadVertices[114] = z.z_;
        quadVertices[115] = XColorTransparent.r_; quadVertices[116] = XColorTransparent.g_; quadVertices[117] = XColorTransparent.b_; quadVertices[118] = XColorTransparent.a_;

        quadVertices[119] = position.x_; quadVertices[120] = position.y_; quadVertices[121] = position.z_;
        quadVertices[122] = XColorTransparent.r_; quadVertices[123] = XColorTransparent.g_; quadVertices[124] = XColorTransparent.b_; quadVertices[125] = XColorTransparent.a_;

        vb->SetSize(18, Urho3D::MASK_POSITION | Urho3D::MASK_COLOR);
        vb->SetData(vertices);

        graphics_->SetVertexBuffer(vb);

        graphics_->SetDepthTest(Urho3D::CMP_ALWAYS);
        graphics_->Draw(Urho3D::TRIANGLE_LIST, 0, 18);

    }


    //ShapesMaterial.SetPass(0);
    //Graphics.DrawMeshNow(Arrows, transform);
    if (selectedAxis == RuntimeHandleAxis::X)
    {
        //Graphics.DrawMeshNow(SelectionArrowX, transform);
    }
    else if (selectedAxis == RuntimeHandleAxis::Y)
    {
        //Graphics.DrawMeshNow(SelectionArrowY, transform);
    }
    else if (selectedAxis == RuntimeHandleAxis::Z)
    {
        //Graphics.DrawMeshNow(SelectionArrowZ, transform);
    }
}

void RuntimeHandles::DoRotationHandle(Urho3D::Quaternion rotation, Urho3D::Vector3 position, RuntimeHandleAxis selectedAxis)
{   
    float screenScale = GetScreenScale(position);
    float radius = HandleScale;

    Urho3D::Matrix3x4 xTranform  = Urho3D::Matrix3x4(Urho3D::Vector3::ZERO, rotation * Urho3D::Quaternion(-90, Urho3D::Vector3::UP), Urho3D::Vector3::ONE);
    Urho3D::Matrix3x4 yTranform  = Urho3D::Matrix3x4(Urho3D::Vector3::ZERO, rotation * Urho3D::Quaternion(-90, Urho3D::Vector3::RIGHT), Urho3D::Vector3::ONE);
    Urho3D::Matrix3x4 zTranform  = Urho3D::Matrix3x4(Urho3D::Vector3::ZERO, rotation, Urho3D::Vector3::ONE);
    Urho3D::Matrix3x4 objToWorld = Urho3D::Matrix3x4(position, Urho3D::Quaternion::IDENTITY, screenScale);


    //LinesClipMaterial.SetPass(0);
    //GL.PushMatrix();
    //GL.MultMatrix(objToWorld);

    //GL.Begin(GL.LINES);
    //GL.Color(selectedAxis != RuntimeHandleAxis::X ? XColor : SelectionColor);
    DrawCircle(xTranform, (selectedAxis != RuntimeHandleAxis::X ? XColor : SelectionColor), radius);
    //GL.Color(selectedAxis != RuntimeHandleAxis::Y ? YColor : SelectionColor);
    DrawCircle(yTranform, (selectedAxis != RuntimeHandleAxis::Y ? YColor : SelectionColor), radius);
    //GL.Color(selectedAxis != RuntimeHandleAxis::Z ? ZColor : SelectionColor);
    DrawCircle(zTranform, (selectedAxis != RuntimeHandleAxis::Z ? ZColor : SelectionColor), radius);
    //GL.End();

    //GL.PopMatrix();

    //LinesBillboardMaterial.SetPass(0);
    //GL.PushMatrix();
    //GL.MultMatrix(objToWorld);

    //GL.Begin(GL.LINES);
    //GL.Color(selectedAxis != RuntimeHandleAxis::Free ? AltColor : SelectionColor);
    DrawCircle(Urho3D::Matrix4::IDENTITY, (selectedAxis != RuntimeHandleAxis::Free ? AltColor : SelectionColor), radius);
    //GL.Color(selectedAxis != RuntimeHandleAxis::Screen ? AltColor : SelectionColor);
    DrawCircle(Urho3D::Matrix4::IDENTITY, (selectedAxis != RuntimeHandleAxis::Screen ? AltColor : SelectionColor), radius * 1.1f);
    //GL.End();

    //GL.PopMatrix();
}

void RuntimeHandles::DrawCircle(Urho3D::Matrix3x4 transform, Urho3D::Color color, float radius)
{
    const int pointsPerCircle = 64;
    float angle = 0.0f;
    float z = 0.0f;
    float vertices[896];
    int index = 0;
    Urho3D::VertexBuffer* vb = new Urho3D::VertexBuffer(context_);

    Urho3D::Vector3 prevPoint = transform * Urho3D::Vector3(radius, 0, z);

    for (int i = 0; i < pointsPerCircle; i++)
    {
        //GL.Vertex(prevPoint);
        vertices[index++] = prevPoint.x_; vertices[index++] = prevPoint.y_; vertices[index++] = prevPoint.z_;
        vertices[index++] = color.r_; vertices[index++] = color.g_; vertices[index++] = color.b_; vertices[index++] = color.a_;

        angle += 2 * M_PI / pointsPerCircle;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        Urho3D::Vector3 point = transform * Urho3D::Vector3(x, y, z);
        //GL.Vertex(point);
        vertices[index++] = point.x_; vertices[index++] = point.y_; vertices[index++] = point.z_;
        vertices[index++] = color.r_; vertices[index++] = color.g_; vertices[index++] = color.b_; vertices[index++] = color.a_;

        prevPoint = point;
    }

    vb->SetSize(384, Urho3D::MASK_POSITION | Urho3D::MASK_COLOR);
    vb->SetData(vertices);

    graphics_->SetVertexBuffer(vb);

    graphics_->SetDepthTest(Urho3D::CMP_ALWAYS);
    graphics_->Draw(Urho3D::LINE_LIST, 0, 384);
}

void RuntimeHandles::DoScaleHandle(Urho3D::Vector3 scale, Urho3D::Vector3 position, Urho3D::Quaternion rotation, RuntimeHandleAxis selectedAxis)
{
    float sScale = GetScreenScale(position);
    Urho3D::Vector3 scaleVector = scale * sScale;
    Urho3D::Matrix3x4 linesTransform = Urho3D::Matrix3x4(position, rotation, scaleVector);

    //LinesMaterial.SetPass(0);

    //GL.Begin(GL.LINES);
    DoAxes(position, linesTransform, selectedAxis);
    //GL.End();

    Urho3D::Matrix3x4 rotM = Urho3D::Matrix3x4(Urho3D::Vector3::ONE, rotation, scale);

    //ShapesMaterial.SetPass(0);
    Urho3D::Vector3 screenScale = Urho3D::Vector3(sScale, sScale, sScale);
    Urho3D::Vector3 xOffset = (rotM * Urho3D::Vector3::RIGHT) * sScale * HandleScale;
    Urho3D::Vector3 yOffset = (rotM * Urho3D::Vector3::UP) * sScale * HandleScale;
    Urho3D::Vector3 zOffset = (rotM * Urho3D::Vector3::FORWARD) * sScale * HandleScale;
    if (selectedAxis == RuntimeHandleAxis::X)
    {
        //Graphics.DrawMeshNow(SelectionCube, Urho3D::Matrix4::IDENTITY.Decompose(position + xOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeY, Urho3D::Matrix4::IDENTITY.Decompose(position + yOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeZ, Urho3D::Matrix4::IDENTITY.Decompose(position + zOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeUniform, Urho3D::Matrix4::IDENTITY.Decompose(position, rotation, screenScale * 1.35f));
    }
    else if (selectedAxis == RuntimeHandleAxis::Y)
    {
        //Graphics.DrawMeshNow(CubeX, Urho3D::Matrix4::IDENTITY.Decompose(position + xOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(SelectionCube, Urho3D::Matrix4::IDENTITY.Decompose(position + yOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeZ, Urho3D::Matrix4::IDENTITY.Decompose(position + zOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeUniform, Urho3D::Matrix4::IDENTITY.Decompose(position, rotation, screenScale * 1.35f));
    }
    else if (selectedAxis == RuntimeHandleAxis::Z)
    {
        //Graphics.DrawMeshNow(CubeX, Urho3D::Matrix4::IDENTITY.Decompose(position + xOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeY, Urho3D::Matrix4::IDENTITY.Decompose(position + yOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(SelectionCube, Urho3D::Matrix4::IDENTITY.Decompose(position + zOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeUniform, Urho3D::Matrix4::IDENTITY.Decompose(position, rotation, screenScale * 1.35f));
    }
    else if (selectedAxis == RuntimeHandleAxis::Free)
    {
        //Graphics.DrawMeshNow(CubeX, Urho3D::Matrix4::IDENTITY.Decompose(position + xOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeY, Urho3D::Matrix4::IDENTITY.Decompose(position + yOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeZ, Urho3D::Matrix4::IDENTITY.Decompose(position + zOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(SelectionCube, Urho3D::Matrix4::IDENTITY.Decompose(position, rotation, screenScale * 1.35f));
    }
    else
    {
        //Graphics.DrawMeshNow(CubeX, Urho3D::Matrix4::IDENTITY.Decompose(position + xOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeY, Urho3D::Matrix4::IDENTITY.Decompose(position + yOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeZ, Urho3D::Matrix4::IDENTITY.Decompose(position + zOffset, rotation, screenScale));
        //Graphics.DrawMeshNow(CubeUniform, Urho3D::Matrix4::IDENTITY.Decompose(position, rotation, screenScale * 1.35f));
    }
}

void RuntimeHandles::DoSceneGizmo(Urho3D::Vector3 position, Urho3D::Quaternion rotation, Urho3D::Vector3 selection, float gizmoScale, float xAlpha, float yAlpha, float zAlpha)
{
    float sScale = GetScreenScale(position) * gizmoScale;
    Urho3D::Vector3 screenScale = Urho3D::Vector3(sScale, sScale, sScale);

    const float billboardScale = 0.125f;
    float billboardOffset = 0.4f;
    if (camera_->IsOrthographic())
    {
        billboardOffset = 0.42f;
    }

    const float cubeScale = 0.15f;

    if (selection != Urho3D::Vector3::ZERO)
    {
        if (selection == Urho3D::Vector3::ONE)
        {
            //ShapesMaterialZTestOffset.SetPass(0);
            //Graphics.DrawMeshNow(SceneGizmoSelectedCube, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, (screenScale * cubeScale)));
        }
        else
        {
            if ((xAlpha == 1.0f || xAlpha == 0.0f) &&
                (yAlpha == 1.0f || yAlpha == 0.0f) &&
                (zAlpha == 1.0f || zAlpha == 0.0f))
            {
                //ShapesMaterialZTestOffset.SetPass(0);
                //Graphics.DrawMeshNow(SceneGizmoSelectedAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation * Urho3D::Quaternion.FromLookRotation(selection, Urho3D::Vector3::UP), screenScale));
            }
        }
    }

    //ShapesMaterialZTest.SetPass(0);
    //ShapesMaterialZTest.color = Urho3D::Color::WHITE;
    //Graphics.DrawMeshNow(SceneGizmoCube, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, (screenScale * cubeScale)));
    if (xAlpha == 1.0f && yAlpha == 1.0f && zAlpha == 1.0f)
    {
        //Graphics.DrawMeshNow(SceneGizmoXAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
        //Graphics.DrawMeshNow(SceneGizmoYAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
        //Graphics.DrawMeshNow(SceneGizmoZAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
    }
    else
    {
        if (xAlpha < 1)
        {
            //ShapesMaterialZTest3.SetPass(0);
            //ShapesMaterialZTest3.color = Urho3D::Color(1, 1, 1, yAlpha);
            //Graphics.DrawMeshNow(SceneGizmoYAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
            //ShapesMaterialZTest4.SetPass(0);
            //ShapesMaterialZTest4.color = Urho3D::Color(1, 1, 1, zAlpha);
            //Graphics.DrawMeshNow(SceneGizmoZAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
            //ShapesMaterialZTest2.SetPass(0);
            //ShapesMaterialZTest2.color = Urho3D::Color(1, 1, 1, xAlpha);
            //Graphics.DrawMeshNow(SceneGizmoXAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
            //XMaterial.SetPass(0);

        }
        else if (yAlpha < 1)
        {
            //ShapesMaterialZTest4.SetPass(0);
            //ShapesMaterialZTest4.color = Urho3D::Color(1, 1, 1, zAlpha);
            //Graphics.DrawMeshNow(SceneGizmoZAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
            //ShapesMaterialZTest2.SetPass(0);
            //ShapesMaterialZTest2.color = Urho3D::Color(1, 1, 1, xAlpha);
            //Graphics.DrawMeshNow(SceneGizmoXAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
            //ShapesMaterialZTest3.SetPass(0);
            //ShapesMaterialZTest3.color = Urho3D::Color(1, 1, 1, yAlpha);
            //Graphics.DrawMeshNow(SceneGizmoYAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
        }
        else
        {
            //ShapesMaterialZTest2.SetPass(0);
            //ShapesMaterialZTest2.color = Urho3D::Color(1, 1, 1, xAlpha);
            //Graphics.DrawMeshNow(SceneGizmoXAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
            //ShapesMaterialZTest3.SetPass(0);
            //ShapesMaterialZTest3.color = Urho3D::Color(1, 1, 1, yAlpha);
            //Graphics.DrawMeshNow(SceneGizmoYAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
            //ShapesMaterialZTest4.SetPass(0);
            //ShapesMaterialZTest4.color = Urho3D::Color(1, 1, 1, zAlpha);
            //Graphics.DrawMeshNow(SceneGizmoZAxis, Urho3D::Matrix3x4::IDENTITY.Decompose(position, rotation, screenScale));
        }
    }

    //XMaterial.SetPass(0);
    //XMaterial.color = Urho3D::Color(1, 1, 1, xAlpha);
    DragSceneGizmoAxis(position, rotation, Urho3D::Vector3::RIGHT, gizmoScale, billboardScale, billboardOffset, sScale);

    //YMaterial.SetPass(0);
    //YMaterial.color = Urho3D::Color(1, 1, 1, yAlpha);
    DragSceneGizmoAxis(position, rotation, Urho3D::Vector3::UP, gizmoScale, billboardScale, billboardOffset, sScale);

    //ZMaterial.SetPass(0);
    //ZMaterial.color = Urho3D::Color(1, 1, 1, zAlpha);
    DragSceneGizmoAxis(position, rotation, Urho3D::Vector3::FORWARD, gizmoScale, billboardScale, billboardOffset, sScale);
}

void RuntimeHandles::DragSceneGizmoAxis(Urho3D::Vector3 position, Urho3D::Quaternion rotation, Urho3D::Vector3 axis, float gizmoScale, float billboardScale, float billboardOffset, float sScale)
{
    Urho3D::Vector3 reflectionOffset;
    Urho3D::Plane reflectPlane = Urho3D::Plane(axis, Urho3D::Vector3::ZERO);

    reflectionOffset = reflectPlane.Reflect(camera_->GetNode()->GetDirection()) * 0.1f;
    float dotAxis = camera_->GetNode()->GetDirection().DotProduct(axis); //Camera.current.transform.forward.DotProduct(axis);
    if (dotAxis > 0)
    {
        if(camera_->IsOrthographic())
        {
            reflectionOffset += axis * dotAxis * 0.4f;
        }
        else
        {
            reflectionOffset = axis * dotAxis * 0.7f;
        }

    }
    else
    {
        if (camera_->IsOrthographic())
        {
            reflectionOffset -= axis * dotAxis * 0.1f;
        }
        else
        {
            reflectionOffset = Urho3D::Vector3::ZERO;
        }
    }


    Urho3D::Vector3 pos = position + (axis + reflectionOffset) * billboardOffset * sScale;
    float scale = GetScreenScale(pos) * gizmoScale;
    Urho3D::Vector3 scaleVector = Urho3D::Vector3::ONE * scale;
    //Graphics.DrawMeshNow(SceneGizmoQuad, Urho3D::Matrix3x4::IDENTITY.Decompose(pos, rotation, scaleVector * billboardScale));
}

float RuntimeHandles::GetGridFarPlane()
{
    float h = camera_->GetNode()->GetWorldPosition().y_; //Camera.current.transform.position.y;
    float d = CountOfDigits(h);
    float spacing = pow(10, d - 1);
    return spacing * 150;
}

/* void RuntimeHandles::DrawGrid(Urho3D::Vector3 gridOffset, float camOffset = 0.0f)
{
    float h = camOffset;
    h = abs(h);
    h = fmax(1, h);

    float d = CountOfDigits(h);

    float spacing = pow(10, d - 1);
    float nextSpacing = pow(10, d);
    float nextNextSpacing = pow(10, d + 1);

    float alpha = 1.0f - (h - spacing) / (nextSpacing - spacing);
    float alpha2 = (h * 10 - nextSpacing) / (nextNextSpacing - nextSpacing);

    Urho3D::Vector3 cameraPosition = Camera.current.transform.position;
    DrawGrid(cameraPosition, gridOffset, spacing, alpha, h * 20);
    DrawGrid(cameraPosition, gridOffset, nextSpacing, alpha2, h * 20);
} */

/* void RuntimeHandles::DrawGrid(Urho3D::Vector3 cameraPosition, Urho3D::Vector3 gridOffset, float spacing, float alpha, float fadeDisance)
{
    cameraPosition.y = gridOffset.y;

    gridOffset.y = 0;


    GridMaterial.SetFloat("_FadeDistance", fadeDisance);
    GridMaterial.SetPass(0);

    GL.Begin(GL.LINES);
    GL.Color(Urho3D::Color(1, 1, 1, 0.1f * alpha));

    cameraPosition.x = floor(cameraPosition.x / spacing) * spacing;
    cameraPosition.z = floor(cameraPosition.z / spacing) * spacing;

    for (int i = -150; i < 150; ++i)
    {
        GL.Vertex(gridOffset + cameraPosition + Urho3D::Vector3(i * spacing, 0, -150 * spacing));
        GL.Vertex(gridOffset + cameraPosition + Urho3D::Vector3(i * spacing, 0, 150 * spacing));

        GL.Vertex(gridOffset + cameraPosition + Urho3D::Vector3(-150 * spacing, 0, i * spacing));
        GL.Vertex(gridOffset + cameraPosition + Urho3D::Vector3(150 * spacing, 0, i * spacing));
    }

    GL.End();
} */

/* void RuntimeHandles::DrawBoundRays(Urho3D::BoundingBox& bounds, Urho3D::Vector3 position, Urho3D::Quaternion rotation, Urho3D::Vector3 scale)
{
    LinesMaterialZTest.SetPass(0);

    Urho3D::Matrix4 transform = Urho3D::Matrix4::IDENTITY.Decompose(position, rotation, scale);

    Urho3D::Vector3 center = transform * bounds.Center();
    float sScale = GetScreenScale(center, Camera.current);
    float length = 10 * sScale;

    Urho3D::Vector3 p10 = bounds.Center() + Urho3D::Vector3(bounds.HalfSize().x, -bounds.HalfSize().y, bounds.HalfSize().z);
    Urho3D::Vector3 p11 = bounds.Center() + Urho3D::Vector3(bounds.HalfSize().x, -bounds.HalfSize().y - length, bounds.HalfSize().z);

    Urho3D::Vector3 p20 = bounds.Center() + Urho3D::Vector3(bounds.HalfSize().x, -bounds.HalfSize().y, -bounds.HalfSize().z);
    Urho3D::Vector3 p21 = bounds.Center() + Urho3D::Vector3(bounds.HalfSize().x, -bounds.HalfSize().y - length, -bounds.HalfSize().z);

    Urho3D::Vector3 p30 = bounds.Center() + Urho3D::Vector3(-bounds.HalfSize().x, -bounds.HalfSize().y, bounds.HalfSize().z);
    Urho3D::Vector3 p31 = bounds.Center() + Urho3D::Vector3(-bounds.HalfSize().x, -bounds.HalfSize().y - length, bounds.HalfSize().z);


    GL.PushMatrix();
    GL.MultMatrix(transform);
    GL.Begin(GL.LINES);
    GL.Color(RaysColor);

    int segments = 100;
    Vector3 dp1 = p11 - p10;
    dp1 = dp1  / segments;
    Vector3 dp2 = p21 - p20;
    dp2 = dp2  / segments;
    Vector3 dp3 = p31 - p30;
    dp3 = dp3 / segments;

    for (int i = 0; i < segments; i++)
    {
        p10 += dp1;
        p20 += dp2;
        p30 += dp3;

        GL.Vertex(p10);
        GL.Vertex(p10 + dp1);

        GL.Vertex(p20);
        GL.Vertex(p20 + dp2);

        GL.Vertex(p30);
        GL.Vertex(p30 + dp3);
        p10 += dp1;
        p20 += dp2;
        p30 += dp3;
    }


    GL.End();
    GL.PopMatrix();
}

void RuntimeHandles::DrawBounds(Urho3D::BoundingBox& bounds, Urho3D::Vector3 position, Urho3D::Quaternion rotation, Urho3D::Vector3 scale)
{
    LinesMaterialZTest.SetPass(0);

    Urho3D::Matrix4 transform = Urho3D::Matrix4::IDENTITY.Decompose(position, rotation, scale);

    Vector3 p0 = bounds.Center() + Urho3D::Vector3(-bounds.HalfSize().x, -bounds.HalfSize().y, -bounds.HalfSize().z);
    Vector3 p1 = bounds.Center() + Urho3D::Vector3(-bounds.HalfSize().x, -bounds.HalfSize().y, bounds.HalfSize().z);
    Vector3 p2 = bounds.Center() + Urho3D::Vector3(-bounds.HalfSize().x, bounds.HalfSize().y, -bounds.HalfSize().z);
    Vector3 p3 = bounds.Center() + Urho3D::Vector3(-bounds.HalfSize().x, bounds.HalfSize().y, bounds.HalfSize().z);
    Vector3 p4 = bounds.Center() + Urho3D::Vector3(bounds.HalfSize().x, -bounds.HalfSize().y, -bounds.HalfSize().z);
    Vector3 p5 = bounds.Center() + Urho3D::Vector3(bounds.HalfSize().x, -bounds.HalfSize().y, bounds.HalfSize().z);
    Vector3 p6 = bounds.Center() + Urho3D::Vector3(bounds.HalfSize().x, bounds.HalfSize().y, -bounds.HalfSize().z);
    Vector3 p7 = bounds.Center() + Urho3D::Vector3(bounds.HalfSize().x, bounds.HalfSize().y, bounds.HalfSize().z);

    Urho3D::Vector3 center = transform * bounds.Center();
    float sScale = GetScreenScale(center, Camera.current);

    Urho3D::Vector3 size = Urho3D::Vector3::ONE * 0.2f * sScale;
    Urho3D::Vector3 sizeX = Urho3D::Vector3(fmin(size.x, bounds.HalfSize().x / abs(scale.x)) , 0, 0);
    Urho3D::Vector3 sizeY = Urho3D::Vector3(0, fmin(size.y, bounds.HalfSize().y / abs(scale.y)) , 0);
    Urho3D::Vector3 sizeZ = Urho3D::Vector3(0, 0, fmin(size.z, bounds.HalfSize().z / abs(scale.z)));

    GL.PushMatrix();
    GL.MultMatrix(transform);
    GL.Begin(GL.LINES);
    GL.Color(BoundsColor);

    DrawCorner(p0, sizeX, sizeY, sizeZ, Urho3D::Vector3( 1,  1,  1));
    DrawCorner(p1, sizeX, sizeY, sizeZ, Urho3D::Vector3( 1,  1, -1));
    DrawCorner(p2, sizeX, sizeY, sizeZ, Urho3D::Vector3( 1, -1,  1));
    DrawCorner(p3, sizeX, sizeY, sizeZ, Urho3D::Vector3( 1, -1, -1));
    DrawCorner(p4, sizeX, sizeY, sizeZ, Urho3D::Vector3(-1,  1,  1));
    DrawCorner(p5, sizeX, sizeY, sizeZ, Urho3D::Vector3(-1,  1, -1));
    DrawCorner(p6, sizeX, sizeY, sizeZ, Urho3D::Vector3(-1, -1,  1));
    DrawCorner(p7, sizeX, sizeY, sizeZ, Urho3D::Vector3(-1, -1, -1));

    GL.End();
    GL.PopMatrix();
}

void RuntimeHandles::DrawCorner(Urho3D::Vector3 p, Urho3D::Vector3 sizeX, Urho3D::Vector3 sizeY, Urho3D::Vector3 sizeZ, Urho3D::Vector3 s)
{
    GL.Vertex(p);
    GL.Vertex(p + sizeX * s.x);
    GL.Vertex(p);
    GL.Vertex(p + sizeY * s.y);
    GL.Vertex(p);
    GL.Vertex(p + sizeZ * s.z);
    GL.Vertex(p);
    GL.Vertex(p + sizeX * s.x);
    GL.Vertex(p);
    GL.Vertex(p + sizeY * s.y);
    GL.Vertex(p);
    GL.Vertex(p + sizeZ * s.z);
}*/

float RuntimeHandles::CountOfDigits(float number)
{
    return (number == 0) ? 1.0f : ceil(log10(abs(number) + 0.5f));
}

void RuntimeHandles::SetGraphicsForDrawing(Urho3D::Matrix3x4 transform)
{
    graphics_->SetBlendMode(Urho3D::BLEND_ALPHA);
    graphics_->SetColorWrite(true);
    graphics_->SetCullMode(Urho3D::CULL_NONE);
    graphics_->SetDepthWrite(false);
   // graphics_->SetLineAntiAlias(true);
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    graphics_->SetShaders(vs, ps);
    graphics_->SetShaderParameter(Urho3D::VSP_MODEL, transform);
    graphics_->SetShaderParameter(Urho3D::VSP_VIEW, view_);
    graphics_->SetShaderParameter(Urho3D::VSP_VIEWINV, view_.Inverse());
    graphics_->SetShaderParameter(Urho3D::VSP_VIEWPROJ, projection_ * view_);
    graphics_->SetShaderParameter(Urho3D::PSP_MATDIFFCOLOR, Urho3D::Color(1.0f, 1.0f, 1.0f, 1.0f));
}

Urho3D::Geometry* RuntimeHandles::CombineVertexBuffer(Urho3D::Geometry* geometry1, Urho3D::Geometry* geometry2)
{

}
