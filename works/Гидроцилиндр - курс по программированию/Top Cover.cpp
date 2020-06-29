
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

	Ptr<Documents> documents = app->documents();
	if (!documents)return false;
	Ptr<Document> doc = documents->add(DocumentTypes::FusionDesignDocumentType);
	if (!doc)return false;
	Ptr<Design> design = app->activeProduct();
	if (!design)return false;
	Ptr<Component> rootComp = design->rootComponent();
	if (!rootComp)return false;
	Ptr<Features> features = rootComp->features();
	if (!features) return false;
	Ptr<Sketches> sketches = rootComp->sketches();
	if (!sketches) return false;
	Ptr<ExtrudeFeatures> extrudes = features->extrudeFeatures();
	if (!extrudes) return false;
	Ptr<FilletFeatures> fillets = features->filletFeatures();
	if (!fillets) return false;
	Ptr<ThreadFeatures> threadFeatures = features->threadFeatures();
	if (!threadFeatures) return false;
	Ptr<HoleFeatures> holes = features->holeFeatures();
	if (!holes) return false;

	double distanceRectangle = 5.080;
	double radiusCylinder = 4.0; 
	double distanceCylinder = 6.2; 
	double radiusHole = 3.2; 
	double distanceHole = -3.8;
	double radiusHoleInternal = 3.0; 
	double distanceHoleInternal = -6.6; 
	double radiusCirclesInternal1 = 7.0; 
	double radiusCirclesInternal2 = 7.5; 
	double radiusCirclesInternal3 = 2.0; 
	double distanceInternal = 0.8;
	double distanceInternal1 = 2.2; 
	double diameterHole = 1.270; 
	double distanceB = 1.95; 
	double radiusFillet = 0.3175;

	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint) return false;
	Ptr<Sketch> sketchRectangle = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchRectangle) return false;
	Ptr<SketchCurves> sketchCurvesRectangle = sketchRectangle->sketchCurves();
	if (!sketchCurvesRectangle) return false;
	Ptr<SketchLines> sketchLines = sketchCurvesRectangle->sketchLines();
	if (!sketchLines) return false;
	Ptr<SketchLineList> lines1 = sketchLines->addCenterPointRectangle(centerPoint, Point3D::create(8.255, 8.255, 0));
	if (!lines1) return false;

	Ptr<Profiles> profilesRectangle = sketchRectangle->profiles();
	if (!profilesRectangle) return false;
	Ptr<Profile> profileRectangle = profilesRectangle->item(0);
	if (!profileRectangle) return false;
	Ptr<ExtrudeFeatureInput> extInputRectangle = extrudes->createInput(profileRectangle, FeatureOperations::NewBodyFeatureOperation);
	if (!extInputRectangle) return false;
	extInputRectangle->setDistanceExtent(false, ValueInput::createByReal(distanceRectangle));
	extInputRectangle->isSolid(true);
	Ptr<ExtrudeFeature> extRectangle = extrudes->add(extInputRectangle);
	if (!extRectangle) return false;

	Ptr<Sketch> sketchCylinder = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchCylinder) return false;
	Ptr<SketchCurves> sketchCurvesCylinder = sketchCylinder->sketchCurves();
	if (!sketchCurvesCylinder) return false;
	Ptr<SketchCircles> sketchCirclesCylinder = sketchCurvesCylinder->sketchCircles();
	if (!sketchCirclesCylinder) return false;
	sketchCirclesCylinder->addByCenterRadius(Point3D::create(0, 0, 5.080), radiusCylinder);

	Ptr<Profiles> profilesCylinder = sketchCylinder->profiles();
	if (!profilesCylinder) return false;
	Ptr<Profile> profileCylinder = profilesCylinder->item(0);
	if (!profileCylinder) return false;
	Ptr<ExtrudeFeatureInput> extFeatureCylinder = extrudes->createInput(profileCylinder, FeatureOperations::JoinFeatureOperation);
	extFeatureCylinder->setDistanceExtent(false, ValueInput::createByReal(distanceCylinder));
	extFeatureCylinder->isSolid(true);
	Ptr<ExtrudeFeature> extCylinder = extrudes->add(extFeatureCylinder);
	if (!extCylinder) return false;

	Ptr<Sketch> sketchHole = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchHole) return false;
	Ptr<SketchCurves> sketchCurvesHole = sketchHole->sketchCurves();
	if (!sketchCurvesHole) return false;
	Ptr<SketchCircles> sketchCirclesHole = sketchCurvesHole->sketchCircles();
	if (!sketchCirclesHole) return false;
	sketchCirclesHole->addByCenterRadius(Point3D::create(0, 0, 11.280), radiusHole);

	Ptr<Profiles> profilesHole = sketchHole->profiles();
	if (!profilesHole) return false;
	Ptr<Profile> profileHole = profilesHole->item(0);
	if (!profileHole) return false;
	Ptr<ExtrudeFeatureInput> extFeatureHole = extrudes->createInput(profileHole, FeatureOperations::CutFeatureOperation);
	extFeatureHole->setDistanceExtent(false, ValueInput::createByReal(distanceHole));
	extFeatureHole->isSolid(true);
	Ptr<ExtrudeFeature> extHole = extrudes->add(extFeatureHole);
	if (!extHole) return false;
	
	Ptr<Sketch> sketchHoleInternal = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchHoleInternal) return false;
	Ptr<SketchCurves> sketchCurvesHoleInternal = sketchHoleInternal->sketchCurves();
	if (!sketchCurvesHoleInternal) return false;
	Ptr<SketchCircles> sketchCirclesHoleInternal = sketchCurvesHoleInternal->sketchCircles();
	if (!sketchCirclesHoleInternal) return false;
	sketchCirclesHoleInternal->addByCenterRadius(Point3D::create(0, 0, 8.480), radiusHoleInternal);
	
	Ptr<Profiles> profilesHoleInternal = sketchHoleInternal->profiles();
	if (!profilesHoleInternal) return false;
	Ptr<Profile> profileHoleInternal = profilesHoleInternal->item(0);
	if (!profileHoleInternal) return false;
	Ptr<ExtrudeFeatureInput> extFeatureHoleInternal = extrudes->createInput(profileHoleInternal, FeatureOperations::CutFeatureOperation);
	extFeatureHoleInternal->setDistanceExtent(false, ValueInput::createByReal(distanceHoleInternal));
	extFeatureHoleInternal->isSolid(true);
	Ptr<ExtrudeFeature> extHoleInternal = extrudes->add(extFeatureHoleInternal);
	if (!extHoleInternal) return false;

	Ptr<Sketch> sketchInternal = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchInternal) return false;
	Ptr<SketchCurves> sketchCurvesInternal = sketchInternal->sketchCurves();
	if (!sketchCurvesInternal) return false;
	Ptr<SketchCircles> sketchCirclesInternal = sketchCurvesInternal->sketchCircles();
	if (!sketchCirclesInternal) return false;
	sketchCirclesInternal->addByCenterRadius(centerPoint, radiusCirclesInternal1);
	sketchCirclesInternal->addByCenterRadius(centerPoint, radiusCirclesInternal2);
	sketchCirclesInternal->addByCenterRadius(centerPoint, radiusCirclesInternal3);
	
	Ptr<Profiles> profilesInternal = sketchInternal->profiles();
	if (!profilesInternal) return false;
	Ptr<Profile> profileInternal = profilesInternal->item(1);
	if (!profileInternal) return false;
	Ptr<ExtrudeFeatureInput> extFeatureInternal = extrudes->createInput(profileInternal, FeatureOperations::CutFeatureOperation);
	extFeatureInternal->setDistanceExtent(false, ValueInput::createByReal(distanceInternal));
	extFeatureInternal->isSolid(true);
	Ptr<ExtrudeFeature> extInternal1 = extrudes->add(extFeatureInternal);
	if (!extInternal1) return false;

	Ptr<Profiles> profilesInternal1 = sketchInternal->profiles();
	if (!profilesInternal1) return false;
	Ptr<Profile> profileInternal1 = profilesInternal1->item(2);
	if (!profileInternal1) return false;
	Ptr<ExtrudeFeatureInput> extFeatureInternal1 = extrudes->createInput(profileInternal1, FeatureOperations::CutFeatureOperation);
	extFeatureInternal1->setDistanceExtent(false, ValueInput::createByReal(distanceInternal1));
	extFeatureInternal1->isSolid(true);
	Ptr<ExtrudeFeature> extInternal3 = extrudes->add(extFeatureInternal1);
	if (!extInternal3) return false;

	Ptr<Sketch> sketchFourhole = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchFourhole) return false;
	Ptr<SketchCurves> sketchCurvesFourhole = sketchFourhole->sketchCurves();
	if (!sketchCurvesFourhole) return false;
	Ptr<SketchPoints> SketchPoints = sketchFourhole->sketchPoints();
	if (!SketchPoints);
	//Построение эскиза точек
	Ptr<SketchPoint> SketchPoint1 = SketchPoints->add(Point3D::create(-6.2, -6.2, 7.030));
	if (!SketchPoint1) return false;
	Ptr<SketchPoint> SketchPoint2 = SketchPoints->add(Point3D::create(6.2, -6.2, 7.030));
	if (!SketchPoint1) return false;
	Ptr<SketchPoint> SketchPoint3 = SketchPoints->add(Point3D::create(-6.2, 6.2, 7.030));
	if (!SketchPoint2) return false;
	Ptr<SketchPoint> SketchPoint4 = SketchPoints->add(Point3D::create(6.2, 6.2, 7.030));
	if (!SketchPoint3) return false;

	Ptr<ObjectCollection> ptColl = ObjectCollection::create();
	if (!ptColl) return false;
	ptColl->add(SketchPoint1);
	ptColl->add(SketchPoint2);
	ptColl->add(SketchPoint3);
	ptColl->add(SketchPoint4);

	Ptr<HoleFeatureInput> holeInput = holes->createSimpleInput(ValueInput::createByReal(diameterHole));
	if (!holeInput) return false;
	holeInput->setPositionBySketchPoints(ptColl);
	holeInput->setAllExtent(PositiveExtentDirection);
	Ptr<HoleFeature> hole = holes->add(holeInput);
	if (!hole) return false;

	Ptr<BRepBodies> bodiesB = rootComp->bRepBodies();
	if (!bodiesB) return false;
	Ptr<BRepBody> bodyB = bodiesB->item(0);
	if (!bodyB) return false;
	Ptr<BRepFaces> facesBase = bodyB->faces();
	if (!facesBase) return false;
	Ptr<BRepFace> FaceBase = facesBase->item(19);
	if (!FaceBase) return false;
	Ptr<ExtrudeFeatureInput> extInputBase = extrudes->createInput(FaceBase, FeatureOperations::JoinFeatureOperation);
	if (!extInputBase) return false;
	extInputBase->setDistanceExtent(false, ValueInput::createByReal(distanceB));
	extInputBase->isSolid(true);
	Ptr<ExtrudeFeature> extB = extrudes->add(extInputBase);
	if (!extB) return false;

	Ptr<BRepBodies> bodies = rootComp->bRepBodies();
	if (!bodiesB) return false;
	Ptr<BRepBody> body = bodies->item(0);
	if (!bodyB) return false;
	Ptr<BRepEdges> edges = body->edges();
	if (!edges) return false;
	Ptr<ObjectCollection> edgeCollection = ObjectCollection::create();
	if (!edgeCollection);
	edgeCollection->add(edges->item(28));
	edgeCollection->add(edges->item(29));
	edgeCollection->add(edges->item(30));
	edgeCollection->add(edges->item(31));
	Ptr<FilletFeatureInput> input = fillets->createInput();
	if (!input) return false;
	input->addConstantRadiusEdgeSet(edgeCollection, ValueInput::createByReal(radiusFillet), true);
	input->isG2(false);
	input->isRollingBallCorner(true);
	Ptr<FilletFeature> fillet = fillets->add(input);
	if (!fillet) return false;

	Ptr<ThreadDataQuery> threadDataQuery = threadFeatures->threadDataQuery();
	if (!threadDataQuery) return false;
	Ptr<ThreadInfo> threadInfo = threadFeatures->createThreadInfo(true, "ANSI Metric M Profile", "M65x4", "6H");
	if (!threadInfo) return false;
	Ptr<BRepBodies> bodiesThread = rootComp->bRepBodies();
	if (!bodiesThread) return false;
	Ptr<BRepBody> bodyThread = bodiesThread->item(0);
	if (!bodyThread) return false;
	Ptr<BRepFaces> FacesThread = bodyThread->faces();
	if (!FacesThread) return false;
	Ptr<BRepFace> faceThread = FacesThread->item(18);
	if (!faceThread) return false;
	Ptr<ThreadFeatureInput> threadInput = threadFeatures->createInput(faceThread, threadInfo);
	if (!threadInput) return false;
	threadInput->isFullLength(true);
	Ptr<ThreadFeature> thread = threadFeatures->add(threadInput);
	if (!thread) return false;

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
	if (!doc->saveAs("Top Cover", folder, "description", "tag")) return false;
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
