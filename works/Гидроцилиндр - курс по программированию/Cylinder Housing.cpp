
#include <Core/CoreAll.h>
#include <Fusion/FusionAll.h>
#include <CAM/CAMAll.h>

using namespace adsk::core;
using namespace adsk::fusion;

Ptr<Application> app;
Ptr<UserInterface> ui;

Ptr<ValueCommandInput> _strHoleDiametr;
Ptr<ValueCommandInput> _strDiametr;
Ptr<ValueCommandInput> _strDistance;
Ptr<ImageCommandInput> _img;

class OnInputChangedEventHander : public adsk::core::InputChangedEventHandler
{
public:
    void notify(const Ptr<InputChangedEventArgs>& eventArgs) override;

};
// обработчик события CommandExecute
class CommandExecuteEventHandler : public adsk::core::CommandEventHandler
{
public:
    void notify(const Ptr<CommandEventArgs>& eventArgs) override;

};

//обработчик события CommandDestroyed
class OnDestroyEventHandler : public adsk::core::CommandEventHandler
{
public:
    void notify(const Ptr<CommandEventArgs>& eventArgs) override;
};


// обработчик событий CommandCreated
class CommandCreatedFinderEventHandler : public adsk::core::CommandCreatedEventHandler
{
public:
    void notify(const Ptr<CommandCreatedEventArgs>& eventArgs) override;
private:
    OnDestroyEventHandler onDestroyHandler;
    CommandExecuteEventHandler gearCommandExecute;
} _cmdCreatedHandler;

extern "C" XI_EXPORT bool run(const char* context)
{
    app = Application::get();
    if (!app)
        return false;

    ui = app->userInterface();
    if (!ui)
        return false;

    //Получить команду, которая была создана.
    Ptr<CommandDefinitions> commandDefinitions = ui->commandDefinitions();
    if (!commandDefinitions)
        return nullptr;

    // Получить существующее  команды или создать его, если он еще не существует.
    Ptr<CommandDefinition> cmdDef = commandDefinitions->itemById("cmdDetails");
    if (!cmdDef)
    {
        cmdDef = commandDefinitions->addButtonDefinition("cmdDetails",
            "Cylinder",
            "Create details.");
    }

    //Подключитесь к команде созданного события
    Ptr<CommandCreatedEvent> commandCreatedEvent = cmdDef->commandCreated();
    if (!commandCreatedEvent)
        return false;

    commandCreatedEvent->add(&_cmdCreatedHandler);

    //Выполните определение команды.
    cmdDef->execute();

    //Предотвратите завершение работы этого модуля при возврате
    adsk::autoTerminate(false);

    return true;
}

// обработчик событий CommandCreated
void CommandCreatedFinderEventHandler::notify(const Ptr<CommandCreatedEventArgs>& eventArgs)
{
    if (eventArgs)
    {
        //  Получить команду, которая была создана
        Ptr<Command> command = eventArgs->command();
        if (command)
        {


            // Подключиться к команде уничтожено событие.
            Ptr<CommandEvent> onDestroy = command->destroy();
            if (!onDestroy)
                return;
            bool isOk = onDestroy->add(&onDestroyHandler);
            if (!isOk)
                return;

            // Подключитесь к входу измененного события
            Ptr<InputChangedEvent> onInputChanged = command->inputChanged();
            if (!onInputChanged)
                return;



            //  Получить коллекцию CommandInputs, связанную с командой.
            Ptr<CommandInputs> inputs = command->commandInputs();
            if (!inputs)
                return;


            Ptr<CommandEvent> executeEvent = command->execute();
            if (!executeEvent)
                return;
            isOk = executeEvent->add(&gearCommandExecute);
            if (!isOk)
                return;
            //Объявление переменных
            double holeDiam = _strHoleDiametr; // радиус внутренней окружности для создания детали (Cylinder Housing) (cm)
            double Diam = _strDiametr;  // радиус внешней окружности для создания детали (Cylinder Housing) (cm)
            double Distance = _strDistance;  // расстояние выдавливания для создания детали (Cylinder Housing) (cm)


            //Созданть изображение в команду
            _img = inputs->addImageCommandInput("Cylinder", "", "C:/Users/User/AppData/Roaming/Autodesk/Autodesk Fusion 360/API/Scripts/Cylinder Housing/Cylinder.png");
            if (!_img)
                return;

            //Создать текстовое поле только для чтения.
            Ptr<TextBoxCommandInput> text = inputs->addTextBoxCommandInput("textBox", "", "Enter an outside diameter greater than 0.", 2, true);
            if (!text)
                return;

            //Создание ввода  значения
            _strDiametr = inputs->addValueInput("Diam", "Diameter (mm)", "mm", ValueInput::createByReal(Diam));
            if (!_strDiametr)
                return;
            // Создать текстовое поле только для чтения.
            Ptr<TextBoxCommandInput> text1 = inputs->addTextBoxCommandInput("textBox", "", "Enter an inside diameter greater than 0", 2, true);
            if (!text1)
                return;
            // Создание ввода  значения
            _strHoleDiametr = inputs->addValueInput("holeDiam", "Hole Diameter (mm)", "mm", ValueInput::createByReal(holeDiam));
            if (!_strHoleDiametr)
                return;
            //Создать текстовое поле только для чтения.
            Ptr<TextBoxCommandInput> text2 = inputs->addTextBoxCommandInput("textBox", "", "Indicate the extrusion distance not equal 0 ", 2, true);
            if (!text2)
                return;
            //Создание ввода  значения
            _strDistance = inputs->addValueInput("Distance", "Distance (mm)", "mm", ValueInput::createByReal(Distance));
            if (!_strDistance)
                return;



        }
    }
}

