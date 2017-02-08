#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QWidget>
#include <QMainWindow>

#include "hierarchy.h"
#include "resourcebrowser.h"
#include "console.h"

#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Container/Ptr.h>

#include <Urho3D/UI/Sprite.h>

using namespace Urho3D;

namespace Ui {
class EditorWindow;
}


class EditorWindow : public QMainWindow, public Urho3D::Object
{
    Q_OBJECT
    URHO3D_OBJECT(EditorWindow, Object)

public:
    EditorWindow(Context *context, QWidget *parent = 0);
    ~EditorWindow();
    int Run();
    void CreateScene();

private slots:

    void on_actionAttribute_inspetor_triggered();

    void on_actionResource_browser_triggered();

    void on_actionConsole_triggered();

    void on_actionInspector_triggered();

    // Timeout handler.
    void OnTimeout();

private:
    //Urho3D based class
    //
    Hierarchy *hierechyWindow;
    QDockWidget *inspectorWindow;
    ResourceBrowser *resourceWindow;
    //Console *consoleWindow;

    Engine *engine_;
    Scene *editorScene_;
    bool drawDebug_;

    Node *cameraNode_;

    void CreateSprites();
    void MoveSprites(float timeStep);
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
};

#endif // EDITORWINDOW_H
