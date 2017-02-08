#include "positionhandle.h"




PositionHandle* PositionHandle::m_current = nullptr;


bool PositionHandle::GetIsBoundingBoxSnapping()
{
    return m_isBoundingBoxSnapping || RuntimeTools::GetBoundingBoxSnapping();
}


Urho3D::Vector3 PositionHandle::GetHandlePosition()
{
    return m_position + m_handleOffset;
}

void PositionHandle::SetHandlePosition(Urho3D::Vector3 value)
{
    m_position = value - m_handleOffset;
}

PositionHandle *PositionHandle::GetCurrent()
{
    return m_current;
}

void PositionHandle::SetCurrent(PositionHandle *value)
{
     m_current = value;
}

RuntimeTool PositionHandle::GetTool()
{
    return RuntimeTool::Move;
}

float PositionHandle::GetCurrentGridUnitSize()
{
    return GridSize;
}

/* protected override void AwakeOverride()
{
    Current = this;
}

protected override void OnDestroyOverride()
{
    base.OnDestroyOverride();
    if (Current == this)
    {
        Current = null;
    }
}

protected override void OnEnableOverride()
{
    base.OnEnableOverride();
    m_isBoundingBoxSnapping = false;
    RuntimeTools.BoundingBoxSnapping = false;
    m_handleOffset = Vector3.zero;
    m_targetExposeToEditor = null;
    m_allExposedToEditor = null;

    RuntimeTools.BoundingBoxSnappingChanged += OnBoundingBoxSnappingChanged;
    OnBoundingBoxSnappingChanged();
}

protected override void OnDisableOverride()
{
    base.OnDisableOverride();
    RuntimeTools.BoundingBoxSnapping = false;
    m_targetExposeToEditor = null;
    m_allExposedToEditor = null;

    RuntimeTools.BoundingBoxSnappingChanged -= OnBoundingBoxSnappingChanged;
}

protected override void UpdateOverride()
{
    base.UpdateOverride();

    if (EventSystem.current && EventSystem.current.IsPointerOverGameObject())
    {
        return;
    }

    if (IsDragging)
    {
        if ((SnapToGround || InputController.GetKey(SnapToGroundKey)) && SelectedAxis != RuntimeHandleAxis.Y)
        {
            SnapActiveTargetsToGround(ActiveTargets, SceneCamera, true);
            transform.position = Targets[0].position;
        }
    }

    if (HightlightOnHover && !IsDragging)
    {
        SelectedAxis = Hit();
    }

    if (InputController.GetKeyDown(BoundingBoxSnappingKey))
    {
        m_isBoundingBoxSnapping = true;
        if (InputController.GetKey(BoundingBoxSnappingToogle))
        {
            RuntimeTools.BoundingBoxSnapping = !RuntimeTools.BoundingBoxSnapping;
        }

        BeginSnap();
        m_prevMousePosition = Input.mousePosition;
    }
    else if (InputController.GetKeyUp(BoundingBoxSnappingKey))
    {
        SelectedAxis = RuntimeHandleAxis.None;
        m_isBoundingBoxSnapping = false;
        if (!IsBoundingBoxSnapping)
        {
            m_handleOffset = Vector3.zero;
        }
    }

    if (IsBoundingBoxSnapping)
    {
        Vector2 mousePosition = Input.mousePosition;
        if (IsDragging)
        {
            SelectedAxis = RuntimeHandleAxis.Snap;
            if (m_prevMousePosition != mousePosition)
            {
                m_prevMousePosition = mousePosition;
                float minDistance = float.MaxValue;
                Vector3 minPoint = Vector3.zero;
                bool minPointFound = false;
                for (int i = 0; i < m_allExposedToEditor.Length; ++i)
                {
                    ExposeToEditor exposeToEditor = m_allExposedToEditor[i];
                    Bounds bounds = exposeToEditor.Bounds;
                    m_boundingBoxCorners[0] = bounds.center + new Vector3(bounds.extents.x, bounds.extents.y, bounds.extents.z);
                    m_boundingBoxCorners[1] = bounds.center + new Vector3(bounds.extents.x, bounds.extents.y, -bounds.extents.z);
                    m_boundingBoxCorners[2] = bounds.center + new Vector3(bounds.extents.x, -bounds.extents.y, bounds.extents.z);
                    m_boundingBoxCorners[3] = bounds.center + new Vector3(bounds.extents.x, -bounds.extents.y, -bounds.extents.z);
                    m_boundingBoxCorners[4] = bounds.center + new Vector3(-bounds.extents.x, bounds.extents.y, bounds.extents.z);
                    m_boundingBoxCorners[5] = bounds.center + new Vector3(-bounds.extents.x, bounds.extents.y, -bounds.extents.z);
                    m_boundingBoxCorners[6] = bounds.center + new Vector3(-bounds.extents.x, -bounds.extents.y, bounds.extents.z);
                    m_boundingBoxCorners[7] = bounds.center + new Vector3(-bounds.extents.x, -bounds.extents.y, -bounds.extents.z);
                    GetMinPoint(ref minDistance, ref minPoint, ref minPointFound, exposeToEditor.BoundsObject.transform);
                }

                if (minPointFound)
                {
                    HandlePosition = minPoint;
                }
            }
        }
        else
        {
            SelectedAxis = RuntimeHandleAxis.None;
            if (m_prevMousePosition != mousePosition)
            {
                m_prevMousePosition = mousePosition;

                float minDistance = float.MaxValue;
                Vector3 minPoint = Vector3.zero;
                bool minPointFound = false;
                for (int i = 0; i < m_targetExposeToEditor.Length; ++i)
                {
                    ExposeToEditor exposeToEditor = m_targetExposeToEditor[i];
                    Bounds bounds = exposeToEditor.Bounds;

                    m_boundingBoxCorners[0] = bounds.center + new Vector3(bounds.extents.x, bounds.extents.y, bounds.extents.z);
                    m_boundingBoxCorners[1] = bounds.center + new Vector3(bounds.extents.x, bounds.extents.y, -bounds.extents.z);
                    m_boundingBoxCorners[2] = bounds.center + new Vector3(bounds.extents.x, -bounds.extents.y, bounds.extents.z);
                    m_boundingBoxCorners[3] = bounds.center + new Vector3(bounds.extents.x, -bounds.extents.y, -bounds.extents.z);
                    m_boundingBoxCorners[4] = bounds.center + new Vector3(-bounds.extents.x, bounds.extents.y, bounds.extents.z);
                    m_boundingBoxCorners[5] = bounds.center + new Vector3(-bounds.extents.x, bounds.extents.y, -bounds.extents.z);
                    m_boundingBoxCorners[6] = bounds.center + new Vector3(-bounds.extents.x, -bounds.extents.y, bounds.extents.z);
                    m_boundingBoxCorners[7] = bounds.center + new Vector3(-bounds.extents.x, -bounds.extents.y, -bounds.extents.z);
                    if(Targets[i] != null)
                    {
                        GetMinPoint(ref minDistance, ref minPoint, ref minPointFound, exposeToEditor.BoundsObject.transform);
                    }
                }

                if (minPointFound)
                {
                    m_handleOffset = minPoint - transform.position;
                }
            }
        }
    }
}

protected override void OnDrop()
{
    base.OnDrop();
    if(SnapToGround || InputController.GetKey(SnapToGroundKey))
    {
        SnapActiveTargetsToGround(ActiveTargets, SceneCamera, true);
        transform.position = Targets[0].position;
    }
} */

