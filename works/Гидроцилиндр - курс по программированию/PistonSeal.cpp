
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
	if (!rootComp) return false;

	Ptr<Sketches> sketches = rootComp->sketches();
	if (!sketches) return false;

	Ptr<RevolveFeatures> revolves = features->revolveFeatures();
	if (!revolves) return false;

	double angle = 180.0;

	Ptr<Sketch> sketch = sketches->add(rootComp->xYConstructionPlane());
	if (!sketch) return false;

	Ptr<SketchCurves> sketchCurves = sketch->sketchCurves();
	if (!sketchCurves) return false;

	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines) return false;

	Ptr<SketchArcs> arcs = sketchCurves->sketchArcs();
	if (!arcs) return false;

	Ptr<SketchLine> lines = sketchLines->addByTwoPoints(Point3D::create(-0.2, 0.6, 0), Point3D::create(0.2, 0.6, 0));
	if (!lines) return false;
	Ptr<SketchLine> lines1 = sketchLines->addByTwoPoints(Point3D::create(0.2, 0.6, 0), Point3D::create(0.4, -0.6, 0));
	if (!lines1) return false;
	Ptr<SketchLine> lines2 = sketchLines->addByTwoPoints(Point3D::create(-0.2, 0.6, 0), Point3D::create(-0.4, -0.6, 0));
	if (!lines2) return false;
	Ptr<SketchLine> lines3 = sketchLines->addByTwoPoints(Point3D::create(0.1, -0.6, 0), Point3D::create(0.4, -0.6, 0));
	if (!lines3) return false;
	Ptr<SketchLine> lines4 = sketchLines->addByTwoPoints(Point3D::create(-0.4, -0.6, 0), Point3D::create(-0.1, -0.6, 0));
	if (!lines4) return false;
	Ptr<SketchLine> lines5 = sketchLines->addByTwoPoints(Point3D::create(0.1, -0.6, 0), Point3D::create(0.0162, -0.0973, 0));
	if (!lines5) return false;
	Ptr<SketchLine> lines6 = sketchLines->addByTwoPoints(Point3D::create(-0.1, -0.6, 0), Point3D::create(-0.0162, -0.0973, 0));
	if (!lines6) return false;
	Ptr<SketchLine> lines7 = sketchLines->addByTwoPoints(Point3D::create(-6.8, 2.6914, 0), Point3D::create(-6.8, 0, 0));
	if (!lines7) return false;

	Ptr<SketchArc> arc = arcs->addByThreePoints(Point3D::create(-0.0162, -0.0973, 0), Point3D::create(0, -0.0836, 0), Point3D::create(0.0162, -0.0973, 0));
	if (!arc) return false;

	Ptr<Profiles> profiles = sketch->profiles();
	if (!profiles) return false;
	Ptr<Profile> profile = profiles->item(0);
	if (!profile) return false;
	Ptr<RevolveFeatureInput> revInput = revolves->createInput(profile, lines7, FeatureOperations::NewBodyFeatureOperation);
	if (!revInput) return false;
	revInput->setAngleExtent(false, ValueInput::createByReal(angle));
	revInput->isSolid(true);

	Ptr<RevolveFeature> rev = revolves->add(revInput);
	if (!rev) return false;

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
	if (!doc->saveAs("Piston Seal", folder, "description", "tag")) return false;

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
