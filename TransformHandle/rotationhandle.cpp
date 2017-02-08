#include "rotationhandle.h"



RotationHandle* RotationHandle::m_current = nullptr;

RotationHandle* RotationHandle::GetCurrent()
{
    return m_current;
}

void RotationHandle::SetCurrent(RotationHandle* value)
{
     m_current = value;
}

RuntimeTool RotationHandle::GetTool()
{
    return RuntimeTool::Rotate;
}

Urho3D::Quaternion RotationHandle::GetStartingRotation()
{
    return RuntimeTools::GetPivotRotation() == RuntimePivotRotation::Global ? m_startingRotation : Urho3D::Quaternion::IDENTITY;
}

Urho3D::Quaternion RotationHandle::GetStartingRotationInv()
{
    return RuntimeTools::GetPivotRotation() == RuntimePivotRotation::Global ? m_startinRotationInv : Urho3D::Quaternion::IDENTITY;
}

float RotationHandle::GetCurrentGridUnitSize()
{
    return GridSize;
}

/*protected override void AwakeOverride()
{
    Current = this;
    RuntimeTools.PivotRotationChanged += OnPivotRotationChanged;
}

protected override void OnDestroyOverride()
{
    base.OnDestroyOverride();
    if (Current == this)
    {
        Current = null;
    }
    RuntimeTools.PivotRotationChanged -= OnPivotRotationChanged;
}

protected override void StartOverride()
{
    base.StartOverride();
    OnPivotRotationChanged();
}

protected override void OnEnableOverride()
{
    base.OnEnableOverride();
    OnPivotRotationChanged();
}

protected override void UpdateOverride()
{
    base.UpdateOverride();
    if (EventSystem.current && EventSystem.current.IsPointerOverGameObject())
    {
        return;
    }
    if (!IsDragging)
    {
        if (HightlightOnHover)
        {
            m_targetInverseMatrix = new Urho3D::Matrix4().Decompose(Target.position, Target.rotation * StartingRotationInv, Vector3.one).inverse;
            SelectedAxis = Hit();
        }

        if(m_targetRotation != Target.rotation)
        {
            m_startingRotation = Target.rotation;
            m_startinRotationInv = Quaternion.Inverse(m_startingRotation);
            m_targetRotation = Target.rotation;
        }
    }
}*/

void RotationHandle::OnPivotRotationChanged()
{
    if (GetTarget() != nullptr)
    {
        m_startingRotation = GetTarget()->GetWorldRotation();
        m_startinRotationInv = GetTarget()->GetWorldRotation().Inverse();
        m_targetRotation = GetTarget()->GetWorldRotation();
    }
}

bool RotationHandle::Intersect(Urho3D::Ray r, Urho3D::Vector3 sphereCenter, float sphereRadius, float &hit1Distance, float &hit2Distance)
{
    hit1Distance = 0.0f;
    hit2Distance = 0.0f;

    Urho3D::Vector3 L = sphereCenter - r.origin_;
    float tc = L.DotProduct(r.direction_);
    if (tc < 0.0)
    {
        return false;
    }

    float d2 = L.DotProduct(L) - (tc * tc);
    float radius2 = sphereRadius * sphereRadius;
    if (d2 > radius2)
    {
        return false;
    }

    float t1c = sqrt(radius2 - d2);
    hit1Distance = tc - t1c;
    hit2Distance = tc + t1c;

    return true;
}

RuntimeHandleAxis RotationHandle::Hit()
{
    float hit1Distance;
    float hit2Distance;

    Urho3D::Ray ray = EditorCamera->GetScreenRay(ui->GetCursorPosition().x_, ui->GetCursorPosition().y_);
    float scale = RuntimeHandles::GetScreenScale(GetTarget()->GetWorldPosition()) * RuntimeHandles::HandleScale;
    if (Intersect(ray, GetTarget()->GetWorldPosition(), outerRadius * scale, hit1Distance, hit2Distance))
    {
        Urho3D::Vector3 dpHitPoint;
        GetPointOnDragPlane(GetDragPlane(), Urho3D::Vector2(ui->GetCursorPosition().x_, ui->GetCursorPosition().y_), dpHitPoint);

        RuntimeHandleAxis axis = HitAxis();
        if(axis != RuntimeHandleAxis::None)
        {
            return axis;
        }

        bool isInside = (dpHitPoint - GetTarget()->GetWorldPosition()).Length() <= innerRadius * scale;

        if(isInside)
        {
            return RuntimeHandleAxis::Free;
        }
        else
        {
            return RuntimeHandleAxis::Screen;
        }
    }

    return RuntimeHandleAxis::None;
}