/*void PositionHandle::SnapActiveTargetsToGround(std::vector<Urho3D::Node*> targets, Urho3D::Camera* camera, bool rotate)
{
    Urho3D::Plane[] planes = GeometryUtility.CalculateFrustumPlanes(camera);
    for (int i = 0; i < targets.Length; ++i)
    {
        Transform activeTarget = targets[i];
        Urho3D::Ray ray = new Ray(activeTarget.position, Urho3D::Vector3::UP);
        bool hitFrustum = false;
        Urho3D::Vector3 topPoint = activeTarget.position;
        for (int j = 0; j < planes.Length; ++j)
        {
            float distance;
            if (planes[j].Raycast(ray, out distance))
            {
                hitFrustum = true;
                topPoint = ray.GetPoint(distance);
            }
        }

        if (!hitFrustum)
        {
            continue;
        }

        ray = new Urho3D::Ray(topPoint, Urho3D::Vector3::DOWN);
        RaycastHit[] hits = Physics.RaycastAll(ray).Where(hit => hit.transform != activeTarget).ToArray();
        if (hits.Length == 0)
        {
            continue;
        }

        float minDistance = float.PositiveInfinity;
        RaycastHit bestHit = hits[0];
        for (int j = 0; j < hits.Length; ++j)
        {
            float mag = (activeTarget.position - hits[j].point).magnitude;
            if (mag < minDistance)
            {
                minDistance = mag;
                bestHit = hits[j];
            }
        }


        activeTarget.position += (bestHit.point - activeTarget.position);
        if (rotate)
        {
            activeTarget.rotation = Quaternion.FromToRotation(activeTarget.up, bestHit.normal) * activeTarget.rotation;
        }
    }
}*/

