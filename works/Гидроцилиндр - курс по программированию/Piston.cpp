
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

	//Указатель на документ
	Ptr<Documents> docs = app->documents();
	if (!docs) return false;
	Ptr<Document> doc = docs->add(DocumentTypes::FusionDesignDocumentType);
	if (!doc) return false;
	// Указатели на инструменты из текущего документа
	Ptr<Design> design = app->activeProduct();
	if (!design) return false;
	//Указатель на компонент
	Ptr<Component> rootComp = design->rootComponent();
	if (!rootComp) return false;
	//Указатель на элемент
	Ptr<Features> features = rootComp->features();
	if (!features) return false;
	//Указатель на эскиз
	Ptr<Sketches> sketches = rootComp->sketches();
	if (!sketches) return false;
	// Указатель на выдавливание
	Ptr<ExtrudeFeatures> extrudes = features->extrudeFeatures();
	if (!extrudes) return false;
	//Указатель на создание резьбы
	Ptr<ThreadFeatures> threadFeatures = features->threadFeatures();
	if (!threadFeatures)return false;
	//Указатель на создание массива
	Ptr<RectangularPatternFeatures> rectangularPatterns = features -> rectangularPatternFeatures();
	if (!rectangularPatterns)return false;

	//Добавляем переменные для создания детали (Piston)
	double radiusCylinderInternal = 1.5; //радиус внутренний окружности цилиндра для создания детали(Piston) (cm)
	double radiusCylinderExternal = 6.5; //радиус внешней окружности цилиндра для создания детали(Piston) (cm)
	double distanceCylinder = 5.7; //расстояние выдавливания цилиндра детали (Piston) (cm)
	double distanceoffsetPlanes = 5.4; //расстояние смещения новой рабочей плоскости детали(Piston) (cm)
	double radiusLintelInternal = 6.5; //радиус внутренний окружности перемычки для создания детали(Piston) (cm)
	double radiusLintelExternal = 7.0; //радиус внешней окружности перемычки для создания детали(Piston) (cm)
	double distanceLintel = -0.9; //расстояние выдавливания перемычки детали (Piston) (cm)
	double quantityOne = 3; //Количество перемычек прямоугольного массива детали (Piston)
	double distanceOne = -4.2;//Расстояние между перемычками прямоугольного массива детали

	// Создание точки в центре координат
	Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
	if (!centerPoint) return false;
	//Первый этап создания детали (Piston) - создание эскиза цилиндра
	//Выбираем рабочую плоскость
	Ptr<Sketch> sketchCylinder = sketches->add(rootComp->xYConstructionPlane());
	if (!sketchCylinder)
		return false;
	// Создание вхождени элемента окружность
	Ptr<SketchCurves> sketchCurvesCylinder = sketchCylinder->sketchCurves();
	if (!sketchCurvesCylinder)
		return false;
	//Выбираем построение эскиза окружности
	Ptr<SketchCircles> sketchCircles = sketchCurvesCylinder->sketchCircles();
	if (!sketchCircles)
		return false;
	//Создание окружности методом построения точки в центре координат и радиуса окружности
	sketchCircles->addByCenterRadius(centerPoint, radiusCylinderInternal);
	sketchCircles->addByCenterRadius(centerPoint, radiusCylinderExternal);
	//Конец первого этапа создания детали (Piston) - создание эскиза цилиндра

	//Второй этап создания детали (Piston) - выдавливание эскиза цилиндра
	//Создание профиля для выдавливания
	Ptr<Profiles> profilesCylinder = sketchCylinder->profiles();
	if (!profilesCylinder)
		return false;
	//Выбор профиля для выдавливания
	Ptr<Profile> profileCylinder = profilesCylinder->item(1);
	if (!profileCylinder)
		return false;
	//Выдавливание с операцией создания нового тела
	Ptr<ExtrudeFeatureInput> extrudeCylinder = extrudes->createInput(profileCylinder,
		NewBodyFeatureOperation);
	if (!extrudeCylinder)
		return false;
	//Указываем направление выдавливания и расстояние
	extrudeCylinder->setDistanceExtent(false, ValueInput::createByReal(distanceCylinder));
	//Выбор твердого тела
	extrudeCylinder->isSolid(true);
	//Создание выдавливания выдавливание эскиза цилиндра
	Ptr<ExtrudeFeature> ext = extrudes->add(extrudeCylinder);
	if (!ext) return false;
	//Конец второго этапа создания детали (Piston) - выдавливание эскиза цилиндра

	//Третий этап создания детали (Piston) - создание дополнительной плоскости
	//Добавляем новую рабочую плоскость
	Ptr<ConstructionPlanes> ctorPlanes = rootComp->constructionPlanes();
	if (!ctorPlanes) return false;
	// Создание допполнительной плоскости
	Ptr<ConstructionPlaneInput> ctorPlaneInput = ctorPlanes->createInput();
	if (!ctorPlaneInput) return false;
	//Определяем смещение новой рабочий плоскости
	Ptr<ValueInput> offsetPlanes = ValueInput::createByReal(distanceoffsetPlanes);
	if (!offsetPlanes) return false;
	//Указываем плоскость и расстояние её смещения
	bool retPlane = ctorPlaneInput->setByOffset(rootComp->xYConstructionPlane(),
		offsetPlanes);
	if (!retPlane) return false;
	//Создаем новую рабочую плоскость
	Ptr<ConstructionPlane> ctorPlane = ctorPlanes->add(ctorPlaneInput);
	if (!ctorPlane) return false;

	//Четвертый этап создания детали (Piston) - создание эскиза перемычки
	//Выбор рабочей плоскости
	Ptr<Sketch> sketchLintel = sketches->add(ctorPlane);
	if (!sketchLintel) return false;
	// Создание вхождени элемента шлиц
	Ptr<SketchCurves> sketchCurvesLintel = sketchLintel->sketchCurves();
	if (!sketchCurvesLintel) return false;
	//Выбираем построение эскиза окружности для перемычки
	Ptr<SketchCircles> sketchCirclesLintel = sketchCurvesLintel->sketchCircles();
	if (!sketchCirclesLintel) return false;
	//Создаем окружности для перемычки, методом точки в центре координат и радиуса окружности
	sketchCirclesLintel->addByCenterRadius(centerPoint, radiusLintelInternal);
	sketchCirclesLintel->addByCenterRadius(centerPoint, radiusLintelExternal);
	//Конец четвертого этапа создания детали (Piston) - создание эскиза перемычки

	//Пятый этап создания детали (Piston) - выдавливание эскиза перемычки
	//Создание профиля для выдавливания
	Ptr<Profiles> profilesLintel = sketchLintel->profiles();
	if (!profilesLintel) return false;
	//Выбор профиля для выдавливания перемычки
	Ptr<Profile> profileLintel = profilesLintel->item(1);
	if (!profileLintel) return false;
	//Выдавливание с операцией присоединения
	Ptr<ExtrudeFeatureInput> extFeatureLintel = extrudes->createInput(profileLintel,
		FeatureOperations::JoinFeatureOperation);
	//Указываем направление выдавливания и расстояние
	extFeatureLintel->setDistanceExtent(false, ValueInput::createByReal(distanceLintel));
	//Выбор твердого тела
	extFeatureLintel->isSolid(true);
	//Создание выдавливания перемычки
	Ptr<ExtrudeFeature> extLintel = extrudes->add(extFeatureLintel);
	if (!extLintel) return false;
	// Конец пятого этапа создания детали (Piston) - выдавливание эскиза перемычки

	Ptr<BRepBodies> bodies = rootComp->bRepBodies();
	if (!bodies)
		return false;
	//Выбор тела для создания прямоугольного массива
	Ptr<BRepBody> body = bodies->item(0);
	if (!body)
		return false;
	//Создание грани для прямоугольного массива
	Ptr<BRepFaces> faces = body->faces();
	if (!faces)
		return false;
	// Создание входных объектов для прямоугольного массива
	Ptr<ObjectCollection> faceCollection = ObjectCollection::create();
	if (!faceCollection)
		return false;
	//Выбор граней для прямоугольного массива
	faceCollection->add(faces->item(0));
	faceCollection->add(faces->item(1));
	faceCollection->add(faces->item(2));
	//Создаем дополнительные ось Z для прямоугольного массива
	Ptr<ConstructionAxis> zAxis = rootComp->zConstructionAxis();
	if (!zAxis)
		return false;
	//Создаем прямоугольный массив для перемычки
	Ptr<RectangularPatternFeatureInput> rectangularPatternInput = rectangularPatterns->createInput(faceCollection, zAxis,
	ValueInput::createByReal(quantityOne), ValueInput::createByReal(distanceOne),
	PatternDistanceType::ExtentPatternDistanceType);
	if (!rectangularPatternInput)
		return false;
	// Создание прямоугольного массива
	Ptr<RectangularPatternFeature> rectangularFeature = rectangularPatterns-> add(rectangularPatternInput);
	if (!rectangularFeature)
		return false;


	Ptr<DataHub> hub = app->data()->activeHub();
	if (!hub) return false;
	Ptr<DataProjects> projects = hub->dataProjects();
	if (!projects) return false;
	Ptr<DataProject> project = nullptr;
	for (Ptr<DataProject>& proj : projects) {

		if (proj->name() == "Hydraulic Cylinder") 
		{
			project = proj;
			break;
		}
	}

	if (!project) return false;
	Ptr<DataFolder> folder = project->rootFolder();
	if (!folder) return false;

	if (!doc->saveAs("Piston", folder, "description", "tag")) return false;

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
