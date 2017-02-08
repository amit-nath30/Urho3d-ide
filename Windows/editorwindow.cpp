#include "editorwindow.h"
#include "ui_editorwindow.h"

#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/CustomGeometry.h>

#include <Urho3D/Math/Color.h>

#include <Urho3D/Core/CoreEvents.h>

#include <Urho3D/Resource/ResourceCache.h>

#include <Urho3D/UI/UI.h>

#include <Urho3D/Scene/Node.h>

#include <Urho3D/Container/Ptr.h>

#include <QTimer>


static const StringHash VAR_VELOCITY("Velocity");

EditorWindow::EditorWindow(Context *context, QWidget *parent) :
    QMainWindow(parent),
    Urho3D::Object(context)
{

    Ui::EditorWindow ui;
    ui.setupUi(this);

    //read editor window layout file and restore it


    //starts initializing urho3d variables

    engine_ = new Urho3D::Engine(context);

    QWidget::showMaximized();
}

EditorWindow::~EditorWindow()
{
    //delete ui;
    engine_->DumpResources(true);
}

EditorWindow::Run()
{
    Urho3D::VariantMap engineParameters = Urho3D::VariantMap();
    engineParameters["FrameLimiter"] = false;
    engineParameters["LogName"] = "ParticleEditor2D.log";
    engineParameters["ExternalWindow"] = (void*)(this->centralWidget()->winId());
    engineParameters["Headless"]    = false;
    engineParameters["Sound"] = false;

    if (!engine_->Initialize(engineParameters))
        return -1;

    CreateScene();
    CreateSprites();

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(EditorWindow, HandleUpdate));

    //create qt timer to update engine frame
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(OnTimeout()));
    timer->start(15);

    //OnTimeout();

    return 0;
}

void EditorWindow::CreateScene()
{
    editorScene_ = new Scene(context_);
    editorScene_->CreateComponent<Octree>();
    editorScene_->CreateComponent<DebugRenderer>();

    // Create camera.
    cameraNode_ = editorScene_->CreateChild("Camera");
    Camera *camera = cameraNode_->CreateComponent<Camera>();

    camera->SetFarClip(300.0f);

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 20.0f, 0.0f));
    cameraNode_->SetRotation(Quaternion(90, 0, 0));

    SharedPtr<Viewport> viewport(new Viewport(context_, editorScene_, camera));

    Renderer* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);
}

void EditorWindow::CreateSprites()
{

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    Color gridColor = Color(0.5, 0.5, 0.5, 0.2);

    Node *gridNode = editorScene_->CreateChild("EditorGrid");
    CustomGeometry *grid = gridNode->CreateComponent<CustomGeometry>();
    grid->SetNumGeometries(1);
    grid->SetMaterial(cache->GetResource<Material>("Materials/VColUnlit.xml"));

    grid->BeginGeometry(0, LINE_LIST);

    float lineOffset = 0;
    int numLines = 10;


    for(int i=0; i<=numLines; i++){
        grid->DefineVertex(Vector3(lineOffset, 0.0, numLines));
        grid->DefineColor(gridColor);
        grid->DefineVertex(Vector3(lineOffset, 0.0, -numLines));
        grid->DefineColor(gridColor);

        grid->DefineVertex(Vector3(-numLines, 0.0, lineOffset));
        grid->DefineColor(gridColor);
        grid->DefineVertex(Vector3(numLines, 0.0, lineOffset));
        grid->DefineColor(gridColor);

        if(i > 0){
            grid->DefineVertex(Vector3(-lineOffset, 0.0, numLines));
            grid->DefineColor(gridColor);
            grid->DefineVertex(Vector3(-lineOffset, 0.0, -numLines));
            grid->DefineColor(gridColor);

            grid->DefineVertex(Vector3(-numLines, 0.0, -lineOffset));
            grid->DefineColor(gridColor);
            grid->DefineVertex(Vector3(numLines, 0.0, -lineOffset));
            grid->DefineColor(gridColor);
        }

        lineOffset += 1;
    }

    grid->Commit();

    //creating lights
    // Create a Zone component for ambient lighting & fog control
    Node* zoneNode = editorScene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    //zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    //zone->SetFogStart(100.0f);
    //zone->SetFogEnd(300.0f);

    // Create a directional light to the world. Enable cascaded shadows on it
    Node* lightNode = editorScene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
}

void EditorWindow::OnTimeout()
{
    if (engine_ && !engine_->IsExiting())
        engine_->RunFrame();
}

void EditorWindow::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
   using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move sprites, scale movement with time step
    MoveSprites(timeStep);
}

void EditorWindow::MoveSprites(float timeStep)
{
   /* Graphics* graphics = GetSubsystem<Graphics>();
    float width = (float)graphics->GetWidth();
    float height = (float)graphics->GetHeight();

    // Go through all sprites
    for (unsigned i = 0; i < sprites_.Size(); ++i)
    {
        Sprite* sprite = sprites_[i];

        // Rotate
        float newRot = sprite->GetRotation() + timeStep * 30.0f;
        sprite->SetRotation(newRot);

        // Move, wrap around rendering window edges
        Vector2 newPos = sprite->GetPosition() + sprite->GetVar(VAR_VELOCITY).GetVector2() * timeStep;
        if (newPos.x_ < 0.0f)
            newPos.x_ += width;
        if (newPos.x_ >= width)
            newPos.x_ -= width;
        if (newPos.y_ < 0.0f)
            newPos.y_ += height;
        if (newPos.y_ >= height)
            newPos.y_ -= height;
        sprite->SetPosition(newPos);
    } */
}

void EditorWindow::on_actionAttribute_inspetor_triggered()
{

}

void EditorWindow::on_actionResource_browser_triggered()
{
    resourceWindow = new ResourceBrowser(this);
    addDockWidget(Qt::LeftDockWidgetArea, resourceWindow);
}

void EditorWindow::on_actionConsole_triggered()
{
    //consoleWindow = new Console(this);
    //addDockWidget(Qt::BottomDockWidgetArea, consoleWindow);
}

void EditorWindow::on_actionInspector_triggered()
{

}