/* void PositionHandle::OnBoundingBoxSnappingChanged()
{
    if (RuntimeTools::GetBoundingBoxSnapping())
    {
        BeginSnap();
    }
    else
    {
        m_handleOffset = Urho3D::Vector3::ZERO;
    }
} */

/* void PositionHandle::BeginSnap()
{
    if(EditorCamera == nullptr)
    {
        return;
    }
    HashSet<ExposeToEditor> targetExposeToEditorHS = new HashSet<ExposeToEditor>();
    if (Target != null)
    {
        m_targetExposeToEditor = new ExposeToEditor[Targets.Length];

        for (int i = 0; i < Targets.Length; ++i)
        {
            Transform target = Targets[i];
            if (target != null)
            {
                ExposeToEditor exposeToEditor = target.GetComponent<ExposeToEditor>();
                if (exposeToEditor != null)
                {
                    m_targetExposeToEditor[i] = exposeToEditor;
                    targetExposeToEditorHS.Add(exposeToEditor);
                }
            }
        }
    }

    Urho3D::Plane[] frustumPlanes = GeometryUtility.CalculateFrustumPlanes(SceneCamera);
    ExposeToEditor[] exposeToEditorObjects = FindObjectsOfType<ExposeToEditor>();
    List<ExposeToEditor> insideOfFrustum = new List<ExposeToEditor>();
    for (int i = 0; i < exposeToEditorObjects.Length; ++i)
    {
        ExposeToEditor exposeToEditor = exposeToEditorObjects[i];
        if (exposeToEditor.CanSnap)
        {
            if (GeometryUtility.TestPlanesAABB(frustumPlanes, new Bounds(exposeToEditor.transform.TransformPoint(exposeToEditor.Bounds.center), Urho3D::Vector3.zero)))
            {
                if (!targetExposeToEditorHS.Contains(exposeToEditor))
                {
                    insideOfFrustum.Add(exposeToEditor);
                }
            }
        }

    }
    m_allExposedToEditor = insideOfFrustum.ToArray();
} */

