
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

	Ptr<MirrorFeatures> mirrorFeatures = features->mirrorFeatures();
	if (!mirrorFeatures)
		return false;

	Ptr<HoleFeatures> holesFeatures = features->holeFeatures();
	if (!holesFeatures)
		return false;



	double diameterHole = 1.270; 
	double distanceBase = 0.5; 
	double distanceHole = -1.0; 
	double angle = 180; 



	Ptr<Sketch> sketchBase = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchBase) return false;

	Ptr<SketchCurves> sketchCurvesBase = sketchBase->sketchCurves();
	if (!sketchCurvesBase) return false;

	Ptr<SketchLines> sketchLines = sketchCurvesBase->sketchLines();
	if (!sketchLines)
		return false;


	Ptr<SketchLine> lines = sketchLines->addByTwoPoints(Point3D::create(-1.270, 0, 0.7332), Point3D::create(-1.270, 0, -0.7332));
	if (!lines)
		return false;

	Ptr<SketchLine> lines1 = sketchLines->addByTwoPoints(Point3D::create(-1.270, 0, -0.7332), Point3D::create(0, 0, -1.4665));
	if (!lines1)
		return false;

	Ptr<SketchLine> lines2 = sketchLines->addByTwoPoints(Point3D::create(0, 0, -1.4665), Point3D::create(1.270, 0, -0.7332));
	if (!lines2)
		return false;

	Ptr<SketchLine> lines3 = sketchLines->addByTwoPoints(Point3D::create(1.270, 0, -0.7332), Point3D::create(1.270, 0, 0.7332));
	if (!lines3)
		return false;

	Ptr<SketchLine> lines4 = sketchLines->addByTwoPoints(Point3D::create(1.270, 0, 0.7332), Point3D::create(0, 0, 1.4665));
	if (!lines4)
		return false;

	Ptr<SketchLine> lines5 = sketchLines->addByTwoPoints(Point3D::create(0, 0, 1.4665), Point3D::create(-1.270, 0, 0.7332));
	if (!lines5)
		return false;

	Ptr<Profiles> profilesBase = sketchBase->profiles();
	if (!profilesBase)
		return false;

	Ptr<Profile> profileBase = profilesBase->item(0);
	if (!profileBase)
		return false;

	Ptr<ExtrudeFeatureInput> extInput = extrudes->createInput(profileBase, FeatureOperations::NewBodyFeatureOperation);
	if (!extInput)
		return false;

	extInput->setDistanceExtent(true, ValueInput::createByReal(distanceBase));
	
	extInput->isSolid(true);

	Ptr<ExtrudeFeature> ext = extrudes->add(extInput);
	if (!ext)
		return false;



	Ptr<Sketch> sketchHole = sketches->add(rootComp->xZConstructionPlane());
	if (!sketchHole) return false;

	Ptr<SketchCurves> sketchCurvesHole = sketchHole->sketchCurves();
	if (!sketchCurvesHole) return false;

	Ptr<SketchPoints> sketchPoints = sketchHole->sketchPoints();
	if (!sketchHole) return false;
	Ptr<SketchPoint> sketchPoint = sketchPoints->add(Point3D::create(0, 0, 0.5));
	if (!sketchPoint) return false;

	Ptr<HoleFeatureInput> holeInput = holesFeatures->createSimpleInput(ValueInput::createByReal(diameterHole));
	if (!holeInput) return false;

	holeInput->setPositionBySketchPoint(sketchPoint);
	holeInput->setAllExtent(PositiveExtentDirection);

	Ptr<HoleFeature> hole = holesFeatures->add(holeInput);
	if (!hole) return false;



	Ptr<Sketch> sketchRounding= sketches->add(rootComp->xYConstructionPlane());
	if (!sketchRounding) return false;

	Ptr<SketchCurves> sketchCurvesRounding = sketchRounding->sketchCurves();
	if (!sketchCurvesRounding) return false;

	Ptr<SketchLines> sketchLinesRounding = sketchCurvesRounding->sketchLines();
	if (!sketchLinesRounding) return false;

	Ptr<SketchLine> linesRounding1 = sketchLinesRounding->addByTwoPoints(Point3D::create(-1.270, 0.5, 0), Point3D::create(-1.5665, 0.5, 0));
	if (!linesRounding1) return false;
	Ptr<SketchLine> linesRounding2 = sketchLinesRounding->addByTwoPoints(Point3D::create(-1.5665, 0.5, 0), Point3D::create(-1.5665, 0.3288, 0));
	if (!linesRounding2) return false;
	Ptr<SketchLine> linesRounding3 = sketchLinesRounding->addByTwoPoints(Point3D::create(-1.5665, 0.3288, 0), Point3D::create(-1.270, 0.5, 0));
	if (!linesRounding3) return false;

	Ptr<Profiles> profilesRounding = sketchRounding->profiles();
	if (!profilesRounding) return false;

	Ptr<Profile> profileRounding = profilesRounding->item(0);
	if (!profileRounding) return false;

	Ptr<ConstructionAxis> yAxis = rootComp->yConstructionAxis();
	if (!yAxis) return false;

	Ptr<RevolveFeatureInput> revInputRounding = revolves->createInput(profileRounding, yAxis, FeatureOperations::CutFeatureOperation);
	if (!revInputRounding) return false;

	revInputRounding->setAngleExtent(false, ValueInput::createByReal(angle));
	revInputRounding->isSolid(true);

	Ptr<RevolveFeature> revolveRounding = revolves->add(revInputRounding);
	if (!revolveRounding) return false;

	Ptr<BRepFaces> endFaces = revolveRounding->faces();
	if (!endFaces) return false;

	Ptr<BRepFace> face = endFaces->item(0);
	if (!face) return false;

	Ptr<ObjectCollection> faceCollection = ObjectCollection::create();
	if (!faceCollection) return false;

	faceCollection->add(face);

	Ptr<MirrorFeatureInput> mirrorInput = mirrorFeatures->createInput(faceCollection, rootComp->xZConstructionPlane());
	if (!mirrorInput) return false;

	Ptr<MirrorFeature> mirrorFeature = mirrorFeatures->add(mirrorInput);
	if (!mirrorFeature) return false;

	Ptr<ThreadDataQuery> threadDataQuery = threadFeatures->threadDataQuery();
	if (!threadDataQuery) return false;
	
	Ptr<ThreadInfo> threadInfo = threadFeatures->createThreadInfo(true, "ANSI Metric M Profile", "M12x1.75", "6H");
	if (!threadInfo) return false;
	
	Ptr<BRepBodies> bodies = rootComp->bRepBodies();
	if (!bodies) return false;
	
	Ptr<BRepBody> body = bodies->item(0);
	if (!body) return false;
	
	Ptr<BRepFaces> sideFaces = body->faces();
	if (!sideFaces) return false;
	
	Ptr<BRepFace> sideface = sideFaces->item(19);
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

	// Выбор папки в облаке
	Ptr<DataFolder> folder = project->rootFolder();
	if (!folder) return false;

	// Сохранение сборки в облаке в выбранной папке с деталями
	if (!doc->saveAs("Tension Bolt Nut", folder, "description", "tag")) return false;

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
