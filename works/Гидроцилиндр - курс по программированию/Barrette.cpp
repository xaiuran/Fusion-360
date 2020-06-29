
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
	Ptr<ChamferFeatures> chamfers = features->chamferFeatures();
	if (!chamfers) return false;
	Ptr<MirrorFeatures> mirrorFeatures = features->mirrorFeatures();
	if (!mirrorFeatures) return false;

	double radius = 1.5;
	double distanceBarrette = 5.25;
	double radiuschamfer = 0.2;
	double distanceoffsetPlanes = 4.75;
	double radiusSlotInternal = 1.4375;
	double radiusSlotExternal = 1.5;
	double distanceSlot = 0.2;

	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint) return false;

	Ptr<Sketch> sketchBarrette = sketches->add(rootComp->yZConstructionPlane());
	if (!sketchBarrette) return false;

	Ptr<SketchCurves> sketchCurvesBarrette = sketchBarrette->sketchCurves();
	if (!sketchCurvesBarrette) return false;

	Ptr<SketchCircles> sketchCircelsBarrette = sketchCurvesBarrette->sketchCircles();
	if (!sketchCircelsBarrette) return false;

	sketchCircelsBarrette->addByCenterRadius(centerPoint, radius);

	Ptr<Profiles> profilesBarrette = sketchBarrette->profiles();
	if (!profilesBarrette) return false;
	Ptr<Profile> profileBarrette = profilesBarrette->item(0);
	if (!profileBarrette) return false;

	Ptr<ExtrudeFeatureInput> extFeatureBarrette = extrudes->createInput(profileBarrette, FeatureOperations::NewBodyFeatureOperation);
	extFeatureBarrette->setDistanceExtent(true, ValueInput::createByReal(distanceBarrette));
	extFeatureBarrette->isSolid(true);
	Ptr<ExtrudeFeature> extBarrette = extrudes->add(extFeatureBarrette);
	if (!extBarrette) return false;

	Ptr<BRepBodies> bodies = rootComp->bRepBodies();
	if (!bodies) return false;

	Ptr<BRepBody> body = bodies->item(0);
	if (!body) return false;

	Ptr<BRepEdges> edges = body->edges();
	if (!edges) return false;
	Ptr<ObjectCollection> edgeCollection = ObjectCollection::create();
	if (!edgeCollection) return false;

	edgeCollection->add(edges->item(0));
	edgeCollection->add(edges->item(1));

	Ptr<ChamferFeatureInput> input = chamfers->createInput(edgeCollection, true);
	if (!input) return false;
	input->setToEqualDistance(ValueInput::createByReal(radiuschamfer));
	input->isTangentChain(true);
	Ptr <ChamferFeature> chamfer = chamfers->add(input);
	if (!chamfer) return false;


	Ptr<ConstructionPlanes> ctorPlanes = rootComp->constructionPlanes();
	if (!ctorPlanes) return false;
	Ptr<ConstructionPlaneInput> ctorPlaneInput = ctorPlanes->createInput();
	if (!ctorPlaneInput) return false;
	Ptr<ValueInput> offsetPlanes = ValueInput::createByReal(distanceoffsetPlanes);
	if (!offsetPlanes) return false;
	bool retPlane = ctorPlaneInput->setByOffset(rootComp->yZConstructionPlane(), offsetPlanes);
	if (!retPlane) return false;
	Ptr<ConstructionPlane> ctorPlaneSlot = ctorPlanes->add(ctorPlaneInput);
	if (!ctorPlaneSlot) return false;

	Ptr<Sketch> sketchSlot = sketches->add(ctorPlaneSlot);
	if (!sketchSlot) return false;
	Ptr<SketchCurves> sketchCurvesSlot = sketchSlot->sketchCurves();
	if (!sketchCurvesSlot) return false;
	Ptr<SketchCircles> sketchCircelsSlot = sketchCurvesSlot->sketchCircles();
	if (!sketchCircelsSlot) return false;

	sketchCircelsSlot->addByCenterRadius(centerPoint, radiusSlotInternal);
	sketchCircelsSlot->addByCenterRadius(centerPoint, radiusSlotExternal);

	Ptr<Profiles> profilesSlot = sketchSlot->profiles();
	if (!profilesSlot) return false;
	Ptr<Profile> profileSlot = profilesSlot->item(1);
	if (!profileSlot) return false;
	Ptr<ExtrudeFeatureInput> extFeatureSlot = extrudes->createInput(profileSlot, FeatureOperations::NewBodyFeatureOperation);
	extFeatureSlot->setDistanceExtent(true, ValueInput::createByReal(distanceSlot));
	extFeatureBarrette->isSolid(true);
	Ptr<ExtrudeFeature> extSlot = extrudes->add(extFeatureSlot);
	if (!extSlot) return false;

	Ptr<BRepFaces> faces = extSlot->faces();
	if (!faces) return false;
	Ptr<ObjectCollection> inputEntites = ObjectCollection::create();
	if (!inputEntites) return false;
	inputEntites->add(extSlot);

	Ptr<MirrorFeature> mirrorInput = mirrorFeatures->createInput(inputEntites, rootComp->yZConstructionPlane());
	if (!mirrorInput) return false;
	Ptr<MirrorFeature> mirrorFeature = mirrorFeatures->add(mirrorInput);
	if (!mirrorFeature) return false;

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
	if (!doc->saveAs("Barrette", folder, "description", "tag")) return false;
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