void PositionHandle::GetMinPoint(float& minDistance, Urho3D::Vector3& minPoint, bool& minPointFound, Urho3D::Node* tr)
{
    //for (int j = 0; j < m_boundingBoxCorners.Length; ++j)
    for(std::vector<Urho3D::Vector3>::iterator it = m_boundingBoxCorners.begin(); it != m_boundingBoxCorners.end(); ++it)
    {
        Urho3D::Vector3 worldPoint = tr->LocalToWorld(*it); //m_boundingBoxCorners[j]
        Urho3D::Vector2 screenPoint = EditorCamera->WorldToScreenPoint(worldPoint);
        Urho3D::Vector2 mousePoint = Urho3D::Vector2(ui->GetCursorPosition().x_, ui->GetCursorPosition().y_);
        float distance = (screenPoint - mousePoint).Length();
        if (distance < minDistance)
        {
            minPointFound = true;
            minDistance = distance;
            minPoint = worldPoint;
        }
    }
}

bool PositionHandle::HitSnapHandle()
{
    Urho3D::Vector2 sp = EditorCamera->WorldToScreenPoint(GetHandlePosition());
    Urho3D::Vector2 mp = Urho3D::Vector2(ui->GetCursorPosition().x_, ui->GetCursorPosition().y_);

    const float pixelSize = 10;

    return sp.x_ - pixelSize <= mp.x_ && mp.x_ <= sp.x_ + pixelSize  &&
           sp.y_ - pixelSize  <= mp.y_ && mp.y_ <= sp.y_ + pixelSize;
}

bool PositionHandle::HitQuad(Urho3D::Vector3 axis, Urho3D::Matrix3x4 matrix, float size)
{
    Urho3D::Ray ray = EditorCamera->GetScreenRay(ui->GetCursorPosition().x_, ui->GetCursorPosition().y_);
    Urho3D::Plane plane = Urho3D::Plane((matrix * axis).Normalized(), (matrix * Urho3D::Vector3::ZERO));

    float distance = ray.HitDistance(plane);
    if(distance != INFINITY)
    {
        return false;
    }

    Urho3D::Vector3 point = ray.direction_ * distance + ray.origin_;//ray.GetPoint(distance);
    point = matrix.Inverse() * point;

    Urho3D::Vector3 toCam = EditorCamera->GetNode()->GetWorldPosition() - GetHandlePosition();

    float fx = toCam.DotProduct(Urho3D::Vector3::RIGHT) < 0 ? -1 : 1;
    float fy = toCam.DotProduct(Urho3D::Vector3::UP) < 0 ? -1 : 1;
    float fz = toCam.DotProduct(Urho3D::Vector3::FORWARD) < 0 ? -1 : 1;

    point.x_ *= fx;
    point.y_ *= fy;
    point.z_ *= fz;

    float lowBound = -0.01f;

    bool result = point.x_ >= lowBound && point.x_ <= size && point.y_ >= lowBound && point.y_ <= size && point.z_ >= lowBound && point.z_ <= size;

    if(result)
    {
        SetDragPlane( GetCurrentDragPlane(matrix, axis) );
    }

    return result;
}

RuntimeHandleAxis PositionHandle::Hit()
{
    float scale = RuntimeHandles::GetScreenScale(GetHandlePosition());
    const Urho3D::Vector3 scaleVector = Urho3D::Vector3(scale, scale, scale);
    const Urho3D::Vector3 position = GetHandlePosition();
    const Urho3D::Quaternion rotation = GetRotation();

    m_matrix = Urho3D::Matrix3x4(position, rotation, Urho3D::Vector3::ONE);// transform.localScale);
    m_inverse = m_matrix.Inverse();

    Urho3D::Matrix3x4 matrix = Urho3D::Matrix3x4(position, rotation, scaleVector);
    float s = 0.3f * scale;

    if (HitQuad(Urho3D::Vector3::UP * RuntimeHandles::HandleScale, m_matrix, s))
    {
        return RuntimeHandleAxis::XZ;
    }

    if (HitQuad(Urho3D::Vector3::RIGHT * RuntimeHandles::HandleScale, m_matrix, s))
    {
        return RuntimeHandleAxis::YZ;
    }

    if (HitQuad(Urho3D::Vector3::FORWARD * RuntimeHandles::HandleScale, m_matrix, s))
    {
        return RuntimeHandleAxis::XY;
    }

    float distToYAxis;
    float distToZAxis;
    float distToXAxis;
    bool hit = HitAxis(Urho3D::Vector3::UP * RuntimeHandles::HandleScale, matrix, distToYAxis);
    hit |= HitAxis(Urho3D::Vector3::FORWARD * RuntimeHandles::HandleScale, matrix, distToZAxis);
    hit |= HitAxis(Urho3D::Vector3::RIGHT * RuntimeHandles::HandleScale, matrix, distToXAxis);

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

    return  RuntimeHandleAxis::None;
}