RuntimeHandleAxis RotationHandle::HitAxis()
{
    float screenScale = RuntimeHandles::GetScreenScale(GetTarget()->GetWorldPosition()) * RuntimeHandles::HandleScale;
    Urho3D::Matrix3x4 xTranform = Urho3D::Matrix3x4(Urho3D::Vector3::ZERO, GetTarget()->GetWorldRotation() * GetStartingRotationInv() * Urho3D::Quaternion(-90, Urho3D::Vector3::UP), Urho3D::Vector3::ONE);
    Urho3D::Matrix3x4 yTranform = Urho3D::Matrix3x4(Urho3D::Vector3::ZERO, GetTarget()->GetWorldRotation() * GetStartingRotationInv() * Urho3D::Quaternion(-90, Urho3D::Vector3::RIGHT), Urho3D::Vector3::ONE);
    Urho3D::Matrix3x4 zTranform = Urho3D::Matrix3x4(Urho3D::Vector3::ZERO, GetTarget()->GetWorldRotation() * GetStartingRotationInv(), Urho3D::Vector3::ONE);
    Urho3D::Matrix3x4 objToWorld = Urho3D::Matrix3x4(GetTarget()->GetWorldPosition(), Urho3D::Quaternion::IDENTITY, Urho3D::Vector3(screenScale, screenScale, screenScale));

    float xDistance;
    float yDistance;
    float zDistance;

    bool hitX = HitAxis(xTranform, objToWorld, xDistance);
    bool hitY = HitAxis(yTranform, objToWorld, yDistance);
    bool hitZ = HitAxis(zTranform, objToWorld, zDistance);

    if(hitX && xDistance < yDistance && xDistance < zDistance)
    {
        return RuntimeHandleAxis::X;
    }
    else if(hitY && yDistance < xDistance && yDistance < zDistance)
    {
        return RuntimeHandleAxis::Y;
    }
    else if(hitZ && zDistance < xDistance && zDistance < yDistance)
    {
        return RuntimeHandleAxis::Z;
    }

    return RuntimeHandleAxis::None;
}

bool RotationHandle::HitAxis(Urho3D::Matrix3x4 transform, Urho3D::Matrix3x4 objToWorld, float& minDistance)
{
    bool hit = false;
    minDistance = INFINITY;

    const float radius = 1.0f;
    const int pointsPerCircle = 32;
    float angle = 0.0f;
    float z = 0.0f;

    Urho3D::Vector3 zeroCamPoint = transform * Urho3D::Vector3::ZERO;
    zeroCamPoint = objToWorld * zeroCamPoint;
    zeroCamPoint = WorldToCameraMatrix(EditorCamera) * zeroCamPoint;

    Urho3D::Vector3 prevPoint = transform * Urho3D::Vector3(radius, 0, z);
    prevPoint = objToWorld * prevPoint;
    for (int i = 0; i < pointsPerCircle; i++)
    {
        angle += 2 * M_PI / pointsPerCircle;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        Urho3D::Vector3 point = transform * Urho3D::Vector3(x, y, z);
        point = objToWorld * point;

        Urho3D::Vector3 camPoint = WorldToCameraMatrix(EditorCamera) * point;

        if(camPoint.z_ > zeroCamPoint.z_)
        {
            Urho3D::Vector2 screenVector = EditorCamera->WorldToScreenPoint(point) - EditorCamera->WorldToScreenPoint(prevPoint);
            float screenVectorMag = screenVector.Length();
            screenVector.Normalize();
            if (screenVector != Urho3D::Vector2::ZERO)
            {
                float distance;
                if (HitScreenAxis(distance, EditorCamera->WorldToScreenPoint(prevPoint), screenVector, screenVectorMag))
                {
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        hit = true;
                    }
                }
            }
        }

        prevPoint = point;
    }
    return hit;
}


