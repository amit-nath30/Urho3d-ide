#include "basehandle.h"

#include <stdlib.h>

BaseHandle::BaseHandle(Urho3D::Graphics *graphics, Urho3D::Input *input, Urho3D::UI *ui):
    graphics(graphics),
    input(input),
    ui(ui)
{

}

/// <summary>
/// current size of grid
/// </summary>
float BaseHandle::GetEffectiveGridUnitSize() const
{
  return m_effectiveGridUnitSize;
}

void BaseHandle::SetEffectiveGridUnitSize(float value)
{
    m_effectiveGridUnitSize = value;
}


std::vector<Urho3D::Node*> BaseHandle::GetActiveTargets() const
{
   return m_activeTargets;
}

std::vector<Urho3D::Node*> BaseHandle::GetTargets() const
{
   return m_targets;
}

void BaseHandle::SetTargets(std::vector<Urho3D::Node*> value)
{
   m_targets = value;
   if(m_targets.empty())
   {
       m_activeTargets.clear();
       return;
   }

   NodeHashSet targetsHS;
   //for (int i = 0; i < m_targets.Length; ++i)
   for(std::vector<Urho3D::Node*>::iterator it = m_targets.begin(); it != m_targets.end(); ++it)
   {
       /*if (m_targets[i] != null && !targetsHS.Contains(m_targets[i]))
       {
           targetsHS.Add(m_targets[i]);
       }*/
       NodeHashSet::iterator containsIterator = targetsHS.find(*it);
       if (*it != NULL && containsIterator == targetsHS.end())
       {
           targetsHS.insert(*it);
       }
   }
   m_targets.assign(targetsHS.begin(), targetsHS.end());
   if (m_targets.empty())
   {
       m_activeTargets = std::vector<Urho3D::Node*>();
       return;
   }
   else if(m_targets.size() == 1)
   {
       m_activeTargets.assign(1, m_targets[0]);
   }

   //for(int i = 0; i < m_targets.Length; ++i)
   for(std::vector<Urho3D::Node*>::iterator it = m_targets.begin(); it != m_targets.end(); ++it)
   {
       Urho3D::Node* target = *it;
       Urho3D::Node* p = target->GetParent();
       while(p != nullptr)
       {
           NodeHashSet::iterator containIterator = targetsHS.find(p);
           if(containIterator != targetsHS.end())
           {
               targetsHS.erase(target);
               break;
           }

           p = p->GetParent();
       }
   }

   m_activeTargets = std::vector<Urho3D::Node*>(targetsHS.begin(), targetsHS.end());
}

Urho3D::Node* BaseHandle::GetTarget() const
{
   if(m_targets.empty())
   {
       return nullptr;
   }
   return m_targets[0];
}

bool BaseHandle::IsDragging()
{
   return m_isDragging;
}

/// <summary>
/// Quaternion Rotation based on selected coordinate system (local or global)
/// </summary>
Urho3D::Quaternion BaseHandle::GetRotation() const
{
   if(m_targets.empty())
   {
       return Urho3D::Quaternion::IDENTITY;
   }

   return RuntimeTools::GetPivotRotation() == RuntimePivotRotation::Local ? GetTarget()->GetRotation() : Urho3D::Quaternion::IDENTITY;
}

RuntimeHandleAxis BaseHandle::GetSelectedAxis()
{
   return m_selectedAxis;
}

void BaseHandle::SetSelectedAxis(RuntimeHandleAxis value)
{
   m_selectedAxis = value;
}

Urho3D::Plane BaseHandle::GetDragPlane()
{
   return m_dragPlane;
}

void BaseHandle::SetDragPlane(Urho3D::Plane value)
{
   m_dragPlane = value;
}

