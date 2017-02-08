#include "scalehandle.h"



ScaleHandle* ScaleHandle::m_current = nullptr;

ScaleHandle* ScaleHandle::GetCurrent()
{
    return m_current;
}

/*void ScaleHandle::GetCurrent(ScaleHandle* value)
{
    m_current = value;
}*/

RuntimeTool ScaleHandle::GetTool()
{
    return RuntimeTool::Scale;
}

float ScaleHandle::GetCurrentGridUnitSize()
{
    return GridSize;
}

/* protected override void AwakeOverride()
{
    Current = this;
    m_scale = Vector3.one;
    m_roundedScale = m_scale;
}

protected override void OnDestroyOverride()
{
    base.OnDestroyOverride();
    if (Current == this)
    {
        Current = null;
    }
}

protected override void UpdateOverride()
{
    base.UpdateOverride();

    if(HightlightOnHover && !IsDragging)
    {
        if (EventSystem.current && EventSystem.current.IsPointerOverGameObject())
        {
            return;
        }
        SelectedAxis = Hit();
    }
}*/

RuntimeHandleAxis ScaleHandle::Hit()
{
    m_screenScale = RuntimeHandles::GetScreenScale(m_position) * RuntimeHandles::HandleScale;
    m_matrix = Urho3D::Matrix3x4(m_position, GetRotation(), Urho3D::Vector3::ONE);
    m_inverse = m_matrix.Inverse();

    Urho3D::Matrix3x4 matrix = Urho3D::Matrix3x4(m_position, GetRotation(), Urho3D::Vector3(m_screenScale, m_screenScale, m_screenScale));

    if (HitCenter())
    {
        return RuntimeHandleAxis::Free;
    }
    float distToYAxis;
    float distToZAxis;
    float distToXAxis;

    bool hit = HitAxis(Urho3D::Vector3::UP, matrix, distToYAxis);
    hit |= HitAxis(Urho3D::Vector3::FORWARD, matrix, distToZAxis);
    hit |= HitAxis(Urho3D::Vector3::RIGHT, matrix, distToXAxis);

    if (hit)
    {
        if (distToYAxis <= distToZAxis && distToYAxis <= distToXAxis)
        {
            return RuntimeHandleAxis::Y;
        }
        else if (distToXAxis <= distToYAxis && distToXAxis <= distToZAxis)
        {
            return RuntimeHandleAxis::X;
        }
        else
        {
            return RuntimeHandleAxis::Z;
        }
    }

    return RuntimeHandleAxis::None;
}

/* protected override bool OnBeginDrag()
{
    SelectedAxis = Hit();

    if(SelectedAxis == RuntimeHandleAxis.Free)
    {
        DragPlane = GetDragPlane();
    }
    else if(SelectedAxis == RuntimeHandleAxis.None)
    {
        return false;
    }

    m_refScales = new Vector3[ActiveTargets.Length];
    for(int i = 0; i < m_refScales.Length; ++i)
    {
        Quaternion rotation = RuntimeTools.PivotRotation == RuntimePivotRotation.Global ? Targets[i].rotation : Quaternion.identity;
        m_refScales[i] = rotation * Target.localScale;
    }
    DragPlane = GetDragPlane();
    bool result = GetPointOnDragPlane(Input.mousePosition, out m_prevPoint);
    if(!result)
    {
        SelectedAxis = RuntimeHandleAxis.None;
    }
    return result;
}

protected override void OnDrag()
{
    Vector3 point;
    if (GetPointOnDragPlane(Input.mousePosition, out point))
    {
        Vector3 offset = m_inverse.MultiplyVector((point - m_prevPoint) / m_screenScale);
        float mag = offset.magnitude;
        if (SelectedAxis == RuntimeHandleAxis.X)
        {
            offset.y = offset.z = 0.0f;
            m_scale.x += Mathf.Sign(offset.x) * mag;
        }
        else if (SelectedAxis == RuntimeHandleAxis.Y)
        {
            offset.x = offset.z = 0.0f;
            m_scale.y += Mathf.Sign(offset.y) * mag;
        }
        else if(SelectedAxis == RuntimeHandleAxis.Z)
        {
            offset.x = offset.y = 0.0f;
            m_scale.z += Mathf.Sign(offset.z) * mag;
        }
        if(SelectedAxis == RuntimeHandleAxis.Free)
        {
            float sign = Mathf.Sign(offset.x + offset.y);
            m_scale.x += sign * mag;
            m_scale.y += sign * mag;
            m_scale.z += sign * mag;
        }

        m_roundedScale = m_scale;

        if(EffectiveGridUnitSize > 0.01)
        {
            m_roundedScale.x = Mathf.RoundToInt(m_roundedScale.x / EffectiveGridUnitSize) * EffectiveGridUnitSize;
            m_roundedScale.y = Mathf.RoundToInt(m_roundedScale.y / EffectiveGridUnitSize) * EffectiveGridUnitSize;
            m_roundedScale.z = Mathf.RoundToInt(m_roundedScale.z / EffectiveGridUnitSize) * EffectiveGridUnitSize;
        }

        for (int i = 0; i < m_refScales.Length; ++i)
        {
            Quaternion rotation =  RuntimeTools.PivotRotation == RuntimePivotRotation.Global ? Targets[i].rotation : Quaternion.identity;

            ActiveTargets[i].localScale = Quaternion.Inverse(rotation) * Vector3.Scale(m_refScales[i], m_roundedScale);
        }

        m_prevPoint = point;
    }
}

protected override void OnDrop()
{
    m_scale = Vector3.one;
    m_roundedScale = m_scale;
}

protected override void DrawOverride()
{
    RuntimeHandles.DoScaleHandle(m_roundedScale, transform.position, Rotation,  SelectedAxis);
} */
