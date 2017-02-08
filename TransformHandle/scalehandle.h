#ifndef SCALEHANDLE_H
#define SCALEHANDLE_H


#include "basehandle.h"

#include <vector>

#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Matrix3x4.h>

class ScaleHandle : public BaseHandle
{
public:
    static ScaleHandle* GetCurrent();

private:
    //static void GetCurrent(ScaleHandle* value);
    RuntimeHandleAxis Hit();

protected:
    RuntimeTool GetTool() override;
    float GetCurrentGridUnitSize() override;


public:
    float GridSize = 0.1f;

private:
    static ScaleHandle* m_current;

    Urho3D::Vector3 m_prevPoint;
    Urho3D::Matrix3x4 m_matrix;
    Urho3D::Matrix3x4 m_inverse;

    Urho3D::Vector3 m_roundedScale;
    Urho3D::Vector3 m_scale;
    std::vector<Urho3D::Vector3> m_refScales;
    float m_screenScale;
};

#endif // SCALEHANDLE_H