/// Lifecycle methods
/* private void Awake()
{
   if(m_targets != null && m_targets.Length > 0)
   {
       Targets = m_targets;
   }

   AwakeOverride();
}

private void Start()
{
   if (SceneCamera == null)
   {
       SceneCamera = Camera.main;
   }

   if (EnableUndo)
   {
       if (!RuntimeUndoComponent.IsInitialized)
       {
           GameObject runtimeUndo = new GameObject();
           runtimeUndo.name = "RuntimeUndo";
           runtimeUndo.AddComponent<RuntimeUndoComponent>();
       }
   }

   if (GLRenderer.Instance == null)
   {
       GameObject glRenderer = new GameObject();
       glRenderer.name = "GLRenderer";
       glRenderer.AddComponent<GLRenderer>();
   }

   if (SceneCamera != null)
   {
       if (!SceneCamera.GetComponent<GLCamera>())
       {
           SceneCamera.gameObject.AddComponent<GLCamera>();
       }
   }

   if (Targets == null || Targets.Length == 0)
   {
       Targets = new[] { transform };
   }

   if (GLRenderer.Instance != null)
   {
       GLRenderer.Instance.Add(this);
   }

   if (Targets[0].position != transform.position)
   {
       transform.position = Targets[0].position;
   }

   StartOverride();
}

private void OnEnable()
{
   if (GLRenderer.Instance != null)
   {
       GLRenderer.Instance.Add(this);
   }

   OnEnableOverride();
}

private void OnDisable()
{
   if (GLRenderer.Instance != null)
   {
       GLRenderer.Instance.Remove(this);
   }

   OnDisableOverride();
}

private void OnDestroy()
{
   if (GLRenderer.Instance != null)
   {
       GLRenderer.Instance.Remove(this);
   }

   OnDestroyOverride();
}

private void Update()
{
   if (Input.GetMouseButtonDown(0))
   {

       if (RuntimeTools.Current != Tool && RuntimeTools.Current != RuntimeTool.None || RuntimeTools.IsViewing)
       {
           return;
       }

       if (EventSystem.current && EventSystem.current.IsPointerOverGameObject())
       {
           return;
       }


       if (SceneCamera == null)
       {
           Debug.LogError("Camera is null");
           return;
       }

       if (m_draggingHandle != null)
       {
           return;
       }

       if (RuntimeEditorApplication.ActiveSceneCamera != null && !RuntimeEditorApplication.IsPointerOverWindow(RuntimeWindowType.SceneView))
       {
           return;
       }

       m_isDragging = OnBeginDrag();
       if (m_isDragging)
       {
           m_draggingHandle = this;
           if (EnableUndo)
           {
               RuntimeUndo.BeginRecord();
               for (int i = 0; i < m_targets.Length; ++i)
               {
                   RuntimeUndo.RecordTransform(m_targets[i]);
               }
               RuntimeUndo.EndRecord();
           }
       }
   }
   else if (Input.GetMouseButtonUp(0))
   {
       if (m_isDragging)
       {
           OnDrop();
           RuntimeUndo.BeginRecord();
           for (int i = 0; i < m_targets.Length; ++i)
           {
               RuntimeUndo.RecordTransform(m_targets[i]);
           }
           RuntimeUndo.EndRecord();
           m_isDragging = false;
           m_draggingHandle = null;
       }
   }
   else
   {
       if (m_isDragging)
       {
           if (InputController.GetKey(UnitSnapKey) || RuntimeTools.UnitSnapping)
           {
               EffectiveGridUnitSize = CurrentGridUnitSize;
           }
           else
           {
               EffectiveGridUnitSize = 0;
           }

           OnDrag();
       }
   }

   UpdateOverride();
}

/// Lifecycle method overrides
protected virtual void AwakeOverride()
{

}

protected virtual void StartOverride()
{

}

protected virtual void OnEnableOverride()
{

}

protected virtual void OnDisableOverride()
{

}

protected virtual void OnDestroyOverride()
{

}

protected virtual void UpdateOverride()
{
   if (Targets != null && Targets.Length > 0 && Targets[0] != null && Targets[0].position != transform.position)
   {
       if (IsDragging)
       {
           Vector3 offset = transform.position - Targets[0].position;
           for (int i = 0; i < ActiveTargets.Length; ++i)
           {
               if (ActiveTargets[i] != null)
               {
                   ActiveTargets[i].position += offset;
               }
           }
       }
       else
       {

           transform.position = Targets[0].position;
           transform.rotation = Targets[0].rotation;
       }
   }
}

/// Drag And Drop virtual methods
protected virtual bool OnBeginDrag()
{
   return false;
}

protected virtual void OnDrag()
{

}

protected virtual void OnDrop()
{

} */

/// Hit testing methods
bool BaseHandle::HitCenter()
{
   Urho3D::Vector2 screenCenter = EditorCamera->WorldToScreenPoint(m_position);
   Urho3D::IntVector2 mouse = ui->GetCursorPosition();
   Urho3D::Vector2 screenPoint = Urho3D::Vector2(graphics->GetWidth() * mouse.x_, graphics->GetHeight() * mouse.y_);

   return (screenPoint - screenCenter).Length() <= SelectionMargin;
}

