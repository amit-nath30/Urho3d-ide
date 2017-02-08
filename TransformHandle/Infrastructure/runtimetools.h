#ifndef RUNTIMETOOLS_H
#define RUNTIMETOOLS_H


enum class RuntimeTool
{
    None,
    Move,
    Rotate,
    Scale,
    View,
};

enum class RuntimePivotRotation
{
    Local,
    Global
};

class RuntimeTools
{
public:
    static bool GetIsViewing();
    static void SetIsViewing(bool value);
    static bool GetIsSceneGizmoSelected();
    static void SetIsSceneGizmoSelected(bool value);
    static bool GetShowSelectionGizmos();
    static void SetShowSelectionGizmos(bool value);
    static bool GetAutoFocus();
    static void SetAutoFocus(bool value);
    static bool GetUnitSnapping();
    static void SetUnitSnapping(bool value);
    static bool GetBoundingBoxSnapping();
    static void SetBoundingBoxSnapping(bool value);
    static RuntimeTool GetCurrent();
    static void SetCurrent(RuntimeTool value);
    static RuntimePivotRotation GetPivotRotation();
    static void SetPivotRotation(RuntimePivotRotation value);


private:
    static RuntimeTool m_current;
    static RuntimePivotRotation m_pivotRotation;
    static bool m_isViewing;
    static bool m_isSceneGizmoSelected;
    static bool m_showSelectionGizmos;
    static bool m_autoFocus;
    static bool m_unitSnapping;
    static bool m_boundingBoxSnapping;
    //static GameObject m_spawnPrefab;

};

#endif // RUNTIMETOOLS_H
