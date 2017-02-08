#ifndef POSITIONHANDLE_H
#define POSITIONHANDLE_H

#include "basehandle.h"

#include <vector>

#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Matrix3x4.h>

#include <Urho3D/Scene/Node.h>

#include <Urho3D/Graphics/Camera.h>


enum class SnapMode
{
    BoundingBox,
    Vertex,
};

class PositionHandle : public BaseHandle
{
public:
    PositionHandle();
    static PositionHandle* GetCurrent();

private:
    static void SetCurrent(PositionHandle* value);
    //static void SnapActiveTargetsToGround(std::vector<Urho3D::Node*> targets, Urho3D::Camera* camera,  bool rotate);

    bool GetIsBoundingBoxSnapping();
    Urho3D::Vector3 GetHandlePosition();
    void SetHandlePosition(Urho3D::Vector3 value);
    //void OnBoundingBoxSnappingChanged();
    //void BeginSnap();
    void GetMinPoint(float& minDistance, Urho3D::Vector3& minPoint, bool& minPointFound, Urho3D::Node* tr);
    bool HitSnapHandle();
    bool HitQuad(Urho3D::Vector3 axis, Urho3D::Matrix3x4 matrix, float size);
    RuntimeHandleAxis Hit();

protected:
    RuntimeTool GetTool() override;
    float GetCurrentGridUnitSize() override;


public:
    float GridSize = 1.0f;
    bool SnapToGround;
    int SnapToGroundKey = 1; //KeyCode.G;
    int BoundingBoxSnappingKey = 2; //KeyCode.V;
    int BoundingBoxSnappingToogle = 3; //KeyCode.LeftShift;


private:
    static PositionHandle* m_current;
    Urho3D::Vector3 m_cursorPosition;
    Urho3D::Vector3 m_currentPosition;
    Urho3D::Vector3 m_prevPoint;
    Urho3D::Matrix3x4 m_matrix;
    Urho3D::Matrix3x4 m_inverse;
    Urho3D::Vector2 m_prevMousePosition;
    //ExposeToEditor[] m_targetExposeToEditor;
    //ExposeToEditor[] m_allExposedToEditor;
    SnapMode SnapMode;
    bool m_isBoundingBoxSnapping = false;
    std::vector<Urho3D::Vector3> m_boundingBoxCorners;
    Urho3D::Vector3 m_handleOffset;

};

#endif // POSITIONHANDLE_H