bool BaseHandle::HitAxis(Urho3D::Vector3 axis, Urho3D::Matrix3x4 matrix, float& distanceToAxis)
{
   axis = matrix * axis;
   Urho3D::Vector2 screenVectorBegin = EditorCamera->WorldToScreenPoint(m_position);
   Urho3D::Vector2 screenVectorEnd = EditorCamera->WorldToScreenPoint(axis + m_position);

   Urho3D::Vector2 screenVector = screenVectorEnd - screenVectorBegin;
   float screenVectorMag = screenVector.Length();
   screenVector.Normalize();
   if (screenVector != Urho3D::Vector2::ZERO)
   {
       return HitScreenAxis(distanceToAxis, screenVectorBegin, screenVector, screenVectorMag);
   }
   else
   {
       Urho3D::IntVector2 mouse = ui->GetCursorPosition();
       Urho3D::Vector2 screenPoint = Urho3D::Vector2(graphics->GetWidth() * mouse.x_, graphics->GetHeight() * mouse.y_);

       distanceToAxis = (screenVectorBegin - screenPoint).Length();
       bool result = distanceToAxis <= SelectionMargin;
       if (!result)
       {
           distanceToAxis = INFINITY;
       }
       else
       {
           distanceToAxis = 0.0f;
       }
       return result;
   }
}

bool BaseHandle::HitScreenAxis(float& distanceToAxis, Urho3D::Vector2 screenVectorBegin, Urho3D::Vector2 screenVector, float screenVectorMag)
{
   Urho3D::Vector2 perp = PerpendicularClockwise(screenVector).Normalized();
   Urho3D::IntVector2 mouse = ui->GetCursorPosition();
   Urho3D::Vector2 mousePosition = Urho3D::Vector2(graphics->GetWidth() * mouse.x_, graphics->GetHeight() * mouse.y_);
   Urho3D::Vector2 relMousePositon = mousePosition - screenVectorBegin;

   distanceToAxis = abs(perp.DotProduct(relMousePositon));
   Urho3D::Vector2 hitPoint = (relMousePositon - perp * distanceToAxis);
   float vectorSpaceCoord = screenVector.DotProduct(hitPoint);

   bool result = vectorSpaceCoord <= screenVectorMag + SelectionMargin && vectorSpaceCoord >= -SelectionMargin && distanceToAxis <= SelectionMargin;
   if (!result)
   {
       distanceToAxis = INFINITY;
   }
   else
   {
       if (screenVectorMag < SelectionMargin)
       {
           distanceToAxis = 0.0f;
       }
   }
   return result;
}

Urho3D::Plane BaseHandle::GetCurrentDragPlane(Urho3D::Matrix3x4 matrix, Urho3D::Vector3 axis)
{
   Urho3D::Plane plane = Urho3D::Plane((matrix * axis).Normalized (), matrix * Urho3D::Vector3::ZERO);
   return plane;
}

Urho3D::Plane BaseHandle::GetCurrentDragPlane()
{
   //Urho3D::Vector3 toCam = EditorCamera->cameraToWorldMatrix * Urho3D::Vector3::FORWARD; //Camera.transform.position - transform.position;
   Urho3D::Vector3 toCam = Urho3D::Vector3::ZERO;
   Urho3D::Plane dragPlane = Urho3D::Plane(toCam.Normalized(), m_position);
   return dragPlane;
}

bool BaseHandle::GetPointOnDragPlane(Urho3D::Vector3 screenPos, Urho3D::Vector3 &point)
{
   return GetPointOnDragPlane(m_dragPlane, screenPos, point);
}

bool BaseHandle::GetPointOnDragPlane(Urho3D::Plane dragPlane, Urho3D::Vector3 screenPos, Urho3D::Vector3 &point)
{
   Urho3D::Ray ray = EditorCamera->GetScreenRay(screenPos.x_, screenPos.y_);

   float distance = ray.HitDistance(dragPlane);
   if (distance != INFINITY)
   {
       point = ray.direction_ * distance;
       return true;
   }

   point = Urho3D::Vector3::ZERO;
   return false;
}

Urho3D::Vector2 BaseHandle::PerpendicularClockwise(Urho3D::Vector3 vector)
{
   return Urho3D::Vector2(-vector.y_, vector.x_);
}

/* void IGL.Draw()
{
   DrawOverride();
}

protected virtual void DrawOverride()
{

} */