//Обработчик события CommandExecute
void CommandExecuteEventHandler::notify(const Ptr<CommandEventArgs>& eventArgs)
{

    //Указатель на документ
    Ptr<Documents> docs = app->documents();
    if (!docs) return;

    Ptr<Document> doc = docs->add(DocumentTypes::FusionDesignDocumentType);
    if (!doc) return;


    // Указатели на инстурменты из текущего документа
    Ptr<Design> design = app->activeProduct();
    if (!design) return;
    //Указатель на компонент
    Ptr<Component> rootComp = design->rootComponent();
    if (!rootComp) return;
    //Указатель на элемент
    Ptr<Features> features = rootComp->features();
    if (!features) return;
    //Указатель на эскиз
    Ptr<Sketches> sketches = rootComp->sketches();
    if (!sketches) return;
    // Указатель на выдавливание
    Ptr<ExtrudeFeatures> extrudes = features->extrudeFeatures();
    if (!extrudes) return;


    double holeDiam = _strHoleDiametr->value();
    double Diam = _strDiametr->value();
    double Distance = _strDistance->value();
    //Проверка на ввод параметров
    if ((holeDiam <= 0) || (Diam <= 0) || (Distance == 0))
    {
        ui->messageBox("Input error");
    }
    else
    {


        Ptr<Point3D> centerPoint = Point3D::create(0, 0, 0);
        if (!centerPoint) return;

        //Создание детали
        //Выбираем рабочую плоскость
        Ptr<Sketch> sketchInternal = sketches->add(rootComp->yZConstructionPlane());
        if (!sketchInternal) return;
        // Создание вхождени элемента окружность
        Ptr<SketchCurves> sketchCurvesInternal = sketchInternal->sketchCurves();
        if (!sketchCurvesInternal) return;
        //Выбираем построение эскиза окружности
        Ptr<SketchCircles> sketchCirclesInternal = sketchCurvesInternal->sketchCircles();
        if (!sketchCirclesInternal) return;


        sketchCirclesInternal->addByCenterRadius(centerPoint, holeDiam / 2);
        sketchCirclesInternal->addByCenterRadius(centerPoint, Diam / 2);

        //Создание профиля для выдавливания
        Ptr<Profiles> profilesInternal = sketchInternal->profiles();
        if (!profilesInternal) return;

        //Выбор профиля для выдавливания ограниченного двумя окружностями с одним центром
        Ptr<Profile> profileInternal = profilesInternal->item(1);
        if (!profileInternal) return;


        //Выдавливание с операцией создания нового тела
        Ptr<ExtrudeFeatureInput> extFeatureInternal = extrudes->createInput(profileInternal, FeatureOperations::NewBodyFeatureOperation);


        //Направление выдавливания
        extFeatureInternal->setDistanceExtent(true, ValueInput::createByReal(Distance));

        //Выбор твердого тела
        extFeatureInternal->isSolid(true);

        Ptr<ExtrudeFeature> extInternal = extrudes->add(extFeatureInternal);
        if (!extInternal) return;
        // Конец выдавливания  профиля
        //Конец создания детали
    }
    // Создание точки в центре координат


    holeDiam = _strHoleDiametr->value();
    Diam = _strDiametr->value();
    Distance = _strDistance->value();
}

void OnDestroyEventHandler::notify(const Ptr<CommandEventArgs>& eventArgs)
{
    adsk::terminate();
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
