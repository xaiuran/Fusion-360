
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
	Ptr<RevolveFeatures> revolves = rootComp->features()->revolveFeatures();
	if (!revolves) return false;
	Ptr<ThreadFeatures> threadFeatures = features->threadFeatures();
	if (!threadFeatures) return false;
	Ptr<HoleFeatures> holesFeatures = features->holeFeatures();
	if (!holesFeatures) return false;

	double diameterHole = 3.0; 
	double distanceBase = 2;
	double angle = 180; 
	double radiusArc = 0.05; 

	Ptr<Sketch> sketchBase = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchBase) return false;
	Ptr<SketchCurves> sketchCurves = sketchBase->sketchCurves();
	if (!sketchCurves) return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines) return false;
	Ptr<SketchLine> lines = sketchLines->addByTwoPoints(Point3D::create(-2.250, 1.299, 0),
		Point3D::create(0, 2.5981, 0));
	if (!lines)
		return false;
	Ptr<SketchLine> lines1 = sketchLines->addByTwoPoints(Point3D::create(0, 2.5981, 0),
		Point3D::create(2.250, 1.299, 0));
	if (!lines1)
		return false;
	Ptr<SketchLine> lines2 = sketchLines->addByTwoPoints(Point3D::create(2.250, 1.299, 0),
		Point3D::create(2.250, -1.299, 0));
	if (!lines2)
		return false;
	Ptr<SketchLine> lines3 = sketchLines->addByTwoPoints(Point3D::create(2.250, -1.299, 0),
		Point3D::create(0, -2.5981, 0));
	if (!lines3)
		return false;
	Ptr<SketchLine> lines4 = sketchLines->addByTwoPoints(Point3D::create(0, -2.5981, 0),
		Point3D::create(-2.250, -1.299, 0));
	if (!lines4)
		return false;
	Ptr<SketchLine> lines5 = sketchLines->addByTwoPoints(Point3D::create(-2.250, -1.299, 0),
		Point3D::create(-2.250, 1.299, 0));
	if (!lines5)
		return false;
	
	Ptr<Profiles> profilesBase = sketchBase->profiles();
	if (!profilesBase) return false;
	Ptr<Profile> profileBase = profilesBase->item(0);
	if (!profileBase) return false;
	Ptr<ExtrudeFeatureInput> extInput = extrudes->createInput(profileBase, FeatureOperations::NewBodyFeatureOperation);
	if (!extInput) return false;
	extInput->setDistanceExtent(false, ValueInput::createByReal(distanceBase));
	extInput->isSolid(true);
	Ptr<ExtrudeFeature> ext = extrudes->add(extInput);
	if (!ext) return false;

	Ptr<Sketch> sketchPP = sketches->add(rootComp->yZConstructionPlane());
	if (!sketchPP) return false;
	Ptr<SketchCurves> sketchCurvesPP = sketchPP->sketchCurves();
	if (!sketchCurvesPP) return false;
	Ptr<SketchLines> sketchlines = sketchCurvesPP->sketchLines();
	if (!sketchlines) return false;
	Ptr<SketchArcs> arcs = sketchCurvesPP->sketchArcs();
	if (!arcs) return false;
	Ptr<SketchLine> linePP = sketchlines->addByTwoPoints(Point3D::create(0, 0, 0), Point3D::create(0, -3.2415, 0));
	if (!linePP) return false;
	Ptr<SketchArc> arcPP = arcs->addByThreePoints(Point3D::create(-1.2, 0, 0), Point3D::create(-1.1017, -0.520, 0), Point3D::create(-0.0783, -3.2265, 0));
	if (!arcPP) return false;
	Ptr<SketchLine> line4 = sketchlines->addByTwoPoints(Point3D::create(0, 0, 0), Point3D::create(-1.2, 0, 0));
	if (!line4) return false;
	Ptr<SketchArc> arc = arcs->addFillet(arcPP, arcPP->endSketchPoint()->geometry(), linePP, linePP->endSketchPoint()->geometry(), radiusArc);
	if (!arc) return false;

	Ptr<Profiles> profilesPP = sketchPP->profiles();
	if (!profilesPP) return false;
	Ptr<Profile> profilePP = profilesPP->item(0);
	if (!profilePP) return false;
	Ptr<ConstructionAxis> zAxis = rootComp->zConstructionAxis();
	if (!zAxis) return false;
	Ptr<RevolveFeatureInput> revInput = revolves->createInput(profilePP, zAxis, FeatureOperations::JoinFeatureOperation);
	if (!revInput) return false;
	revInput->setAngleExtent(false, ValueInput::createByReal(angle));
	revInput->isSolid(true);
	Ptr<RevolveFeature> revPP = revolves->add(revInput);
	if (!revPP) return false;

	Ptr<Sketch> sketchRounding = sketches->add(rootComp->yZConstructionPlane());
	if (!sketchRounding) return false;
	Ptr<SketchCurves> sketchCurvesRounding = sketchRounding->sketchCurves();
	if (!sketchCurvesRounding) return false;
	Ptr<SketchLines> sketchLinesRounding = sketchCurvesRounding->sketchLines();
	if (!sketchLinesRounding) return false;
	Ptr<SketchLine> linesRounding1 = sketchLinesRounding->addByTwoPoints(Point3D::create(-2.0, 2.0, 0), Point3D::create(-2.0, 2.866, 0));
	if (!linesRounding1) return false;
	Ptr<SketchLine> linesRounding2 = sketchLinesRounding->addByTwoPoints(Point3D::create(-2.0, 2.866, 0), Point3D::create(-1.5, 2.866, 0));
	if (!linesRounding2) return false;
	Ptr<SketchLine> linesRounding3 = sketchLinesRounding->addByTwoPoints(Point3D::create(-1.5, 2.866, 0), Point3D::create(-2.0, 2.0, 0));
	if (!linesRounding3) return false;

	Ptr<Profiles> profilesRounding = sketchRounding->profiles();
	if (!profilesRounding) return false;
	Ptr<Profile> profileRounding = profilesRounding->item(0);
	if (!profileRounding) return false;
	Ptr<RevolveFeatureInput> revInputRounding = revolves->createInput(profileRounding, zAxis, FeatureOperations::CutFeatureOperation);
	if (!revInputRounding) return false;
	revInputRounding->setAngleExtent(false, ValueInput::createByReal(angle));
	revInputRounding->isSolid(true);
	Ptr<RevolveFeature> revRounding = revolves->add(revInputRounding);
	if (!revRounding) return false;

	Ptr<Sketch> sketchHole = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchHole) return false;
	Ptr<SketchCurves> sketchCurvesHole = sketchHole->sketchCurves();
	if (!sketchCurvesHole) return false;
	Ptr<SketchPoints> SketchPoints = sketchHole->sketchPoints();
	if (!SketchPoints) return false;
	Ptr<SketchPoint> SketchPoint = SketchPoints->add(Point3D::create(0, 0, 2.0));
	if (!SketchPoint) return false;

	Ptr<HoleFeatureInput> holeInput = holesFeatures->createSimpleInput(ValueInput::createByReal(diameterHole));
	if (!holeInput) return false;
	holeInput->setPositionBySketchPoint(SketchPoint);
	holeInput->setAllExtent(PositiveExtentDirection);
	Ptr<HoleFeature> hole = holesFeatures->add(holeInput);
	if (!hole) return false;

	Ptr<ThreadDataQuery> threadDataQuery = threadFeatures->threadDataQuery();
	if (!threadDataQuery) return false;
	Ptr<ThreadInfo> threadInfo = threadFeatures->createThreadInfo(true, "ANSI Metric M Profile", "M30x3.5", "6H");
	if (!threadInfo) return false;
	Ptr<BRepBodies> bodies = rootComp->bRepBodies();
	if (!bodies) return false;
	Ptr<BRepBody> body = bodies->item(0);
	if (!body) return false;
	Ptr<BRepFaces> sideFaces = body->faces();
	if (!sideFaces) return false;
	Ptr<BRepFace> sideface = sideFaces->item(0);
	if (!sideface) return false;
	Ptr<ThreadFeatureInput> threadInput = threadFeatures->createInput(sideface, threadInfo);
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
	if (!doc->saveAs("Rod Nut", folder, "description", "tag")) return false;
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