/*protected override bool OnBeginDrag()
{
    SelectedAxis = Hit();

    m_currentPosition = HandlePosition;
    m_cursorPosition = HandlePosition;

    if (IsBoundingBoxSnapping)
    {
        return HitSnapHandle();
    }

    if (SelectedAxis == RuntimeHandleAxis.XZ)
    {
        return GetPointOnDragPlane(Input.mousePosition, out m_prevPoint);
    }

    if (SelectedAxis == RuntimeHandleAxis.YZ)
    {
        return GetPointOnDragPlane(Input.mousePosition, out m_prevPoint);
    }

    if (SelectedAxis == RuntimeHandleAxis.XY)
    {
        return GetPointOnDragPlane(Input.mousePosition, out m_prevPoint);
    }

    if (SelectedAxis != RuntimeHandleAxis.None)
    {
        DragPlane = GetDragPlane();
        bool result = GetPointOnDragPlane(Input.mousePosition, out m_prevPoint);
        if(!result)
        {
            SelectedAxis = RuntimeHandleAxis.None;
        }
        return result;
    }

    return false;
}

protected override void OnDrag()
{
    if (IsBoundingBoxSnapping)
    {
        return;
    }

    Vector3 point;
    if (GetPointOnDragPlane(Input.mousePosition, out point))
    {
        Vector3 offset = m_inverse.MultiplyVector(point - m_prevPoint);
        float mag = offset.magnitude;
        if (SelectedAxis == RuntimeHandleAxis.X)
        {
            offset.y = offset.z = 0.0f;
        }
        else if (SelectedAxis == RuntimeHandleAxis.Y)
        {
            offset.x = offset.z = 0.0f;
        }
        else if (SelectedAxis == RuntimeHandleAxis.Z)
        {
            offset.x = offset.y = 0.0f;
        }

        if (EffectiveGridUnitSize == 0.0)
        {
            offset = m_matrix.MultiplyVector(offset).normalized * mag;
            transform.position += offset;
            m_prevPoint = point;
        }
        else
        {
            offset = m_matrix.MultiplyVector(offset).normalized * mag;
            m_cursorPosition += offset;
            Vector3 toCurrentPosition = m_cursorPosition - m_currentPosition;
            Vector3 gridOffset = Vector3.zero;
            if (Mathf.Abs(toCurrentPosition.x * 1.5f) >= EffectiveGridUnitSize)
            {
                gridOffset.x = EffectiveGridUnitSize * Mathf.Sign(toCurrentPosition.x);
            }

            if (Mathf.Abs(toCurrentPosition.y * 1.5f) >= EffectiveGridUnitSize)
            {
                gridOffset.y = EffectiveGridUnitSize * Mathf.Sign(toCurrentPosition.y);
            }


            if (Mathf.Abs(toCurrentPosition.z * 1.5f) >= EffectiveGridUnitSize)
            {
                gridOffset.z = EffectiveGridUnitSize * Mathf.Sign(toCurrentPosition.z);
            }

            m_currentPosition += gridOffset;
            HandlePosition = m_currentPosition;
            m_prevPoint = point;
        }
    }
}

protected override void DrawOverride()
{
    RuntimeHandles.DoPositionHandle(HandlePosition, Rotation, SelectedAxis, IsBoundingBoxSnapping);
} */
