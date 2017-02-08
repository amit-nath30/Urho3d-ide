#ifndef BASEHANDLE_H
#define BASEHANDLE_H

#include "runtimehandles.h"
#include "Infrastructure/runtimetools.h"

#include <vector>
#include <unordered_set>

#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Math/Matrix4.h>
#include <Urho3D/Math/Plane.h>

#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>

#include <Urho3D/Scene/Node.h>

#include <Urho3D/Input/Input.h>

#include <Urho3D/UI/UI.h>

#define M_PI 3.141593f


namespace std
{
  template<>
    struct hash<Urho3D::Node*>
    {
      size_t
      operator()(const Urho3D::Node* obj) const
      {
        return hash<unsigned>()(obj->GetID());
      }
    };
}

struct NodeHasher
{
    size_t
    operator()(const Urho3D::Node* obj) const
    {
        return std::hash<unsigned>()(obj->GetID());
    }
};

struct NodeComparator
{
  bool
  operator()(const Urho3D::Node* obj1, const Urho3D::Node* obj2) const
  {
    if (obj1->GetID() == obj2->GetID())
      return true;
    return false;
  }
};

typedef std::unordered_set<Urho3D::Node*, NodeHasher, NodeComparator> NodeHashSet;

class BaseHandle
{

public:
    BaseHandle(Urho3D::Graphics *graphics, Urho3D::Input *input, Urho3D::UI* ui);
    std::vector<Urho3D::Node*> GetTargets() const;
    void SetTargets(std::vector<Urho3D::Node*> value);
    Urho3D::Node* GetTarget() const;

private:
    void SetEffectiveGridUnitSize(float value);
    static Urho3D::Vector2 PerpendicularClockwise(Urho3D::Vector3 vector);

protected:
    virtual RuntimeTool GetTool() = 0;
    virtual float GetCurrentGridUnitSize() = 0;

    float GetEffectiveGridUnitSize() const;
    std::vector<Urho3D::Node*> GetActiveTargets() const;
    Urho3D::Quaternion GetRotation() const;
    RuntimeHandleAxis GetSelectedAxis();
    void SetSelectedAxis(RuntimeHandleAxis value);
    Urho3D::Plane GetDragPlane();
    void SetDragPlane(Urho3D::Plane value);
    bool HitCenter();
    bool HitAxis(Urho3D::Vector3 axis, Urho3D::Matrix3x4 matrix, float& distanceToAxis);
    bool HitScreenAxis(float& distanceToAxis, Urho3D::Vector2 screenVectorBegin, Urho3D::Vector2 screenVector, float screenVectorMag);
    Urho3D::Plane GetCurrentDragPlane(Urho3D::Matrix3x4 matrix, Urho3D::Vector3 axis);
    Urho3D::Plane GetCurrentDragPlane();
    bool GetPointOnDragPlane(Urho3D::Vector3 screenPos, Urho3D::Vector3 &point);
    bool GetPointOnDragPlane(Urho3D::Plane dragPlane, Urho3D::Vector3 screenPos, Urho3D::Vector3 &point);


public:
    /// <summary>
    /// Use RuntimeUndo subsystem
    /// </summary>
    bool EnableUndo = true;

    /// <summary>
    /// HighlightOnHover
    /// </summary>
    bool HightlightOnHover = true;

    /// <summary>
    /// Key which activates Unit Snapping
    /// </summary>
    int UnitSnapKey = 10; //KeyCode.LeftControl;

    /// <summary>
    /// Raycasting camera
    /// </summary>
    Urho3D::Camera* EditorCamera;

    /// <summary>
    /// Screen space selection margin in pixesl
    /// </summary>
    float SelectionMargin = 10;

    bool IsDragging();

private:
    float m_effectiveGridUnitSize;

    /// <summary>
    /// Target objects which will be affected by handle (for example if m_targets array containes O1 and O2 objects,
    /// and O1 is parent of O2 then m_activeTargets array will contain only O1 object)
    /// </summary>
    std::vector<Urho3D::Node*> m_activeTargets;

    /// <summary>
    /// All Target objects
    /// </summary>
   std::vector<Urho3D::Node*> m_targets;

   /// <summary>
   /// Dragging Handle reference
   /// </summary>
   static BaseHandle* m_draggingHandle;

   /// <summary>
   /// Selected axis
   /// </summary>
   RuntimeHandleAxis m_selectedAxis;

   /// <summary>
   /// Whether drag operation in progress
   /// </summary>
   bool m_isDragging;

   /// <summary>
   /// Drag plane
   /// </summary>
   Urho3D::Plane m_dragPlane;

protected:
   Urho3D::Vector3 m_position;
   Urho3D::Quaternion m_rotation;

   Urho3D::Graphics* graphics;
   Urho3D::Input* input;
   Urho3D::UI* ui;

};
#endif // BASEHANDLE_H
