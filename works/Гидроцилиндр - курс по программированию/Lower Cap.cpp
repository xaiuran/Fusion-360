
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

	//”казатели
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
	if(!fillets) return false;
	Ptr<RectangularPatternFeatures> rectangularPatterns = features->rectangularPatternFeatures();
	if (!rectangularPatterns) return false;

	//ƒобавл€ем переменные дл€ создани€ детали (Lower Cap)
	double distanceBase = 4.01; 
	double distanceRectangle = 7.82; 
	double distanceSemiCircles = -9.525; 
	double radiusHole = 1.5; 
	double radiusCirclesInternal1 = 7.0; 
	double radiusCirclesInternal2 = 7.5; 
	double radiusCirclesInternal3 = 2.0; 
	double distanceInternal = 0.8; 
	double distanceInternal1 = 3.683; 
	double radiusFillet = 0.3175; 
	double radiusFourHole = 0.635;
	double quantityOne = 2; 
	double distanceOne = 12.4; 
	double quantityTwo = 2; 
	double distanceTwo = -12.4;
	double threadLength = 12.4;

	Ptr<Sketch> sketchBase = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchBase) return false;
	Ptr<SketchCurves> sketchCurvesBase = sketchBase->sketchCurves();
	if (!sketchCurvesBase) return false;
	Ptr<SketchLines> sketchLineBase = sketchCurvesBase->sketchLines();
	if (!sketchLineBase) return false;
	Ptr<SketchLineList> linesBase = sketchLineBase->addCenterPointRectangle(Point3D::create(0, 0, 0), Point3D::create(8.255, 8.255, 0));
	if (!linesBase) return false;

	Ptr<Profiles> profilesBase = sketchBase->profiles();
	if (!profilesBase) return false;
	Ptr<Profile> profileBase = profilesBase->item(0);
	if (!profilesBase);
	Ptr<ExtrudeFeatureInput> extInputBase = extrudes->createInput(profileBase, FeatureOperations::NewBodyFeatureOperation);
	if (!extInputBase);
	extInputBase->setDistanceExtent(false, ValueInput::createByReal(distanceBase));
	extInputBase->isSolid(true);
	Ptr<ExtrudeFeature> extBase = extrudes->add(extInputBase);
	if (!extBase) return false;

	Ptr<Sketch> sketchRectangle = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchRectangle) return false;
	Ptr<SketchCurves> sketchCurvesRectangle = sketchRectangle->sketchCurves();
	if (!sketchCurvesRectangle) return false;
	Ptr<SketchLines> sketchLinesRectangle = sketchCurvesRectangle->sketchLines();
	if (!sketchLinesRectangle) return false;
	Ptr<SketchLineList>  linesRectagle = sketchLinesRectangle->addCenterPointRectangle(Point3D::create(0, 0, 0), Point3D::create(4.7625, 4.7625, 0));
	if (!linesRectagle) return false;
	
	Ptr<Profiles> profilesRectangle = sketchRectangle->profiles();
	if (!profilesRectangle)
		return false;
	Ptr<Profile> profileRectangle = profilesRectangle->item(0);
	if (!profileRectangle)
		return false;
	Ptr<ExtrudeFeatureInput> extInputRectangle = extrudes->createInput(profileRectangle,
		FeatureOperations::JoinFeatureOperation);
	if (!extInputRectangle)
		return false;
	extInputRectangle->setDistanceExtent(false, ValueInput::createByReal(distanceRectangle));
	extInputRectangle->isSolid(true);
	Ptr<ExtrudeFeature> extRectangle = extrudes->add(extInputRectangle);
	if (!extRectangle)
		return false;

	Ptr<Sketch> sketchSemiCircles = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchSemiCircles) return false;
	Ptr<SketchCurves> sketchecurvesSemiCircles = sketchSemiCircles->sketchCurves();
	if (!sketchecurvesSemiCircles) return false;
	Ptr<SketchArcs> arcs = sketchecurvesSemiCircles->sketchArcs();
	if (!arcs) return false;
	Ptr<SketchLines> sketchLinesArc = sketchecurvesSemiCircles->sketchLines();
	if (!sketchLinesArc) return false;
	arcs->addByThreePoints(Point3D::create(-4.7625, 7.820, 4.7625), Point3D::create(0,12.600, 4.7625), Point3D::create(4.7625, 7.820, 4.7625));
	sketchLinesArc->addByTwoPoints(Point3D::create(-4.7625, 7.820, 4.7625), Point3D::create(4.7625, 7.820, 4.7625));

	Ptr<Profiles> profilesSemiCircles = sketchSemiCircles->profiles();
	if (!profilesSemiCircles) return false;
	Ptr<Profile> profileSemiCircles = profilesSemiCircles->item(0);
	if (!profileSemiCircles) return false;
	Ptr<ExtrudeFeatureInput> extInputSemiCircles = extrudes->createInput(profileSemiCircles, FeatureOperations::JoinFeatureOperation);
	if (!extInputSemiCircles) return false;
	//false - в одну сторону!
	extInputSemiCircles->setDistanceExtent(false, ValueInput::createByReal(distanceSemiCircles));
	extInputSemiCircles->isSolid(true);
	Ptr<ExtrudeFeature> extSemiCircles = extrudes->add(extInputSemiCircles);
	if (!extSemiCircles) return false;
	
	Ptr<Sketch> sketchHole = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchHole) return false;
	Ptr<SketchCurves> sketchCurvesHole = sketchHole->sketchCurves();
	if (!sketchCurvesHole) return false;
	Ptr<SketchCircles> sketchCirclesHole = sketchCurvesHole->sketchCircles();
	if (!sketchCirclesHole) return false;
	sketchCirclesHole->addByCenterRadius(Point3D::create(0, 7.620, 4.7625), radiusHole);

	Ptr<Profiles> profilesHole = sketchHole->profiles();
	if (!profilesHole) return false;
	Ptr<Profile> profileHole = profilesHole->item(0);
	if (!profileHole) return false;
	Ptr<ExtrudeFeatureInput> extHole = extrudes->createInput(profileHole, FeatureOperations::CutFeatureOperation);
	if (!extHole) return false;
	extHole->setAllExtent(PositiveExtentDirection);
	extHole->isSolid(true);
	Ptr<ExtrudeFeature> extrudeHole = extrudes->add(extHole);
	if (!extrudeHole) return false;

	Ptr<Sketch> sketchRectangleHole = sketches->add(rootComp->yZConstructionPlane());
	if (!sketchRectangleHole) return false;
	Ptr<SketchCurves> sketchCurvesRectangleHole = sketchRectangleHole->sketchCurves();
	if (!sketchCurvesRectangleHole) return false;
	Ptr<SketchLines> sketchLinesRectangleHole = sketchCurvesRectangleHole->sketchLines();
	if (!sketchLinesRectangleHole) return false;
	sketchLinesRectangleHole->addTwoPointRectangle(Point3D::create(1.9055, 12.690, -4.7635), Point3D::create(-1.952, 4.01, -4.7635));
	if (!sketchLinesRectangleHole) return false;

	Ptr<Profiles> profilesRectangleHole = sketchRectangleHole->profiles();
	if (!profilesRectangleHole) return false;
	Ptr<Profile> profileRectangleHole = profilesRectangleHole->item(0);
	if (!profileRectangleHole) return false;
	Ptr<ExtrudeFeatureInput> extFeatureRectangleHole = extrudes->createInput(profileRectangleHole, FeatureOperations::CutFeatureOperation);
	if (!extFeatureRectangleHole) return false;
	extFeatureRectangleHole->setAllExtent(PositiveExtentDirection);
	Ptr<ExtrudeFeature> extRectangleHole = extrudes->add(extFeatureRectangleHole);
	if (!extRectangleHole) return false;

	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint) return false;
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
	Ptr<ExtrudeFeature> extInternal = extrudes->add(extFeatureInternal);
	if (!extInternal) return false;

	Ptr<Profiles> profilesInternal1 = sketchInternal->profiles();
	if (!profilesInternal1) return false;
	Ptr<Profile> profileInternal1 = profilesInternal1->item(2);
	if (!profileInternal1) return false;
	Ptr<ExtrudeFeatureInput> extFeatureInternal1 = extrudes->createInput(profileInternal1, FeatureOperations::CutFeatureOperation);
	extFeatureInternal1->setDistanceExtent(false, ValueInput::createByReal(distanceInternal1));
	extFeatureInternal1->isSolid(true);
	Ptr<ExtrudeFeature> extInternal3 = extrudes->add(extFeatureInternal1);
	if (!extInternal3) return false;

	Ptr<BRepBodies> bodies = rootComp->bRepBodies();
	if (!bodies) return false;
	Ptr<BRepBody> body = bodies->item(0);
	if (!body) return false;
	Ptr<BRepEdges> edges = body->edges();
	if (!edges) return false;
	Ptr<ObjectCollection> edgeCollection = ObjectCollection::create();
	if (!edgeCollection) return false;
	edgeCollection->add(edges->item(38));
	edgeCollection->add(edges->item(40));
	edgeCollection->add(edges->item(42));
	edgeCollection->add(edges->item(44));
	Ptr<FilletFeatureInput> input = fillets->createInput();
	if (!input) return false;
	input->addConstantRadiusEdgeSet(edgeCollection, ValueInput::createByReal(radiusFillet),true);
	input->isG2(false);
	input->isRollingBallCorner(true);
	Ptr<FilletFeature> fillet = fillets->add(input);
	if (!fillet) return false;

	//4 отверсти€
	Ptr<Sketch> sketchFourhole = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchFourhole) return false;
	Ptr<SketchCurves> sketchCurvesFourhole = sketchFourhole->sketchCurves();
	if (!sketchCurvesFourhole) return false;
	Ptr<SketchCircles> sketchCirclesFourhole = sketchCurvesFourhole->sketchCircles();
	if (!sketchCirclesFourhole) return false;
	sketchCirclesFourhole->addByCenterRadius(Point3D::create(-6.2, -6.2, 0), radiusFourHole);

	Ptr<Profiles> profilesFourhole = sketchFourhole->profiles();
	if (!profilesFourhole) return false;
	auto profilesCollection = ObjectCollection::create();
	profilesCollection->add(profilesFourhole->item(0));
	Ptr<ExtrudeFeatureInput> extFeatureFourhole = extrudes->createInput(profilesCollection, FeatureOperations::CutFeatureOperation);
	extFeatureFourhole->setAllExtent(PositiveExtentDirection);
	extFeatureFourhole->isSolid(true);
	Ptr<ExtrudeFeature> extFourhole = extrudes->add(extFeatureFourhole);
	if (!extFourhole) return false;

	Ptr<BRepBodies> bodiesFourhole = extFourhole->bodies();
	if (!bodiesFourhole) return false;
	Ptr<BRepBody> bodyFourhole = bodiesFourhole->item(0);
	if (!bodyFourhole) return false;
	Ptr<BRepFaces> faces = bodyFourhole->faces();
	if (!faces) return false;
	Ptr<BRepFace> endFace = faces->item(0);
	if (!endFace) return false;
	Ptr<ObjectCollection> inputEntites = ObjectCollection::create();
	if (!inputEntites) return false;
	inputEntites->add(endFace);
	Ptr<ConstructionAxis> zAxis = rootComp->zConstructionAxis();
	if (!zAxis) return false;
	Ptr<ConstructionAxis> xAxis = rootComp->xConstructionAxis();
	if (!xAxis) return false;

	Ptr<RectangularPatternFeatureInput> rectangularPatternInput = rectangularPatterns->createInput(inputEntites, xAxis, ValueInput::createByReal(quantityOne), ValueInput::createByReal(distanceOne),
	PatternDistanceType::ExtentPatternDistanceType);
	if (!rectangularPatternInput) return false;
	rectangularPatternInput->setDirectionTwo(zAxis, ValueInput::createByReal(quantityTwo), ValueInput::createByReal(distanceTwo));
	Ptr<RectangularPatternFeature> rectangularFeature = rectangularPatterns->add(rectangularPatternInput);
	if (!rectangularFeature) return false;

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
	if (!doc->saveAs("Lower Cap", folder, "description", "tag")) return false;
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
