
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
	if (!threadFeatures) return false;

	Ptr<HoleFeatures> holesFeatures = features->holeFeatures();
	if (!holesFeatures)
		return false;


	double radiusCylinder = 3.25;
	double distanceCylinder = 4.2;
	double threadLength = 2.5;
	double distanceoffsetPlanes = 1.7;
	double radiusSlotInternal = 3.0;
	double radiusSlotExternal = 3.25;
	double distanceSlot = -0.3;
	double distancePolygon = 1.4;
	double diameterHole = 4.2;

	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint) return false;

	Ptr<Sketch> sketchCylinder = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchCylinder)
		return false;

	Ptr<SketchCurves> sketchCurvesCylinder = sketchCylinder->sketchCurves();
	if (!sketchCurvesCylinder)
		return false;

	Ptr<SketchCircles> sketchCircles = sketchCurvesCylinder->sketchCircles();
	if (!sketchCircles)
		return false;

	sketchCircles->addByCenterRadius(centerPoint, radiusCylinder);

	Ptr<Profiles> profilesCylinder = sketchCylinder->profiles();
	if (!profilesCylinder)
		return false;

	Ptr<Profile> profileCylinder = profilesCylinder->item(0);
	if (!profileCylinder)
		return false;

	Ptr<ExtrudeFeatureInput> extrudeCylinder = extrudes->createInput(profileCylinder, NewBodyFeatureOperation);
	if (!extrudeCylinder)
		return false;

	extrudeCylinder->setDistanceExtent(false, ValueInput::createByReal(distanceCylinder));

	extrudeCylinder->isSolid(true);

	Ptr<ExtrudeFeature> extCylinder = extrudes->add(extrudeCylinder);
	if (!extCylinder) return false;

	Ptr<ThreadDataQuery> threadDataQuery = threadFeatures->threadDataQuery();
	if (!threadDataQuery) return false;

	Ptr<ThreadInfo> threadInfo = threadFeatures->createThreadInfo(false, "ANSI Metric M Profile", "M65x4", "6g");
	if (!threadInfo) return false;

	Ptr<BRepBodies> bodies = rootComp->bRepBodies();
	if (!bodies) return false;

	Ptr<BRepBody> body = bodies->item(0);
	if (!body) return false;

	Ptr<BRepFaces> sideFaces = body->faces();
	if (!sideFaces) return false;

	Ptr<BRepFace> sideface = sideFaces->item(0);
	if (!sideface) return false;

	Ptr<ObjectCollection> faces = ObjectCollection::create();
	if (!faces) return false;

	faces->add(sideface);

	Ptr<ThreadFeatureInput> threadInput = threadFeatures->createInput(faces, threadInfo);
	if (!threadInput) return false;

	threadInput->threadLength(ValueInput::createByReal(threadLength));

	Ptr<ThreadFeature> thread = threadFeatures->add(threadInput);
	if (!thread) return false;


	Ptr<ConstructionPlanes> ctorPlanes = rootComp->constructionPlanes();
	if (!ctorPlanes) return false;

	Ptr<ConstructionPlaneInput> ctorPlaneInput = ctorPlanes->createInput();
	if (!ctorPlaneInput) return false;

	bool retPlane = ctorPlaneInput->setByOffset(rootComp->xYConstructionPlane(), ValueInput::createByReal(distanceoffsetPlanes));
	if (!retPlane) return false;

	Ptr<ConstructionPlane> ctorPlane = ctorPlanes->add(ctorPlaneInput);
	if (!ctorPlane) return false;


	Ptr<Sketch> sketchSlot = sketches->add(ctorPlane);
	if (!sketchSlot)
		return false;

	Ptr<SketchCurves> sketchCurvesSlot = sketchSlot->sketchCurves();
	if (!sketchCurvesSlot)
		return false;

	Ptr<SketchCircles> sketchCirclesSlot = sketchCurvesSlot->sketchCircles();
	if (!sketchCirclesSlot)
		return false;

	sketchCirclesSlot->addByCenterRadius(centerPoint, radiusSlotInternal);
	sketchCirclesSlot->addByCenterRadius(centerPoint, radiusSlotExternal);

	Ptr<Profiles> profilesSlot = sketchSlot->profiles();
	if (!profilesSlot)
		return false;

	Ptr<Profile> profileSlot = profilesSlot->item(1);
	if (!profileSlot)
		return false;

	Ptr<ExtrudeFeatureInput> extFeatureSlot = extrudes->createInput(profileSlot, FeatureOperations::CutFeatureOperation);
	if (!extFeatureSlot)
		return false;

	extFeatureSlot->setDistanceExtent(false, ValueInput::createByReal(distanceSlot));

	extFeatureSlot->isSolid(true);

	Ptr<ExtrudeFeature> extSlot = extrudes->add(extFeatureSlot);
	if (!extSlot) return false;

	Ptr<Sketch> sketchPolygon = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchPolygon)
		return false;

	Ptr<SketchCurves> sketchCurvesPolygon = sketchPolygon->sketchCurves();
	if (!sketchCurvesPolygon)
		return false;

	Ptr<SketchLines> sketchLines = sketchCurvesPolygon->sketchLines();

	Ptr<SketchLine> lines = sketchLines->addByTwoPoints(Point3D::create(0, 3.7356, 0), Point3D::create(-3.2351, 1.8678, 0));
	if (!lines) return false;

	Ptr<SketchLine> lines1 = sketchLines->addByTwoPoints(Point3D::create(-3.2351, 1.8678, 0), Point3D::create(-3.2351, -1.8678, 0));
	if (!lines1)
		return false;

	Ptr<SketchLine> lines2 = sketchLines->addByTwoPoints(Point3D::create(-3.2351, -1.8678, 0), Point3D::create(0, -3.7356, 0));
	if (!lines2)
		return false;

	Ptr<SketchLine> lines3 = sketchLines->addByTwoPoints(Point3D::create(0, -3.7356, 0), Point3D::create(3.2351, -1.8678, 0));
	if (!lines3)
		return false;

	Ptr<SketchLine> lines4 = sketchLines->addByTwoPoints(Point3D::create(3.2351, -1.8678, 0), Point3D::create(3.2351, 1.8678, 0));
	if (!lines4)
		return false;

	Ptr<SketchLine> lines5 = sketchLines->addByTwoPoints(Point3D::create(3.2351, 1.8678, 0), Point3D::create(0, 3.7356, 0));
	if (!lines5)
		return false;

	Ptr<Profiles> profilesPolygon = sketchPolygon->profiles();
	if (!profilesPolygon) return false;

	Ptr<Profile> profilePolygon = profilesPolygon->item(0);
	if (!profilePolygon) return false;

	Ptr<ExtrudeFeatureInput> extFeaturePolygon = extrudes->createInput(profilePolygon, FeatureOperations::JoinFeatureOperation);
	if (!extFeatureSlot)
		return false;

	extFeaturePolygon->setDistanceExtent(false, ValueInput::createByReal(distancePolygon));

	extFeaturePolygon->isSolid(true);

	Ptr<ExtrudeFeature> extPolygon = extrudes->add(extFeaturePolygon);
	if (!extPolygon) return false;

	Ptr<Sketch> sketchHole = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchHole)
		return false;

	Ptr<SketchCurves> sketchCurvesHole = sketchHole->sketchCurves();
	if (!sketchCurvesHole)
		return false;

	Ptr<SketchPoints> SketchPoints = sketchHole->sketchPoints();
	if (!SketchPoints) return false;

	Ptr<SketchPoint> SketchPoint = SketchPoints->add(centerPoint);
	if (!SketchPoint) return false;

	Ptr<HoleFeatureInput> holeInput = holesFeatures->createSimpleInput(ValueInput::createByReal(diameterHole));
	if (!holeInput)
		return false;
	
	holeInput->setPositionBySketchPoint(SketchPoint);

	holeInput->setAllExtent(NegativeExtentDirection);
	//holeInput->tipAngle(false);

	Ptr<HoleFeature> hole = holesFeatures->add(holeInput);
	if (!hole)
		return false;


	Ptr<DataHub> hub = app->data()->activeHub();
	if (!hub) return false;
	Ptr<DataProjects> projects = hub->dataProjects();
	if (!projects) return false;

	Ptr<DataProject> project = nullptr;
	for (Ptr<DataProject>& proj : projects)
	{
		if (proj->name() == "Hydraulic Cylinder")
		{
			project = proj;
			break;
		}
	}
	if (!project) return false;

	Ptr<DataFolder> folder = project->rootFolder();
	if (!folder) return false;

	if (!doc->saveAs("Nut Guide Rod", folder, "description", "tag")) return false;

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