/* protected override bool OnBeginDrag()
{
    m_targetRotation = Target.rotation;
    m_targetInverseMatrix = new Urho3D::Matrix4().Decompose(Target.position, Target.rotation * StartingRotationInv, Vector3.one).inverse;
    SelectedAxis = Hit();
    m_deltaX = 0.0f;
    m_deltaY = 0.0f;

    if (SelectedAxis == RuntimeHandleAxis.Screen)
    {
        Vector2 center = SceneCamera.WorldToScreenPoint(Target.position);
        Vector2 point = Input.mousePosition;

        float angle = Mathf.Atan2(point.y - center.y, point.x - center.x);
        m_targetInverse = Quaternion.Inverse(new Urho3D::Quaternion(Mathf.Rad2Deg * angle, Vector3.forward));
        m_targetInverseMatrix = new Urho3D::Matrix4().Decompose(Target.position, Target.rotation, Vector3.one).inverse;
    }
    else
    {
        if(SelectedAxis == RuntimeHandleAxis.X)
        {
            m_startingRotationAxis = (Target.rotation * Quaternion.Inverse(StartingRotation)) * Vector3.right;
        }
        else if (SelectedAxis == RuntimeHandleAxis.Y)
        {
            m_startingRotationAxis = (Target.rotation * Quaternion.Inverse(StartingRotation)) * Vector3.up;
        }
        else if (SelectedAxis == RuntimeHandleAxis.Z)
        {
            m_startingRotationAxis = (Target.rotation * Quaternion.Inverse(StartingRotation)) * Vector3.forward;
        }

        m_targetInverse = Quaternion.Inverse(Target.rotation);
    }

    return SelectedAxis != RuntimeHandleAxis.None;
}

protected override void OnDrag()
{
    float deltaX = Input.GetAxis("Mouse X");
    float deltaY = Input.GetAxis("Mouse Y");

    deltaX = deltaX * XSpeed;
    deltaY = deltaY * YSpeed;

    m_deltaX += deltaX;
    m_deltaY += deltaY;


    Vector3 delta = StartingRotation * Quaternion.Inverse(Target.rotation) * SceneCamera.cameraToWorldMatrix.MultiplyVector(new Vector3(m_deltaY, -m_deltaX, 0));
    Quaternion rotation = Quaternion.identity;
    if (SelectedAxis == RuntimeHandleAxis.X)
    {
        Vector3 rotationAxis = Quaternion.Inverse(Target.rotation) * m_startingRotationAxis;

        if (EffectiveGridUnitSize != 0.0f)
        {
            if(Mathf.Abs(delta.x) >= EffectiveGridUnitSize)
            {
                delta.x = Mathf.Sign(delta.x) * EffectiveGridUnitSize;
                m_deltaX = 0.0f;
                m_deltaY = 0.0f;
            }
            else
            {
                delta.x = 0.0f;
            }
        }

        rotation = new Urho3D::Quaternion(delta.x, rotationAxis);
    }
    else if (SelectedAxis == RuntimeHandleAxis.Y)
    {
        Vector3 rotationAxis = Quaternion.Inverse(Target.rotation) * m_startingRotationAxis;

        if (EffectiveGridUnitSize != 0.0f)
        {
            if (Mathf.Abs(delta.y) >= EffectiveGridUnitSize)
            {
                delta.y = Mathf.Sign(delta.y) * EffectiveGridUnitSize;
                m_deltaX = 0.0f;
                m_deltaY = 0.0f;
            }
            else
            {
                delta.y = 0.0f;
            }
        }

        rotation = new Urho3D::Quaternion(delta.y, rotationAxis);

    }
    else if (SelectedAxis == RuntimeHandleAxis.Z)
    {
        Vector3 rotationAxis = Quaternion.Inverse(Target.rotation) * m_startingRotationAxis;

        if (EffectiveGridUnitSize != 0.0f)
        {
            if (Mathf.Abs(delta.z) >= EffectiveGridUnitSize)
            {
                delta.z = Mathf.Sign(delta.z) * EffectiveGridUnitSize;
                m_deltaX = 0.0f;
                m_deltaY = 0.0f;
            }
            else
            {
                delta.z = 0.0f;
            }
        }
        rotation = new Urho3D::Quaternion(delta.z, rotationAxis);

    }
    else if(SelectedAxis == RuntimeHandleAxis.Free)
    {
        delta = StartingRotationInv * delta;
        rotation = Quaternion.Euler(delta.x, delta.y, delta.z);
        m_deltaX = 0.0f;
        m_deltaY = 0.0f;
    }
    else
    {
        delta = m_targetInverse * new Vector3(m_deltaY, -m_deltaX, 0);
        if (EffectiveGridUnitSize != 0.0f)
        {
            if (Mathf.Abs(delta.x) >= EffectiveGridUnitSize)
            {
                delta.x = Mathf.Sign(delta.x) * EffectiveGridUnitSize;
                m_deltaX = 0.0f;
                m_deltaY = 0.0f;
            }
            else
            {
                delta.x = 0.0f;
            }
        }
        Vector3 axis = m_targetInverseMatrix.MultiplyVector(SceneCamera.cameraToWorldMatrix.MultiplyVector(-Vector3.forward));
        rotation = new Urho3D::Quaternion(delta.x, axis);
    }

    if (EffectiveGridUnitSize == 0.0f)
    {
        m_deltaX = 0.0f;
        m_deltaY = 0.0f;
    }


    for (int i = 0; i < ActiveTargets.Length; ++i)
    {
        ActiveTargets[i].rotation *= rotation;
    }
}

protected override void OnDrop()
{
    base.OnDrop();
    m_targetRotation = Target.rotation;
}


protected override void DrawOverride()
{
    RuntimeHandles.DoRotationHandle(Target.rotation * StartingRotationInv, Target.position, SelectedAxis);
}*/

Urho3D::Matrix3x4 RotationHandle::WorldToCameraMatrix(Urho3D::Camera* camera)
{
    Urho3D::Matrix3x4 matrix = Urho3D::Matrix3x4(camera->GetNode()->GetWorldPosition(), camera->GetNode()->GetWorldRotation(), Urho3D::Vector3::ONE);
    matrix = matrix.Inverse();
    matrix.m20_ *= -1.0f;
    matrix.m21_ *= -1.0f;
    matrix.m22_ *= -1.0f;
    matrix.m23_ *= -1.0f;

    return matrix;
}
