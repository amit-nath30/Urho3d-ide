#include "runtimetools.h"

/* public delegate void RuntimeToolsEvent();
public delegate void SpawnPrefabChanged(GameObject oldPrefab);


public static event RuntimeToolsEvent ToolChanged;
public static event RuntimeToolsEvent PivotRotationChanged;
public static event SpawnPrefabChanged SpawnPrefabChanged;

public static event RuntimeToolsEvent IsViewingChanged;
public static event RuntimeToolsEvent IsSceneGizmoSelectedChanged;
public static event RuntimeToolsEvent ShowSelectionGizmosChanged;
public static event RuntimeToolsEvent AutoFocusChanged;
public static event RuntimeToolsEvent UnitSnappingChanged;
public static event RuntimeToolsEvent BoundingBoxSnappingChanged;*/

RuntimeTool RuntimeTools::m_current = RuntimeTool::None;
RuntimePivotRotation RuntimeTools::m_pivotRotation = RuntimePivotRotation::Local;
bool RuntimeTools::m_isViewing = false;
bool RuntimeTools::m_isSceneGizmoSelected = true;
bool RuntimeTools::m_showSelectionGizmos = false;
bool RuntimeTools::m_autoFocus = false;
bool RuntimeTools::m_unitSnapping = false;
bool RuntimeTools::m_boundingBoxSnapping = false;



bool RuntimeTools::GetIsViewing()
{
    return m_isViewing;
}

void RuntimeTools::SetIsViewing(bool value)
{
    if(m_isViewing != value)
    {
        m_isViewing = value;
        /*if(IsViewingChanged != null)
        {
            IsViewingChanged();
        }*/
    }
}

bool RuntimeTools::GetIsSceneGizmoSelected()
{
    return m_isSceneGizmoSelected;
}

void RuntimeTools::SetIsSceneGizmoSelected(bool value)
{
    if(m_isSceneGizmoSelected != value)
    {
        m_isSceneGizmoSelected = value;
        /*if(IsSceneGizmoSelectedChanged != null)
        {
            IsSceneGizmoSelectedChanged();
        }*/
    }
}

bool RuntimeTools::GetShowSelectionGizmos()
{
    return m_showSelectionGizmos;
}

void RuntimeTools::SetShowSelectionGizmos(bool value)
{
    if(m_showSelectionGizmos != value)
    {
        m_showSelectionGizmos = value;
        /*if(ShowSelectionGizmosChanged != null)
        {
            ShowSelectionGizmosChanged();
        }*/
    }
}


bool RuntimeTools::GetAutoFocus()
{
    return m_autoFocus;
}

void RuntimeTools::SetAutoFocus(bool value)
{
    if(m_autoFocus != value)
    {
        m_autoFocus = value;
        /*if(AutoFocusChanged != null)
        {
            AutoFocusChanged();
        }*/
    }
}


bool RuntimeTools::GetUnitSnapping()
{
    return m_unitSnapping;
}

void RuntimeTools::SetUnitSnapping(bool value)
{
    if(m_unitSnapping != value)
    {
        m_unitSnapping = value;
        /*if(UnitSnappingChanged != null)
        {
            UnitSnappingChanged();
        }*/
    }
}

bool RuntimeTools::GetBoundingBoxSnapping()
{
   return m_boundingBoxSnapping;

}

void RuntimeTools::SetBoundingBoxSnapping(bool value)
{
    if(m_boundingBoxSnapping != value)
    {
        m_boundingBoxSnapping = value;
        /*if(BoundingBoxSnappingChanged != null)
        {
            BoundingBoxSnappingChanged();
        }*/
    }
}

RuntimeTool RuntimeTools::GetCurrent()
{
    return m_current;
}

void RuntimeTools::SetCurrent(RuntimeTool value)
{
    if (m_current != value)
    {
        m_current = value;
        /*if (ToolChanged != null)
        {
            ToolChanged();
        }*/
    }
}

RuntimePivotRotation RuntimeTools::GetPivotRotation()
{
   return m_pivotRotation;
}

void RuntimeTools::SetPivotRotation(RuntimePivotRotation value)
{
    if (m_pivotRotation != value)
    {
        m_pivotRotation = value;
        /*if (PivotRotationChanged != null)
        {
            PivotRotationChanged();
        }*/
    }
}
