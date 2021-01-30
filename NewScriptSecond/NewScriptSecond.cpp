
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
	Ptr<ExtrudeFeatures> extrudes = features->extrudeFeatures();
	if (!extrudes) return false;
	Ptr<HoleFeatures> holesFeatures = features->holeFeatures();
	if (!holesFeatures)return false;

	double radiusInternal = 2.225;
	double radiusExternal = 3.2;
	double distanceBackingSeal = 0.975;
	double radiusHole = 0.175;
	double distanceHole = 10.0;


	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint) return false;

	Ptr<Sketch> sketchInternal = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchInternal) return false;
	Ptr<SketchCurves> sketchCurvesInternal = sketchInternal->sketchCurves();
	if (!sketchCurvesInternal) return false;
	Ptr<SketchCircles> sketchCirclesInternal = sketchCurvesInternal->sketchCircles();
	if (!sketchCirclesInternal) return false;
	sketchCirclesInternal->addByCenterRadius(centerPoint, radiusInternal);
	sketchCirclesInternal->addByCenterRadius(centerPoint, radiusExternal);
	Ptr<Profiles> profilesInternal = sketchInternal->profiles();
	if (!profilesInternal) return false;
	Ptr<Profile> profileInternal = profilesInternal->item(1);
	if (!profileInternal) return false;
	Ptr<ExtrudeFeatureInput> extFeatureInternal = extrudes->createInput(profileInternal, FeatureOperations::NewBodyFeatureOperation);
	extFeatureInternal->setDistanceExtent(false, ValueInput::createByReal(distanceBackingSeal));
	extFeatureInternal->isSolid(true);
	Ptr<ExtrudeFeature> extInternal = extrudes->add(extFeatureInternal);
	if (!extInternal) return false;

	//Первое отверстие
	Ptr<Sketch> sketchHole = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchHole) return false;
	Ptr<SketchCurves> sketchCurvesHole = sketchHole->sketchCurves();
	if (!sketchCurvesHole) return false;
	Ptr<SketchCircles> sketchCirclesHole = sketchCurvesHole->sketchCircles();
	if (!sketchCirclesHole) return false;
	sketchCirclesHole->addByCenterRadius(Point3D::create(2.775, 0, 0), radiusHole);
	Ptr<Profiles> profilesHole = sketchHole->profiles();
	if (!profilesHole) return false;
	Ptr<Profile> profileHole = profilesHole->item(0);
	if (!profileHole) return false;
	Ptr<ExtrudeFeatureInput> extFeatureHole = extrudes->createInput(profileHole, FeatureOperations::CutFeatureOperation);
	extFeatureHole->setDistanceExtent(false, ValueInput::createByReal(distanceHole));
	extFeatureHole->isSolid(true);
	Ptr<ExtrudeFeature> extHole = extrudes->add(extFeatureHole);
	if (!extHole) return false;


	//второе отверстие 
	Ptr<Sketch> sketchHoleTwo = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchHoleTwo) return false;
	Ptr<SketchCurves> sketchCurvesHoleTwo = sketchHoleTwo->sketchCurves();
	if (!sketchCurvesHoleTwo) return false;
	Ptr<SketchCircles> sketchCirclesHoleTwo = sketchCurvesHoleTwo->sketchCircles();
	if (!sketchCirclesHoleTwo) return false;
	sketchCirclesHoleTwo->addByCenterRadius(Point3D::create(-2.1993, 1.7001, 0), radiusHole);

	Ptr<Profiles> profilesHoleTwo = sketchHoleTwo->profiles();
	if (!profilesHoleTwo) return false;
	Ptr<Profile> profileHoleTwo = profilesHoleTwo->item(0);
	if (!profileHoleTwo) return false;
	Ptr<ExtrudeFeatureInput> extFeatureHoleTwo = extrudes->createInput(profileHoleTwo, FeatureOperations::CutFeatureOperation);
	extFeatureHoleTwo->setDistanceExtent(false, ValueInput::createByReal(distanceHole));
	extFeatureHoleTwo->isSolid(true);
	Ptr<ExtrudeFeature> extHoleTwo = extrudes->add(extFeatureHoleTwo);
	if (!extHoleTwo) return false;

	//Третье отверстие
	Ptr<Sketch> sketchHoleThree = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchHoleThree) return false;
	Ptr<SketchCurves> sketchCurvesHoleThree = sketchHoleThree->sketchCurves();
	if (!sketchCurvesHoleThree) return false;
	Ptr<SketchCircles> sketchCirclesHoleThree = sketchCurvesHoleThree->sketchCircles();
	if (!sketchCirclesHoleThree) return false;
	sketchCirclesHoleThree->addByCenterRadius(Point3D::create(-2.1993, -1.7001, 0), radiusHole);


	Ptr<Profiles> profilesHoleThree = sketchHoleThree->profiles();
	if (!profilesHoleThree) return false;
	Ptr<Profile> profileHoleThree = profilesHoleThree->item(0);
	if (!profileHoleThree) return false;
	Ptr<ExtrudeFeatureInput> extFeatureHoleThree = extrudes->createInput(profileHoleThree, FeatureOperations::CutFeatureOperation);
	extFeatureHoleThree->setDistanceExtent(false, ValueInput::createByReal(10.0));
	extFeatureHoleThree->isSolid(true);
	Ptr<ExtrudeFeature> extHoleThree = extrudes->add(extFeatureHoleThree);
	if (!extHoleThree) return false;

	Ptr<DataHub> hub = app->data()->activeHub();
	if (!hub) return false;
	Ptr<DataProjects> projects = hub->dataProjects();
	if (!projects) return false;
	Ptr<DataProject> project = nullptr;
	for (Ptr<DataProject>& proj : projects) {
		if (proj->name() == "Кран-робот") {
			project = proj;
			break;
		}
	}
	if (!project) return false;
	Ptr<DataFolder> folder = project->rootFolder();
	if (!folder) return false;
	if (!doc->saveAs("NewScriptSecond", folder, "description", "tag"))
		return false;
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
