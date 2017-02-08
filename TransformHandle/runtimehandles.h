#ifndef RUNTIMEHANDLES_H
#define RUNTIMEHANDLES_H


#include <Urho3D/Math/Color.h>
#include <Urho3D/Math/Quaternion.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Matrix4.h>
#include <Urho3D/Math/Matrix3x4.h>
#include <Urho3D/Math/BoundingBox.h>
#include <Urho3D/Math/Frustum.h>

#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/ShaderVariation.h>

#include <Urho3D/Scene/Node.h>

#include <Urho3D/Core/Context.h>

#define M_PI 3.141593f
#define DEG_2_RAD 0.01745329
#define SIGN(X) X<0 ? -1:1

enum class RuntimeHandleAxis
{
    None,
    X,
    Y,
    Z,
    XY,
    XZ,
    YZ,
    Screen,
    Free,
    Snap,
};


class RuntimeHandles
{
public:
   static void Initialize(Urho3D::Context* context, Urho3D::Graphics* graphics, Urho3D::Camera *camera);
   static Urho3D::Geometry* CreateCubeMesh(Urho3D::Color color, Urho3D::Vector3 center, float scale, float cubeLength = 1, float cubeWidth = 1, float cubeHeight = 1);
   static float GetScreenScale(Urho3D::Vector3 position);
   static void DoPositionHandle(Urho3D::Vector3 position, Urho3D::Quaternion rotation, RuntimeHandleAxis selectedAxis = RuntimeHandleAxis::None, bool snapMode = false);
   static void DoRotationHandle(Urho3D::Quaternion rotation, Urho3D::Vector3 position, RuntimeHandleAxis selectedAxis = RuntimeHandleAxis::None);
   static void DoScaleHandle(Urho3D::Vector3 scale, Urho3D::Vector3 position, Urho3D::Quaternion rotation, RuntimeHandleAxis selectedAxis = RuntimeHandleAxis::None);
   static void DoSceneGizmo(Urho3D::Vector3 position, Urho3D::Quaternion rotation, Urho3D::Vector3 selection, float gizmoScale, float xAlpha = 1.0f, float yAlpha = 1.0f, float zAlpha = 1.0f);
   static float GetGridFarPlane();
   //static void DrawGrid(Urho3D::Vector3 gridOffset, float camOffset = 0.0f);
   //static void DrawBoundRays(Urho3D::BoundingBox& bounds, Urho3D::Vector3 position, Urho3D::Quaternion rotation, Urho3D::Vector3 scale);
   //static void DrawBounds(Urho3D::BoundingBox& bounds, Urho3D::Vector3 position, Urho3D::Quaternion rotation, Urho3D::Vector3 scale);
   static float CountOfDigits(float number);

private:
    static Urho3D::Geometry* CreateQuadMesh(float quadWidth = 1, float cubeHeight = 1);
    static Urho3D::Geometry* CreateConeMesh(Urho3D::Color color, Urho3D::Matrix3x4 transform, float scale);
    static Urho3D::Geometry* CreateSceneGizmoHalfAxis(Urho3D::Color color, Urho3D::Quaternion rotation);
    static Urho3D::Geometry* CreateSceneGizmoAxis(Urho3D::Color axisColor, Urho3D::Color altColor, Urho3D::Quaternion rotation);
    static void DoAxes(Urho3D::Vector3 position, Urho3D::Matrix3x4 transform, RuntimeHandleAxis selectedAxis);
    static void DrawCircle(Urho3D::Matrix3x4 transform, Urho3D::Color color, float radius);
    static void DragSceneGizmoAxis(Urho3D::Vector3 position, Urho3D::Quaternion rotation, Urho3D::Vector3 axis, float gizmoScale, float billboardScale, float billboardOffset, float sScale);
    //static void DrawGrid(Urho3D::Vector3 cameraPosition, Urho3D::Vector3 gridOffset, float spacing, float alpha, float fadeDisance);
    //static void DrawCorner(Urho3D::Vector3 p, Urho3D::Vector3 sizeX, Urho3D::Vector3 sizeY, Urho3D::Vector3 sizeZ, Urho3D::Vector3 s);
    static void SetGraphicsForDrawing(Urho3D::Matrix3x4 transform = Urho3D::Matrix3x4::IDENTITY);
    static Urho3D::Geometry* CombineVertexBuffer(Urho3D::Geometry* geometry1, Urho3D::Geometry* geometry2);

public:
    static constexpr float HandleScale = 1.0f;
    static Urho3D::Color XColor;
    static Urho3D::Color XColorTransparent;
    static Urho3D::Color YColor;
    static Urho3D::Color YColorTransparent;
    static Urho3D::Color ZColor;
    static Urho3D::Color ZColorTransparent;
    static Urho3D::Color AltColor;
    static Urho3D::Color SelectionColor;
    static Urho3D::Color BoundsColor;
    static Urho3D::Color RaysColor;

private:
    static Urho3D::Context* context_;
    static Urho3D::Camera* camera_;
    static Urho3D::Graphics* graphics_;

    static Urho3D::Matrix3x4 view_;
    static Urho3D::Matrix4 projection_;

    static Urho3D::ShaderVariation* vs;
    static Urho3D::ShaderVariation* ps;

    static Urho3D::Geometry* Arrows;
    static Urho3D::Geometry* SelectionArrowY;
    static Urho3D::Geometry* SelectionArrowX;
    static Urho3D::Geometry* SelectionArrowZ;

    static Urho3D::Geometry* SelectionCube;
    static Urho3D::Geometry* CubeX;
    static Urho3D::Geometry* CubeY;
    static Urho3D::Geometry* CubeZ;
    static Urho3D::Geometry* CubeUniform;

    static Urho3D::Geometry* SceneGizmoSelectedAxis;
    static Urho3D::Geometry* SceneGizmoXAxis;
    static Urho3D::Geometry* SceneGizmoYAxis;
    static Urho3D::Geometry* SceneGizmoZAxis;
    static Urho3D::Geometry* SceneGizmoCube;
    static Urho3D::Geometry* SceneGizmoSelectedCube;
    static Urho3D::Geometry* SceneGizmoQuad;

    static Urho3D::Material ShapesMaterialZTest;
    static Urho3D::Material ShapesMaterialZTest2;
    static Urho3D::Material ShapesMaterialZTest3;
    static Urho3D::Material ShapesMaterialZTest4;
    static Urho3D::Material ShapesMaterialZTestOffset;
    static Urho3D::Material ShapesMaterial;
    static Urho3D::Material LinesMaterial;
    static Urho3D::Material LinesMaterialZTest;
    static Urho3D::Material LinesClipMaterial;
    static Urho3D::Material LinesBillboardMaterial;
    static Urho3D::Material XMaterial;
    static Urho3D::Material YMaterial;
    static Urho3D::Material ZMaterial;
    static Urho3D::Material GridMaterial;
};

#endif // RUNTIMEHANDLES_H
