
#include <Core/CoreAll.h>
#include <Fusion/FusionAll.h>
#include <CAM/CAMAll.h>

using namespace adsk::core;
using namespace adsk::fusion;
using namespace adsk::cam;

Ptr<Application> app;
Ptr<UserInterface> ui;

extern "C" XI_EXPORT bool run(const char* context)
{
	app = Application::get();
	if (!app)
		return false;

	ui = app->userInterface();
	if (!ui)
		return false;

	Ptr<Documents> docs = app->documents();
	if (!docs) return false;
	Ptr<Document> doc = docs->add(DocumentTypes::FusionDesignDocumentType);
	if (!doc) return false;

	Ptr<Design> design = app->activeProduct();
	if (!design) return false;
	Ptr<Component> rootComp = design->rootComponent();
	if (!rootComp) return false;
	Ptr<Features> features = rootComp->features();
	if (!features) return false;
	Ptr<Sketches> sketches = rootComp->sketches();
	if (!sketches) return false;


	Ptr<CommandDefinitions> commandDefinitions = ui->commandDefinitions();
	if (!commandDefinitions) return nullptr;

	double radiusInternal = 3.0;
	double radiusExternal = 3.2;

	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);

	Ptr<Sketch> sketchInternal = sketches->add(rootComp->xYConstructionPlane());
	if (!centerPoint) return false;

	Ptr<SketchCurves> sketchCurvesInternal = sketchInternal->sketchCurves();
	if (!sketchCurvesInternal) return false;

	Ptr<SketchCircles> sketchCircelsInternal = sketchCurvesInternal->sketchCircles();
	if (!sketchCircelsInternal) return false;

	sketchCircelsInternal->addByCenterRadius(centerPoint, radiusInternal);
	sketchCircelsInternal->addByCenterRadius(centerPoint, radiusExternal);

	Ptr<CommandDefinition> extrudeCmd = commandDefinitions->itemById("Extrude");
	if (!extrudeCmd) {
		extrudeCmd = commandDefinitions->addButtonDefinition("Extrude", "Command Inputs Sample", "Sample to demonstrate varios command inputs");
		
	}
	extrudeCmd->execute();
	adsk::autoTerminate(true);

	Ptr<DataHub> hub = app->data()->activeHub();
	if (!hub) return false;
	Ptr<DataProjects> projects = hub->dataProjects();
	if (!projects) return false;
	Ptr<DataProject> project = nullptr;
	for (Ptr<DataProject>& proj : projects) {
		if (proj->name() == "Hydraulic Cylinder") {
			project = proj;
			break;
		}
	}

	if (!project) return false;
	Ptr<DataFolder> folder = project->rootFolder();
	if (!folder) return false; 
	if (!doc->saveAs("Rod Guide Seal", folder, "description", "tag")) return false;


	return true;
}

#ifdef XI_WIN

#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif // XI_WIN
