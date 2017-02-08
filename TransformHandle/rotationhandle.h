#ifndef ROTATIONHANDLE_H
#define ROTATIONHANDLE_H

#include "basehandle.h"

#include <Urho3D/Math/Quaternion.h>
#include <Urho3D/Math/Matrix3x4.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Ray.h>

class RotationHandle : public BaseHandle
{
public:
    RotationHandle();
    static RotationHandle* GetCurrent();

private:
    static void SetCurrent(RotationHandle* value);
    static Urho3D::Matrix3x4 WorldToCameraMatrix(Urho3D::Camera* camera);

    Urho3D::Quaternion GetStartingRotation();
    Urho3D::Quaternion GetStartingRotationInv();
    void OnPivotRotationChanged();
    bool Intersect(Urho3D::Ray r, Urho3D::Vector3 sphereCenter, float sphereRadius, float& hit1Distance, float& hit2Distance);
    RuntimeHandleAxis Hit();
    RuntimeHandleAxis HitAxis();
    bool HitAxis(Urho3D::Matrix3x4 transform, Urho3D::Matrix3x4 objToWorld, float& minDistance);

protected:
    RuntimeTool GetTool() override;
    float GetCurrentGridUnitSize() override;



public:
    float GridSize = 15.0f;
    float XSpeed = 10.0f;
    float YSpeed = 10.0f;

private:
    static RotationHandle* m_current;

    const float innerRadius = 1.0f;
    const float outerRadius = 1.2f;
    const float hitDot = 0.2f;

    float m_deltaX;
    float m_deltaY;

    Urho3D::Quaternion m_targetRotation = Urho3D::Quaternion::IDENTITY;
    Urho3D::Quaternion m_startingRotation = Urho3D::Quaternion::IDENTITY;
    Urho3D::Quaternion m_startinRotationInv = Urho3D::Quaternion::IDENTITY;

    Urho3D::Quaternion m_targetInverse = Urho3D::Quaternion::IDENTITY;
    Urho3D::Matrix4 m_targetInverseMatrix;
    Urho3D::Vector3 m_startingRotationAxis = Urho3D::Vector3::ZERO;
};

#endif // ROTATIONHANDLE_H
