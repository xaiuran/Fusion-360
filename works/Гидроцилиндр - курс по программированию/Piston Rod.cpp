
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
	if (!threadFeatures)
		return false;


	double radiusCylinder = 2.0; 
	double distanceCylinder = 28; 
	double radiusInternalPM = 1.5; 
	double radiusExternalPM = 2.0; 
	double distancePM = -3.6; 
	double distanceRectangle = 5.3; 
	double distancePM1 = 8.0; 

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
	
	Ptr<SketchCircle> sketchCircle = sketchCircles->addByCenterRadius(centerPoint, radiusCylinder);
	if (!sketchCircle)
		return false;
	

	Ptr<Profiles> profilesCylinder = sketchCylinder->profiles();
	if (!profilesCylinder)
		return false;

	Ptr<Profile> profileCylinder = profilesCylinder->item(0);
	if (!profileCylinder)
		return false;
	
	Ptr<ExtrudeFeatureInput> extrudeCylinder = extrudes->createInput(profileCylinder, NewBodyFeatureOperation);
	if (!extrudeCylinder)
		return false;
	
	extrudeCylinder->setDistanceExtent(true, ValueInput::createByReal(distanceCylinder));
	
	extrudeCylinder->isSolid(true);
	
	Ptr<ExtrudeFeature> ext = extrudes->add(extrudeCylinder);
	if (!ext) return false;
	


	Ptr<Sketch> sketchPM = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchPM) return false;
	
	Ptr<SketchCurves> sketchCurvesPM = sketchPM->sketchCurves();
	if (!sketchCurvesPM) return false;
	
	Ptr<SketchCircles> sketchCirclesPM = sketchCurvesPM->sketchCircles();
	if (!sketchCirclesPM) return false;
	
	sketchCirclesPM->addByCenterRadius(Point3D::create(0, 0, 28.0), radiusInternalPM);
	sketchCirclesPM->addByCenterRadius(Point3D::create(0, 0, 28.0), radiusExternalPM);
	


	Ptr<Profiles> profilesPM = sketchPM->profiles();
	if (!profilesPM) return false;
	
	Ptr<Profile> profilePM = profilesPM->item(1);
	if (!profilePM) return false;
	
	Ptr<ExtrudeFeatureInput> extFeaturePM = extrudes->createInput(profilePM, FeatureOperations::CutFeatureOperation);

	
	extFeaturePM->setDistanceExtent(false, ValueInput::createByReal(distancePM));
	
	extFeaturePM->isSolid(true);
	
	Ptr<ExtrudeFeature> extPM = extrudes->add(extFeaturePM);
	if (!extPM) return false;
	

	Ptr<ThreadDataQuery> threadDataQueryPM = threadFeatures->threadDataQuery();
	if (!threadDataQueryPM) return false;

	Ptr<ThreadInfo> threadPM = threadFeatures->createThreadInfo(false, "ANSI Metric M Profile", "M30x2", "6g");
	if (!threadPM) return false;

	Ptr<BRepFaces> sideFacesPM = extPM->sideFaces();
	if (!sideFacesPM) return false;

	Ptr<BRepFace> sideFacePM = sideFacesPM->item(0);
	if (!sideFacePM) return false;

	Ptr<ThreadFeatureInput> threadInputPM = threadFeatures->createInput(sideFacePM, threadPM);
	if (!threadInputPM) return false;
	threadInputPM->isFullLength(true);
	Ptr<ThreadFeature> thread = threadFeatures->add(threadInputPM);
	if (!thread) return false;

	Ptr<Sketch> sketchRectangle = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchRectangle) return false;
	
	Ptr<SketchCurves> sketchCurvesRectangle = sketchRectangle->sketchCurves();
	if (!sketchCurvesRectangle) return false;

	
	Ptr<SketchLines> sketchLines = sketchCurvesRectangle->sketchLines();
	if (!sketchLines)
		return false;

	sketchLines->addTwoPointRectangle(Point3D::create(-3.1, 2.3, 28.0), Point3D::create(-1.7, -1.7, 28.0));
	sketchLines->addTwoPointRectangle(Point3D::create(1.7, 2.3, 28.0), Point3D::create(3.1, -1.7, 28.0));

	Ptr<Profiles> profilesRectangle = sketchRectangle->profiles();
	if (!profilesRectangle) return false;

	
	auto profilesCollection = ObjectCollection::create();
	profilesCollection->add(profilesRectangle->item(0));
	profilesCollection->add(profilesRectangle->item(1));
	
	Ptr<ExtrudeFeatureInput> extFeatureRectangle = extrudes->createInput(profilesCollection, FeatureOperations::CutFeatureOperation);
	
	extFeatureRectangle->setDistanceExtent(true, ValueInput::createByReal(distanceRectangle));
	
	extFeatureRectangle->isSolid(true);
	
	Ptr<ExtrudeFeature> extFourhole = extrudes->add(extFeatureRectangle);
	if (!extFourhole) return false;
	



	Ptr<Sketch> sketchPM1 = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchPM1) return false;

	Ptr<SketchCurves> sketchCurvesPM1 = sketchPM1->sketchCurves();
	if (!sketchCurvesPM1) return false;

	Ptr<SketchCircles> sketchCirclesPM1 = sketchCurvesPM1->sketchCircles();
	if (!sketchCirclesPM1) return false;

	sketchCirclesPM1->addByCenterRadius(Point3D::create(0, 0, -28.0), radiusInternalPM);
	sketchCirclesPM1->addByCenterRadius(Point3D::create(0, 0, -28.0), radiusExternalPM);

	

	Ptr<Profiles> profilesPM1 = sketchPM1->profiles();
	if (!profilesPM1) return false;

	Ptr<Profile> profilePM1 = profilesPM1->item(1);
	if (!profilePM1) return false;

	Ptr<ExtrudeFeatureInput> extFeaturePM1 = extrudes->createInput(profilePM1, FeatureOperations::CutFeatureOperation);


	extFeaturePM1->setDistanceExtent(false, ValueInput::createByReal(distancePM1));

	extFeaturePM1->isSolid(true);

	Ptr<ExtrudeFeature> extPM1 = extrudes->add(extFeaturePM1);
	if (!extPM1) return false;

	

	Ptr<ThreadDataQuery> threadDataQueryPM1 = threadFeatures->threadDataQuery();
	if (!threadDataQueryPM1)
		return false;

	
	Ptr<ThreadInfo> threadInfoPM1 = threadFeatures->createThreadInfo(false, "ANSI Metric M Profile", "M30x3.5", "6g");
	if (!threadInfoPM1)
		return false;

	Ptr<BRepFaces> sideFacesPM1 = extPM1->sideFaces();
	if (!sideFacesPM1)
		return false;

	Ptr<BRepFace> sidefacePM1 = sideFacesPM1->item(0);
	if (!sidefacePM1)
		return false;

	Ptr<ThreadFeatureInput> threadInputPM1 = threadFeatures->createInput(sidefacePM1, threadInfoPM1);
	if (!threadInputPM1)
		return false;

	threadInputPM1->isFullLength(true);

	Ptr<ThreadFeature> threadPM1 = threadFeatures->add(threadInputPM1);
	if (!threadPM1)
		return false;
	

	
	Ptr<DataHub> hub = app->data()->activeHub();
	if (!hub) return false;
		Ptr<DataProjects> projects = hub->dataProjects();
		if (!projects) return false;
		
		Ptr<DataProject> project = nullptr;
		for (Ptr<DataProject>& proj : projects)
		{
			if (proj->name() == "My Hydraulic Cylinder")
			{
				project = proj;
				break;
			}
		}
		if (!project) return false;
		
		Ptr<DataFolder> folder = project->rootFolder();
		if (!folder) return false;
	
		if (!doc->saveAs("Piston Rod", folder, "description", "tag")) return false;
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
