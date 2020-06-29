
#include <Core/CoreAll.h>
#include <Fusion/FusionAll.h>
#include <CAM/CAMAll.h>
#include <map>

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

	Ptr<Application> app = Application::get();
	if (!app) return false;

	ui = app->userInterface();
	if (!ui) return false;

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

	Ptr<DataFile> dataFile;
	std::string fileName = "Hydraulic Cylinder";

	for (Ptr<DataFile>& datFil : files)
	{
		if (datFil->name() == fileName)
		{
			dataFile = datFil;
			break;
		}
	}

	Ptr<Occurrence>occur = occurrences->addByInsert(dataFile, Matrix3D::create(), false);
	if (!occur) return false;

	auto childsOccurrences = occur->childOccurrences();

	Ptr<MaterialLibraries> matLibs = app->materialLibraries();
	if (!matLibs)
		return false;
	Ptr<MaterialLibrary> lib = matLibs->itemByName("Fusion 360 Appearance Library");
	if (!lib)
		return false;
	Ptr<Appearances> libAppear = lib->appearances();
	if (!libAppear)
		return false;


	std::map < std::string, Ptr < Appearance >> apps;

	apps["Cylinder Glass"] = libAppear->itemByName("Glass - Light Color (Blue)");
	apps["Stainless Steel"] = libAppear->itemByName("Stainless Steel - Polished");
	apps["Rubber"] = libAppear->itemByName("Rubber - Hard");
	apps["Titanium"] = libAppear->itemByName("Titanium - Polished");
	apps["Galvanized"] = libAppear->itemByName("Steel - Galvanized (Small)");


	// Cylinder Housing
	childsOccurrences->item(0)->bRepBodies()->item(0)->appearance(apps["Cylinder Glass"]);

	// Backing Seal 1
	childsOccurrences->item(1)->bRepBodies()->item(0)->appearance(apps["Rubber"]);

	// Backing Seal 2
	childsOccurrences->item(2)->bRepBodies()->item(0)->appearance(apps["Rubber"]);

	// Top Cover
	childsOccurrences->item(3)->bRepBodies()->item(0)->appearance(apps["Stainless Steel"]);

	// Lower Cap
	childsOccurrences->item(4)->bRepBodies()->item(0)->appearance(apps["Stainless Steel"]);

	// Piston
	childsOccurrences->item(5)->bRepBodies()->item(0)->appearance(apps["Titanium"]);

	// Piston Seal 1
	childsOccurrences->item(6)->bRepBodies()->item(0)->appearance(apps["Rubber"]);

	// Piston Seal 2
	childsOccurrences->item(7)->bRepBodies()->item(0)->appearance(apps["Rubber"]);

	// Piston Rod
	childsOccurrences->item(8)->bRepBodies()->item(0)->appearance(apps["Titanium"]);

	// Rod Nut
	childsOccurrences->item(9)->bRepBodies()->item(0)->appearance(apps["Galvanized"]);

	// Fork
	childsOccurrences->item(10)->bRepBodies()->item(0)->appearance(apps["Stainless Steel"]);

	// Rod Guide
	childsOccurrences->item(11)->bRepBodies()->item(0)->appearance(apps["Titanium"]);

	// Rod Guide Seal
	childsOccurrences->item(12)->bRepBodies()->item(0)->appearance(apps["Rubber"]);

	// Nut Guide Rod
	childsOccurrences->item(13)->bRepBodies()->item(0)->appearance(apps["Galvanized"]);

	// Barrette 1
	childsOccurrences->item(14)->bRepBodies()->item(0)->appearance(apps["Galvanized"]);

	// Barrette 2
	childsOccurrences->item(15)->bRepBodies()->item(0)->appearance(apps["Galvanized"]);

	// Tension Bolt
	childsOccurrences->item(16)->bRepBodies()->item(0)->appearance(apps["Galvanized"]);
	childsOccurrences->item(16)->bRepBodies()->item(1)->appearance(apps["Galvanized"]);
	childsOccurrences->item(16)->bRepBodies()->item(2)->appearance(apps["Galvanized"]);
	childsOccurrences->item(16)->bRepBodies()->item(3)->appearance(apps["Galvanized"]);

	// Tension Bolt Nut
	childsOccurrences->item(17)->bRepBodies()->item(0)->appearance(apps["Galvanized"]);
	childsOccurrences->item(17)->bRepBodies()->item(1)->appearance(apps["Galvanized"]);
	childsOccurrences->item(17)->bRepBodies()->item(2)->appearance(apps["Galvanized"]);
	childsOccurrences->item(17)->bRepBodies()->item(3)->appearance(apps["Galvanized"]);

	// Tension Bolt Nut (Mirror)
	childsOccurrences->item(18)->bRepBodies()->item(0)->appearance(apps["Galvanized"]);
	childsOccurrences->item(18)->bRepBodies()->item(1)->appearance(apps["Galvanized"]);
	childsOccurrences->item(18)->bRepBodies()->item(2)->appearance(apps["Galvanized"]);
	childsOccurrences->item(18)->bRepBodies()->item(3)->appearance(apps["Galvanized"]);

	if (!doc->saveAs("Hydraulic Cylinder + Materials", folder, "description", "tag")) return false;

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
