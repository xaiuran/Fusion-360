
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

	//ui->messageBox("Hello script");
	Ptr<Documents> documents = app->documents();
	if (!documents)
		return false;
	Ptr<Document> doc = documents->add(DocumentTypes::FusionDesignDocumentType);
	if (!doc)
		return false;

	Ptr<Product> product = app->activeProduct();
	if (!product)
		return false;
	Ptr<Design> design = product;
	if (!design)
		return false;
	Ptr<Component> rootComp = design->rootComponent();
	if (!rootComp)
		return false;

	Ptr<Sketches> sketches = rootComp->sketches();
	if (!sketches)
		return false;
	Ptr<ConstructionPlane> xz = rootComp->xZConstructionPlane();
	if (!xz)
		return false;

	Ptr<Sketch> sketch = sketches->add(xz);
	if (!sketch)
		return false;
	Ptr<SketchCurves> sketchCurves = sketch->sketchCurves();
	if (!sketchCurves)
		return false;
	Ptr<SketchCircles> sketchCircles = sketchCurves->sketchCircles();
	if (!sketchCircles)
		return false;
	Ptr<SketchLines> sketchLines = sketchCurves->sketchLines();
	if (!sketchLines)
		return false;

	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint)
		return false;
	Ptr<SketchCircle> circle = sketchCircles->addByCenterRadius(centerPoint, 5.0);
	if (!circle)
		return false;
	Ptr<Point3D> point0 = Point3D::create(0, 10, 0);
	if (!point0)
		return false;
	Ptr<Point3D> point1 = Point3D::create(10, 10, 0);
	if (!point1)
		return false;
	Ptr<SketchLine> line = sketchLines->addByTwoPoints(point0, point1);
	if (!line)
		return false;

	Ptr<Profiles> profs = sketch->profiles();
	if (!profs)
		return false;
	Ptr<Profile> prof = profs->item(0);
	if(!prof)
		return false;


	Ptr<Features> feats = rootComp->features();
	if (!feats)
		return false;
	Ptr<ExtrudeFeatures> extrudes = feats->extrudeFeatures();
	if (!extrudes)
		return false;
	Ptr<ExtrudeFeatureInput> extInput = extrudes->createInput(prof, FeatureOperations::NewComponentFeatureOperation);
	if (!extInput)
		return false;


	Ptr<ValueInput> distance = ValueInput::createByReal(5);
	if (!distance)
		return false;
	extInput->setDistanceExtent(true, distance);
	extInput->isSolid(true);

	Ptr<ExtrudeFeature> ext = extrudes->add(extInput);
	if (!ext)
		return false;
	Ptr<BRepEdges> edges = ext->bodies()->item(0)->edges();


	Ptr<Sketch> sketch1 = sketches->add(xz);
	if (!sketch1)
		return false;
	Ptr<SketchCircle> circle1 = sketchCircles->addByCenterRadius(centerPoint, 5.0);
	if (!circle1)
		return false;
	Ptr<SketchCircle> circle2 = sketchCircles->addByCenterRadius(centerPoint, 6.0);
	if (!circle2)
		return false;
	Ptr<Point3D> point2 = Point3D::create(0, -10, 0);
	if (!point2)
		return false;
	Ptr<Point3D> point3 = Point3D::create(-10, -10, 0);
	if (!point3)
		return false;
	Ptr<SketchLine> line1 = sketchLines->addByTwoPoints(point2, point3);
	if (!line1)
		return false;

	Ptr<Profile> prof1 = profs->item(1);
	if (!prof1)
		return false;

	Ptr<ExtrudeFeatureInput> extInput1 = extrudes->createInput(prof1, FeatureOperations::NewComponentFeatureOperation);
	if (!extInput1)
		return false;

	Ptr<ValueInput> distance1 = ValueInput::createByReal(5);
	if (!distance1)
		return false;
	extInput1->setDistanceExtent(true, distance1);
	extInput1->isSolid(true);

	Ptr<ExtrudeFeature> ext1 = extrudes->add(extInput1);
	if (!ext1)
		return false;

	Ptr<BRepEdges> edges1 = ext1->bodies()->item(0)->edges();


	Ptr<JointGeometry> geo0 = JointGeometry::createByCurve(edges->item(0), JointKeyPointTypes::CenterKeyPoint);
	if (!geo0)
		return false;

	Ptr<JointGeometry> geo1 = JointGeometry::createByCurve(edges1->item(0), JointKeyPointTypes::CenterKeyPoint);
	if (!geo1)
		return false;

	Ptr<Joints> joints = rootComp->joints();
	if (!joints)
		return false;
	Ptr<JointInput> jointInput = joints->createInput(geo0, geo1);
	if (!jointInput)
		return false;

	Ptr<ValueInput> offset = ValueInput::createByString("40 mm");
	if (!offset)
		return false;
	jointInput->offset(offset);
	jointInput->isFlipped(false);
	jointInput->setAsRigidJointMotion();

	Ptr<Joint> joint = joints->add(jointInput);
	if (!joint)
		return false;

	adsk::fusion::FeatureHealthStates health = joint->healthState();
	if (health == adsk::fusion::FeatureHealthStates::ErrorFeatureHealthState || health == adsk::fusion::FeatureHealthStates::WarningFeatureHealthState) {
		std::string msg = joint->errorOrWarningMessage();
	}

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
