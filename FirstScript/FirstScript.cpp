
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
	Ptr<FilletFeatures> fillets = features->filletFeatures();
	if (!fillets) return false;
	Ptr<RectangularPatternFeatures> rectangularPatterns = features->rectangularPatternFeatures();
	if (!rectangularPatterns) return false;
	
	double radiusSmall = 2;
	double radiusBig = 1.5;
	double distanceExtrude = 0.7; 
	double distanceExtrudeSmall = 0.5;

	//меньшая окружность
	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint) return false;
	Ptr<Sketch> sketchInternal = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchInternal) return false;
	Ptr<SketchCurves> sketchCurvesInternal = sketchInternal->sketchCurves();
	if (!sketchCurvesInternal) return false;
	Ptr<SketchCircles> sketchCirclesInternal = sketchCurvesInternal->sketchCircles();
	if (!sketchCirclesInternal) return false;
	sketchCirclesInternal->addByCenterRadius(centerPoint, radiusBig); 
	
	//выдавливание
	Ptr<Profiles> profilesInternal = sketchInternal->profiles();
	if (!profilesInternal) return false;
	Ptr<Profile> profileInternal = profilesInternal->item(0); 
	if (!profileInternal) return false;
	Ptr<ExtrudeFeatureInput> extFeature1 = extrudes->createInput(profileInternal, FeatureOperations::NewBodyFeatureOperation);
	extFeature1->setDistanceExtent(false, ValueInput::createByReal(distanceExtrudeSmall)); 
	extFeature1->isSolid(true);
	Ptr<ExtrudeFeature> extInternal = extrudes->add(extFeature1);
	if (!extInternal) return false;


	Ptr<Point3D> newPoint = Point3D::create(0, 0, -0.5);
	if (!newPoint) return false;
	Ptr<Sketch> sketchInternalNew = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchInternalNew) return false;
	Ptr<SketchCurves> sketchCurvesInternalNew = sketchInternalNew->sketchCurves();
	if (!sketchCurvesInternalNew) return false;
	Ptr<SketchCircles> sketchCirclesInternalNew = sketchCurvesInternal->sketchCircles();
	if (!sketchCirclesInternalNew) return false;
	sketchCirclesInternalNew->addByCenterRadius(newPoint, radiusSmall);


	Ptr<Profiles> profilesInternalNew = sketchInternalNew->profiles();
	if (!profilesInternalNew) return false;
	Ptr<Profile> profileInternalNew = profilesInternalNew->item(0);
	if (!profileInternalNew) return false;
	Ptr<ExtrudeFeatureInput> extFeature2 = extrudes->createInput(profileInternalNew, FeatureOperations::JoinFeatureOperation);
	extFeature2->setDistanceExtent(false, ValueInput::createByReal(distanceExtrudeSmall));
	extFeature2->isSolid(true);
	Ptr<ExtrudeFeature> extInternal1 = extrudes->add(extFeature2);
	if (!extInternal1) return false;

	Ptr<DataHub> hub = app->data()->activeHub();
	if (!hub) return false;
	Ptr<DataProjects> projects = hub->dataProjects();
	if (!projects) return false;
	Ptr<DataProject> project = nullptr;
	for (Ptr<DataProject>& proj : projects) {
		if (proj->name() == "Fusion 360 для школьников") {
			project = proj;
			break;
		}
	}
	if (!project) return false;
	Ptr<DataFolder> folder = project->rootFolder();
	if (!folder) return false;
	if (!doc->saveAs("NewBody", folder, "description", "tag")) return false;
	
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
