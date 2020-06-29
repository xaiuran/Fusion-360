
#include <Core/CoreAll.h>
#include <Fusion/FusionAll.h>
#include <CAM/CAMAll.h>

using namespace adsk::core;
using namespace adsk::fusion;
using namespace adsk::cam;
using namespace std;

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
	Ptr<Document> doc = app->activeDocument();
	if (!doc) return false;
	Ptr<Design> design = app->activeProduct();
	if (!design) return false;
	Ptr<Component> rootComp = design->rootComponent();
	if (!rootComp) return false;
	Ptr<Occurrences> occurrences = rootComp->occurrences();
	if (!occurrences) return false;
	Ptr<Joints> joints = rootComp->joints();
	if (!joints)
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
	Ptr<DataFiles> files = folder->dataFiles();
	if (!files) return false;

	//Добавление деталей в сборку
	vector<string> filesName {
		"Cylinder Housing", "Backing Seal", "Backing Seal", "Top Cover", "Lower Cap", "Piston", "Piston Seal", "Piston Seal", "Piston Rod", "Rod Nut", "Fork",
		"Rod Guide", "Rod Guide Seal", "Nut Guide Rod", "Barrette", "Barrette", "Tension Bolt", "Tension Bolt Nut", 
	
	};

	vector<Ptr<DataFile>> dataFilesArr;
	for (string fileName : filesName)
	{
		for (Ptr<DataFile>& datFil : files)
		{
			if (datFil->name() == fileName)
			{
				dataFilesArr.push_back(datFil);
			}

		}
	}

	for (Ptr<DataFile>& dataFile : dataFilesArr)
	{
		Ptr<Occurrences> refOccur = occurrences->addByInsert(dataFile, Matrix3D::create(), false);

	}

	if (occurrences->count() != filesName.size())
		return false;

	occurrences->item(0)->isGrounded(true);

	auto bodyCH = occurrences->item(0)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesCH = bodyCH->edges();
	if (!edgesCH)
		return false;
	auto bodyBS1 = occurrences->item(1)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesBS1 = bodyBS1->edges();
	if (!edgesBS1)
		return false;
	auto bodyBS2 = occurrences->item(2)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesBS2 = bodyBS2->edges();
	if (!edgesBS2) 
		return false;
	auto bodyTC = occurrences->item(3)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesTC = bodyTC->edges();
	if (!edgesTC)
		return false;
	auto bodyLC = occurrences->item(4)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesLC = bodyLC->edges();
	if (!edgesLC)
		return false;
	auto bodyP = occurrences->item(5)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesP = bodyP->edges();
	if (!edgesP) 
		return false;
	auto bodyPS1 = occurrences->item(6)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesPS1 = bodyPS1->edges();
	if (!edgesPS1) 
		return false;
	auto bodyPS2 = occurrences->item(7)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesPS2 = bodyPS2->edges();
	if (!edgesPS2) 
		return false;
	auto bodyPR = occurrences->item(8)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesPR = bodyPR->edges();
	if (!edgesPR)
		return false;
	auto bodyRN = occurrences->item(9)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesRN = bodyRN->edges();
	if (!edgesRN)
		return false;
	auto bodyF = occurrences->item(10)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesF = bodyF->edges();
	if (!edgesF)
		return false;
	auto bodyRG = occurrences->item(11)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesRG = bodyRG->edges();
	if (!edgesRG) 
		return false;
	auto bodyRGS = occurrences->item(12)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesRGS = bodyRGS->edges();
	if (!edgesRGS)
		return false;
	auto bodyNGR = occurrences->item(13)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesNGR = bodyNGR->edges();
	if (!edgesNGR)
		return false;
	auto bodyB1 = occurrences->item(14)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesB1 = bodyB1->edges();
	if (!edgesB1)
		return false;
	auto bodyB2 = occurrences->item(15)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesB2 = bodyB2->edges();
	if (!edgesB2)
		return false;
	auto bodyTB = occurrences->item(16)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesTB = bodyTB->edges();
	if (!edgesTB)
		return false;
	auto bodyTBN = occurrences->item(17)->bRepBodies()->item(0);
	Ptr<BRepEdges> edgesTBN = bodyTBN->edges();
	if (!edgesTBN)
		return false;


	Ptr<BRepFaces> facesTC = bodyTC->faces();
	if (!facesTC) return false;
	Ptr<BRepFaces> facesLC = bodyLC->faces();
	if (!facesLC) return false;



	//Первое соединение Cylinder Hoousing, Backing Seal
	Ptr<JointGeometry> geoCH1 = JointGeometry::createByCurve(edgesCH->item(2), JointKeyPointTypes::CenterKeyPoint);
	if (!geoCH1)
		return false;
	Ptr<JointGeometry> geoBS1 = JointGeometry::createByCurve(edgesBS1->item(2), JointKeyPointTypes::CenterKeyPoint);
	if (!geoBS1)
		return false;
	Ptr<JointInput> jointInputCHBS1 = joints->createInput(geoBS1, geoCH1);
	if (!jointInputCHBS1)
		return false;
	Ptr<ValueInput> offsetCHBS1 = ValueInput::createByString("8 mm");
	if (!offsetCHBS1)
		return false;
	jointInputCHBS1->offset(offsetCHBS1);
	jointInputCHBS1->isFlipped(true);
	jointInputCHBS1->setAsRigidJointMotion();
	Ptr<Joint> jointCHBS1 = joints->add(jointInputCHBS1);
	if (!jointCHBS1)
		return false;
	//В случае ошибки!
	adsk::fusion::FeatureHealthStates health = jointCHBS1->healthState();
	if (health == adsk::fusion::FeatureHealthStates::ErrorFeatureHealthState ||
		health == adsk::fusion::FeatureHealthStates::WarningFeatureHealthState)
	{
		std::string msg = jointCHBS1->errorOrWarningMessage();
		ui->messageBox(msg);
	}

	//Второе соединение CH, Backing Seal #2
	Ptr<JointGeometry> geoCH2 = JointGeometry::createByCurve(edgesCH->item(0), JointKeyPointTypes::CenterKeyPoint);
	if (!geoCH2)
		return false;
	Ptr<JointGeometry> geoBS2 = JointGeometry::createByCurve(edgesBS2->item(2), JointKeyPointTypes::CenterKeyPoint);
	if (!geoBS2)
		return false;
	Ptr<JointInput> jointInputCHBS2 = joints->createInput(geoBS2, geoCH2);
	if (!jointInputCHBS2)
		return false;
	Ptr<ValueInput> offsetCHBS2 = ValueInput::createByString("8 mm");
	if (!offsetCHBS2)
		return false;
	jointInputCHBS2->offset(offsetCHBS2);
	jointInputCHBS2->isFlipped(true);
	jointInputCHBS2->setAsRigidJointMotion();
	Ptr<Joint> jointCHBS2 = joints->add(jointInputCHBS2);
	if (!jointCHBS2)
		return false;
	
	//Третье соединение Cylinder Housing, Top Cover
	Ptr<JointGeometry> geoTC1 = JointGeometry::createByCurve(edgesTC->item(38), JointKeyPointTypes::CenterKeyPoint);
	if (!geoTC1)
		return false;
	Ptr<JointGeometry> geoCH3 = JointGeometry::createByCurve(edgesCH->item(3), JointKeyPointTypes::CenterKeyPoint);
	if (!geoCH3)
		return false;
	Ptr<JointInput>jointInputCHTC = joints->createInput(geoTC1, geoCH3);
	if (!jointInputCHTC)
		return false;
	jointInputCHTC->isFlipped(false);
	jointInputCHTC->setAsRigidJointMotion();
	Ptr<Joint> jointCHTC = joints->add(jointInputCHTC);
	if (!jointCHTC)
		return false;

	//Четвертое соединение Cylinder Housing, Lower Cap
	Ptr<JointGeometry> geoLC1 = JointGeometry::createByCurve(edgesLC->item(34), JointKeyPointTypes::CenterKeyPoint);
	if (!geoLC1)
		return false;
	Ptr<JointGeometry> geoCH4 = JointGeometry::createByCurve(edgesCH->item(1), JointKeyPointTypes::CenterKeyPoint);
	if (!geoCH4)
		return false;
	Ptr<JointInput>jointInputCHLC = joints->createInput(geoLC1, geoCH4);
	if (!jointInputCHLC)
		return false;
	jointInputCHLC->isFlipped(false);
	jointInputCHLC->setAsRigidJointMotion();
	Ptr<Joint> jointCHLC = joints->add(jointInputCHLC);
	if (!jointCHLC)
		return false;

	//Пятое соединение Piston и Piston Seal
	Ptr<JointGeometry> geoP1 = JointGeometry::createByCurve(edgesP->item(1), JointKeyPointTypes::CenterKeyPoint);
	if (!geoP1)
		return false;
	Ptr<JointGeometry> geoPS1 = JointGeometry::createByCurve(edgesPS1->item(7), JointKeyPointTypes::CenterKeyPoint);
	if (!geoPS1)
		return false;
	Ptr<JointInput> jointInputPPS1 = joints->createInput(geoPS1, geoP1);
	if (!jointInputPPS1)
		return false;
	jointInputPPS1->isFlipped(true);
	jointInputPPS1->setAsRigidJointMotion();
	Ptr<Joint> jointPPS1 = joints->add(jointInputPPS1);
	if (!jointPPS1)
		return false;

	//Шестое соединение Piston и Piston Seal
	Ptr<JointGeometry> geoP2 = JointGeometry::createByCurve(edgesP->item(11), JointKeyPointTypes::CenterKeyPoint);
	if (!geoP2)
		return false;
	Ptr<JointGeometry> geoPS2 = JointGeometry::createByCurve(edgesPS2->item(7), JointKeyPointTypes::CenterKeyPoint);
	if (!geoPS2)
		return false;
	Ptr<JointInput> jointInputPPS2 = joints->createInput(geoPS2, geoP2);
	if (!jointInputPPS2)
		return false;
	jointInputPPS2->isFlipped(true);
	jointInputPPS2->setAsRigidJointMotion();
	Ptr<Joint> jointPPS2 = joints->add(jointInputPPS2);
	if (!jointPPS2)
		return false;

	//Седьмое соединенение Piston Rod, Rod Nut 
	Ptr<BRepFaces> facesP = bodyP->faces();
	if (!facesP)
		return false;
	Ptr<BRepFaces> facesRN = bodyRN->faces();
	if (!facesRN)
		return false;
	Ptr<BRepFaces> facesPR = bodyPR->faces();
	if (!facesPR)
		return false;
	Ptr<JointGeometry> geoP3 = JointGeometry::createByPlanarFace(facesP->item(14), edgesP->item(4), JointKeyPointTypes::CenterKeyPoint);
	if (!geoP3)
		return false;
	Ptr<JointGeometry> geoPR1 = JointGeometry::createByCurve(edgesPR->item(0), JointKeyPointTypes::CenterKeyPoint);
	if (!geoPR1)
		return false;
	Ptr<JointInput> jointInputPPR1 = joints->createInput(geoP3, geoPR1);
	if (!jointInputPPR1)
		return false;
	jointInputPPR1->isFlipped(true);
	jointInputPPR1->setAsRigidJointMotion();
	Ptr<Joint> jointPPR1 = joints->add(jointInputPPR1);
	if (!jointPPR1)
		return false;
	Ptr<JointGeometry> geoRN= JointGeometry::createByPlanarFace(facesRN->item(11), edgesRN->item(0), JointKeyPointTypes::CenterKeyPoint);
	if (!geoRN)
		return false;
	Ptr<JointGeometry> geoP4 = JointGeometry::createByCurve(edgesP->item(5), JointKeyPointTypes::CenterKeyPoint);
	if (!geoP4)
		return false;
	Ptr<JointInput> jointInputPRN = joints->createInput(geoRN, geoP4);
	if (!jointInputPRN)
		return false;
	jointInputPRN->isFlipped(true);
	jointInputPRN->setAsRigidJointMotion();
	Ptr<Joint> jointPRN = joints->add(jointInputPRN);
	if (!jointPRN)
		return false;
	
	//Восьмое соединение 
	Ptr<JointGeometry> geoPR2 = JointGeometry::createByCurve(edgesPR->item(15), JointKeyPointTypes::CenterKeyPoint);
	if (!geoPR2)
			return false;
	Ptr<JointGeometry> geoF1 = JointGeometry::createByCurve(edgesF->item(5), JointKeyPointTypes::CenterKeyPoint);
	if (!geoF1)
		return false;
	Ptr<JointInput> jointInputPRF1 = joints->createInput(geoF1, geoPR2);
	if (!jointInputPRF1)
		return false;
	jointInputPRF1->isFlipped(false);
	jointInputPRF1->setAsRigidJointMotion();
	Ptr<Joint> jointPRF1 = joints->add(jointInputPRF1);
	if (!jointPRF1)
		return false;

	//Девятое соединение 
	Ptr<JointGeometry> geoTC2 = JointGeometry::createByCurve(edgesTC->item(40), JointKeyPointTypes::CenterKeyPoint);
	if (!geoTC2)
		return false;
	Ptr<JointGeometry> geoRG1 = JointGeometry::createByCurve(edgesRG->item(3), JointKeyPointTypes::CenterKeyPoint);
	if (!geoRG1)
		return false;
	Ptr<JointInput> jointInputTCRG1 = joints->createInput(geoRG1, geoTC2);
	if (!jointInputTCRG1)
		return false;
	jointInputTCRG1->isFlipped(false);
	jointInputTCRG1->setAsRigidJointMotion();
	Ptr<Joint> jointTCRG1 = joints->add(jointInputTCRG1);
	if (!jointTCRG1)
		return false;
	
	//Десятое соединение
	Ptr<JointGeometry> geoRG2 = JointGeometry::createByCurve(edgesRG->item(1), JointKeyPointTypes::CenterKeyPoint);
	if (!geoRG2)
		return false;
	Ptr<JointGeometry> geoRGS = JointGeometry::createByCurve(edgesRGS->item(0), JointKeyPointTypes::CenterKeyPoint);
	if (!geoRGS)
		return false;
	Ptr<JointInput> jointInputRGRGS = joints->createInput(geoRGS, geoRG2);
	if (!jointInputRGRGS)
		return false;
	jointInputRGRGS->isFlipped(true);
	jointInputRGRGS->setAsRigidJointMotion();
	Ptr<Joint> jointRGRGS = joints->add(jointInputRGRGS);
	if (!jointRGRGS)
		return false;

	//Одиннадцатое соединение
	Ptr<JointGeometry> geoTC3 = JointGeometry::createByCurve(edgesTC->item(42), JointKeyPointTypes::CenterKeyPoint);
	if (!geoTC3)
		return false;
	Ptr<JointGeometry> geoNGR = JointGeometry::createByCurve(edgesNGR->item(56), JointKeyPointTypes::CenterKeyPoint);
	if (!geoNGR)
		return false;
	Ptr<JointInput> jointInputTCNGR = joints->createInput(geoNGR, geoTC3);
	if (!jointInputTCNGR)
		return false;
	jointInputTCNGR->isFlipped(false);
	jointInputTCNGR->setAsRigidJointMotion();
	Ptr<Joint> jointTCNGR = joints->add(jointInputTCNGR);
	if (!jointTCNGR)
		return false;

	Ptr<JointGeometry> geoPRS = JointGeometry::createByNonPlanarFace(facesPR->item(6), JointKeyPointTypes::MiddleKeyPoint);
	if (!geoPRS) return false;
	Ptr<JointGeometry> geoNRS = JointGeometry::createByCurve(edgesNGR->item(1), JointKeyPointTypes::CenterKeyPoint);
	if (!geoNRS) return false;

	Ptr<JointInput> jointInputPRNRS = joints->createInput(geoPRS, geoNRS);
	if (!jointInputPRNRS) return false;

	jointInputPRNRS->isFlipped(true);
	jointInputPRNRS->setAsSliderJointMotion(ZAxisJointDirection);

	Ptr<Joint> jointPRNRS = joints->add(jointInputPRNRS);
	if (!jointPRNRS) return false;

	Ptr<SliderJointMotion> sliderMotion = jointPRNRS->jointMotion();
	if (!sliderMotion) return false;
	Ptr<JointLimits> limits = sliderMotion->slideLimits();
	if (!limits) return false;
	limits->isRestValueEnabled(true);
	limits->restValue(0.0);
	limits->isMinimumValueEnabled(true);
	limits->minimumValue(-9.5);
	limits->isMaximumValueEnabled(true);
	limits->maximumValue(22.5);


	Ptr<JointGeometry> geoB1 = JointGeometry::createByCurve(edgesB1->item(1), JointKeyPointTypes::CenterKeyPoint);
	if (!geoB1)
		return false;

	Ptr<JointGeometry> geoF2 = JointGeometry::createByCurve(edgesF->item(3), JointKeyPointTypes::CenterKeyPoint);
	if (!geoF2)
		return false;

	Ptr<JointInput> jointInputB1F2 = joints->createInput(geoB1, geoF2);
	if (!jointInputB1F2)
		return false;

	jointInputB1F2->isFlipped(false);
	jointInputB1F2->setAsRigidJointMotion();

	Ptr<Joint> jointB1F2 = joints->add(jointInputB1F2);
	if (!jointB1F2)
		return false;


	Ptr<JointGeometry> geoB2 = JointGeometry::createByCurve(edgesB2->item(1), JointKeyPointTypes::CenterKeyPoint);
	if (!geoB2)
		return false;

	Ptr<JointGeometry> geoLC2 = JointGeometry::createByCurve(edgesLC->item(55), JointKeyPointTypes::CenterKeyPoint);
	if (!geoLC2)
		return false;

	Ptr<JointInput> jointInputB2LC2 = joints->createInput(geoB2, geoLC2);
	if (!jointInputB2LC2)
		return false;

	jointInputB2LC2->isFlipped(false);
	jointInputB2LC2->setAsRigidJointMotion();

	Ptr<Joint> jointB2LC2 = joints->add(jointInputB2LC2);
	if (!jointB2LC2)
		return false;

	Ptr<JointGeometry> geoTC4 = JointGeometry::createByCurve(edgesTC->item(9), JointKeyPointTypes::CenterKeyPoint);
	if (!geoTC4)
		return false;

	Ptr<JointGeometry> geoTB1 = JointGeometry::createByCurve(edgesTB->item(3), JointKeyPointTypes::CenterKeyPoint);
	if (!geoTB1)
		return false;

	Ptr<JointInput> jointInputTCTB1 = joints->createInput(geoTB1, geoTC4);
	if (!jointInputTCTB1)
		return false;

	Ptr<ValueInput> offsetTCTB1 = ValueInput::createByString("-15 mm");
	if (!offsetTCTB1)
		return false;
	jointInputTCTB1->offset(offsetTCTB1);
	jointInputTCTB1->isFlipped(false);
	jointInputTCTB1->setAsRigidJointMotion();

	Ptr<Joint> jointTCTB1 = joints->add(jointInputTCTB1);
	if (!jointTCTB1)
		return false;

	Ptr<Features> features = rootComp->features();
	if (!features) return false;

	Ptr<ObjectCollection> inputEntitesTB4 = ObjectCollection::create();
	if (!inputEntitesTB4) return false;

	inputEntitesTB4->add(bodyTB);

	Ptr<ConstructionAxis> yAxis = rootComp->yConstructionAxis();
	if (!yAxis) return false;
	Ptr<ConstructionAxis> zAxis = rootComp->zConstructionAxis();
	if (!zAxis) return false;

	Ptr<ValueInput> quantityOneTB4 = ValueInput::createByString("2");
	if (!quantityOneTB4) return false;
	Ptr<ValueInput> distanceOneTB4 = ValueInput::createByString("-124 mm");
	if (!distanceOneTB4) return false;
	Ptr<ValueInput> quantityTwoTB4 = ValueInput::createByString("2");
	if (!quantityTwoTB4) return false;
	Ptr<ValueInput> distanceTwoTB4 = ValueInput::createByString("-124 mm");
	if (!distanceTwoTB4) return false;

	Ptr<RectangularPatternFeatures> rectangularPatternTB4 = features->rectangularPatternFeatures();
	if (!rectangularPatternTB4) return false;
	Ptr<RectangularPatternFeatureInput> rectangularPatternInputTB4 = rectangularPatternTB4->createInput(inputEntitesTB4, yAxis, quantityOneTB4, distanceOneTB4, PatternDistanceType::SpacingPatternDistanceType);
	if (!rectangularPatternInputTB4) return false;

	rectangularPatternInputTB4->setDirectionTwo(zAxis, quantityTwoTB4, distanceTwoTB4);

	Ptr<RectangularPatternFeature> rectangularFeatureTB4 = rectangularPatternTB4->add(rectangularPatternInputTB4);
	if (!rectangularFeatureTB4) return false;

	Ptr<JointGeometry> geoTC5 = JointGeometry::createByCurve(edgesTC->item(9), JointKeyPointTypes::CenterKeyPoint);
	if (!geoTC5)
		return false;

	Ptr<JointGeometry> geoTBN = JointGeometry::createByCurve(edgesTBN->item(51), JointKeyPointTypes::CenterKeyPoint);
	if (!geoTBN)
		return false;

	Ptr<JointInput> jointInputTCTBN = joints->createInput(geoTBN, geoTC5);
	if (!jointInputTCTBN)
		return false;

	jointInputTCTBN->isFlipped(true);
	jointInputTCTBN->setAsRigidJointMotion();

	Ptr<Joint> jointTCTBN = joints->add(jointInputTCTBN);
	if (!jointTCTBN) return false;

	Ptr<ObjectCollection> inputEntitesTBN1 = ObjectCollection::create();
	if (!inputEntitesTBN1) return false;

	inputEntitesTBN1->add(bodyTBN);
	
	Ptr<ValueInput> quantityOneTBN1 = ValueInput::createByString("2");
	if (!quantityOneTBN1)
		return false;
	Ptr<ValueInput> distanceOneTBN1 = ValueInput::createByString("-124 mm");
	if (!distanceOneTBN1)
		return false;
	Ptr<ValueInput> quantityTwoTBN1 = ValueInput::createByString("2");
	if (!quantityTwoTBN1)
		return false;
	Ptr<ValueInput> distanceTwoTBN1 = ValueInput::createByString("-124 mm");
	if (!distanceTwoTBN1)
		return false;

	Ptr<RectangularPatternFeatures> rectangularPatternTBN1 = features->rectangularPatternFeatures();
	if (!rectangularPatternTBN1) return false;
	Ptr<RectangularPatternFeatureInput> rectangularPatternInputTBN1 = rectangularPatternTBN1->createInput(inputEntitesTBN1, yAxis, quantityOneTBN1, distanceOneTBN1, PatternDistanceType::SpacingPatternDistanceType);
	if (!rectangularPatternInputTBN1) return false;

	rectangularPatternInputTBN1->setDirectionTwo(zAxis, quantityTwoTBN1, distanceTwoTBN1);

	Ptr<RectangularPatternFeature> rectangularFeatureTBN1 = rectangularPatternTBN1->add(rectangularPatternInputTBN1);
	if (!rectangularFeatureTBN1) return false;

	Ptr<ConstructionPlanes> planes = rootComp->constructionPlanes();
	if (!planes) return false;

	Ptr<ConstructionPlaneInput> planeInput = planes->createInput();
	if (!planeInput) return false;

	planeInput->setByTwoPlanes(facesTC->item(2), facesLC->item(27));

	Ptr<ConstructionPlane> plane = planes->add(planeInput);
	if (!plane) return false;

	Ptr<ObjectCollection> inputEntites = ObjectCollection::create();
	if (!inputEntites) return false;

	inputEntites->add(occurrences->item(17));

	Ptr<MirrorFeatures> mirrorFeatures = features->mirrorFeatures();
	if (!mirrorFeatures)
		return false;
	Ptr<MirrorFeatureInput> mirrorInput = mirrorFeatures->createInput(inputEntites, plane);
	if (!mirrorInput)
		return false;

	Ptr<MirrorFeature> mirrorFeature = mirrorFeatures->add(mirrorInput);
	if (!mirrorFeature)
		return false;

	plane->isLightBulbOn(false);

	if (!doc->saveAs("Hydraulic Cylinder", folder, "description", "tag")) return false;


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
