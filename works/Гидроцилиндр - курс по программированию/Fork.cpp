
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
	Ptr<ThreadFeatures> threadFeatures = features->threadFeatures();
	if (!threadFeatures)return false;
	Ptr<HoleFeatures> holesFeatures = features->holeFeatures();
	if (!holesFeatures)return false;


	double distanceBase = 9.525; 
	double diameterHole = 3.0; 
	double threadLength = 3.6; 
	double radiusCHInternal = 1.5; 
	double radiusCHExternal = 3.6;
	double distanceHole = 1.6;


	Ptr<Sketch> sketchBase = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchBase) return false;
	Ptr<SketchCurves> sketchCurvesBase = sketchBase->sketchCurves();
	if (!sketchCurvesBase) return false;
	Ptr<SketchLines> sketchLines = sketchCurvesBase->sketchLines();
	if (!sketchLines)
		return false;
	Ptr<SketchArcs> arcs = sketchCurvesBase->sketchArcs();
	if (!arcs)
		return false;
	arcs->addByCenterStartSweep(Point3D::create(-5.7, 0, 0), Point3D::create(-5.7, 3.6,
		0), 3.143);
	sketchLines->addCenterPointRectangle(Point3D::create(0, 0, 0), Point3D::create(5.7, 3.6,
		0));


	Ptr<Profiles> profilesBase = sketchBase->profiles();
	if (!profilesBase) return false;
	auto profilesCollection = ObjectCollection::create();
	profilesCollection->add(profilesBase->item(0));
	profilesCollection->add(profilesBase->item(1));
	Ptr<ExtrudeFeatureInput> extFeatureBase = extrudes->createInput(profilesCollection, FeatureOperations::NewBodyFeatureOperation);
	extFeatureBase->setDistanceExtent(false, ValueInput::createByReal(distanceBase));
	extFeatureBase->isSolid(true);
	Ptr<ExtrudeFeature> extBase = extrudes->add(extFeatureBase);
	if (!extBase) return false;

	Ptr<Sketch> sketchRH = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchRH)
		return false;
	Ptr<SketchCurves> sketchCurvesRH = sketchRH->sketchCurves();
	if (!sketchCurvesRH)
		return false;
	Ptr<SketchLines> sketchLinesRH = sketchCurvesRH->sketchLines();
	if (!sketchLinesRH)
		return false;
	sketchLinesRH->addTwoPointRectangle(Point3D::create(-0.3, -2.857, 3.6),
			Point3D::create(-9.3, -6.667, 3.6));
	if (!sketchLinesRH) return false;

	Ptr<Profiles> profilesRH = sketchRH->profiles();
	if (!profilesRH) return false;
	Ptr<Profile> profileCH = profilesRH->item(0);
	if (!profileCH) return false;
	Ptr<ExtrudeFeatureInput> extFeatureCH = extrudes->createInput(profileCH,
		FeatureOperations::CutFeatureOperation);
	if (!extFeatureCH) return false;
	extFeatureCH->setAllExtent(PositiveExtentDirection);
	Ptr<ExtrudeFeature> extCH = extrudes->add(extFeatureCH);
	if (!extCH) return false;



	Ptr<Sketch> sketchHole = sketches->add(rootComp->yZConstructionPlane());
	if (!sketchHole) return false;
	Ptr<SketchCurves> sketchCurvesHole = sketchHole->sketchCurves();
	if (!sketchCurvesHole) return false;
	Ptr<SketchCircles> sketchCirclesHole = sketchCurvesHole->sketchCircles();
	if (!sketchCirclesHole) return false;
	sketchCirclesHole->addByCenterRadius(Point3D::create(-4.7625, 0, 5.7), radiusCHInternal);
	sketchCirclesHole->addByCenterRadius(Point3D::create(-4.7625, 0, 5.7), radiusCHExternal);
	Ptr<SketchPoints> SketchPoints1 = sketchHole->sketchPoints();
	if (!SketchPoints1)
		return false;
	Ptr<SketchPoint> SketchPoint1 = SketchPoints1->add(Point3D::create(-4.7625, 0, 5.7));
	if (!SketchPoint1)
		return false;

	Ptr<Profiles> profilesHole = sketchHole->profiles();
	if (!profilesHole) return false;
	Ptr<Profile> profileHole = profilesHole->item(1);
	if (!profileHole) return false;
	Ptr<ExtrudeFeatureInput> extFeatureHole = extrudes->createInput(profileHole,
		FeatureOperations::JoinFeatureOperation);
	extFeatureHole->setDistanceExtent(false, ValueInput::createByReal(distanceHole));
	extFeatureHole->isSolid(true);
	Ptr<ExtrudeFeature> extHole = extrudes->add(extFeatureHole);
	if (!extHole) return false;

	Ptr<HoleFeatureInput> holeInput = holesFeatures -> createSimpleInput(ValueInput::createByReal(diameterHole));
	if (!holeInput)
		return false;
	holeInput->setPositionBySketchPoint(SketchPoint1);
	holeInput->setAllExtent(PositiveExtentDirection);
	Ptr<HoleFeature> hole = holesFeatures->add(holeInput);
	if (!hole)
		return false;
	
	Ptr<Sketch> sketchHole2 = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchHole2) return false;
	Ptr<SketchCurves> sketchCurvesHole3 = sketchHole2->sketchCurves();
	if (!sketchCurvesHole3) return false;
	Ptr<SketchPoints> SketchPoints = sketchHole2->sketchPoints();
	if (!SketchPoints)
		return false;
	Ptr<SketchPoint> SketchPoint = SketchPoints->add(Point3D::create(-5.7, 0, 9.525));
	if (!SketchPoint)
		return false;
	
	Ptr<HoleFeatureInput> holeInput1 = holesFeatures -> createSimpleInput(ValueInput::createByReal(diameterHole));
	if (!holeInput1)
		return false;
	holeInput1->setPositionBySketchPoint(SketchPoint);
	holeInput1->setAllExtent(PositiveExtentDirection);
	Ptr<HoleFeature> hole1 = holesFeatures->add(holeInput1);
	if (!hole1)
		return false;
	
	Ptr<ThreadDataQuery> threadDataQuery = threadFeatures->threadDataQuery();
	if (!threadDataQuery) return false;
	Ptr<ThreadInfo> threadInfo = threadFeatures->createThreadInfo(true, "ANSI Metric M Profile", "M30x2", "6H");
	if (!threadInfo) return false;
	Ptr<BRepBodies> bodies1 = rootComp->bRepBodies();
	if (!bodies1) return false;
	Ptr<BRepBody> body1 = bodies1->item(0);
	if (!body1) return false;
	Ptr<BRepFaces> sideFaces = body1->faces();
	if (!sideFaces) return false;
	Ptr<BRepFace> sideface = sideFaces->item(2);
	if (!sideface) return false;
	Ptr<ThreadFeatureInput> threadInput = threadFeatures->createInput(sideface, threadInfo);
	if (!threadInput) return false;
	threadInput->isFullLength(false);
	threadInput->threadLength(ValueInput::createByReal(threadLength));
	Ptr<ThreadFeature> thread = threadFeatures->add(threadInput);
	if (!thread) return false;
	
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
	if (!doc->saveAs("Fork", folder, "description", "tag")) return false;
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
