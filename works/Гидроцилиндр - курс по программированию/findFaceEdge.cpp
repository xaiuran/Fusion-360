
#include <Core/CoreAll.h>
#include <Fusion/FusionAll.h>
#include <CAM/CAMAll.h>

using namespace adsk::core;
using namespace adsk::fusion;
using namespace adsk::cam;

Ptr<Application> app;
Ptr<UserInterface> ui;

  class OnInputChangedEventHander : public adsk::core::InputChangedEventHandler
    {
    public:
        void notify(const Ptr<InputChangedEventArgs>& eventArgs) override;
    };

    class OnDestroyEventHandler : public adsk::core::CommandEventHandler
    {
    public:
        void notify(const Ptr<CommandEventArgs>& eventArgs) override;
    };

    class CommandCreatedFinderEventHandler : public adsk::core::CommandCreatedEventHandler
    {
    public:
        void notify(const Ptr<CommandCreatedEventArgs>& eventArgs) override;
    private:
        OnDestroyEventHandler onDestroyHandler;
        OnInputChangedEventHander onInputChangedHandler;
    } _cmdCreatedHandler;


extern "C" XI_EXPORT bool run(const char* context)
    {
        app = Application::get();
        if (!app)
            return false;

        ui = app->userInterface();
        if (!ui)
            return false;

        Ptr<CommandDefinitions> commandDefinitions = ui->commandDefinitions();
        if (!commandDefinitions)
            return nullptr;

        Ptr<CommandDefinition> cmdDef = commandDefinitions->itemById("findFaceEdge");
        if (!cmdDef)
        {
            cmdDef = commandDefinitions->addButtonDefinition("findFaceEdge",
                "Find Edge & Face",
                "Helper for getting edges and faces indexes.");
        }

        Ptr<CommandCreatedEvent> commandCreatedEvent = cmdDef->commandCreated();
        if (!commandCreatedEvent)
            return false;

        commandCreatedEvent->add(&_cmdCreatedHandler);

        cmdDef->execute();

        adsk::autoTerminate(false);

        return true;
   }

    void CommandCreatedFinderEventHandler::notify(const Ptr<CommandCreatedEventArgs> & eventArgs)
   {
        if (eventArgs)
        {
            Ptr<Command> command = eventArgs->command();
            if (command)
            {
                command->cancelButtonText("Ok");
                command->isOKButtonVisible(false);

                Ptr<CommandEvent> onDestroy = command->destroy();
                if (!onDestroy)
                    return;
                bool isOk = onDestroy->add(&onDestroyHandler);
                if (!isOk)
                    return;

                Ptr<InputChangedEvent> onInputChanged = command->inputChanged();
                if (!onInputChanged)
                    return;

                isOk = onInputChanged->add(&onInputChangedHandler);
                if (!isOk)
                    return;

                Ptr<CommandInputs> inputs = command->commandInputs();
                if (!inputs)
                    return;

                Ptr<SelectionCommandInput> selectionInput = inputs->addSelectionInput("selection", "Select", "Select edge or face to be finded");
                if (!selectionInput)
                    return;
                selectionInput->setSelectionLimits(1, 1);

                Ptr<StringValueCommandInput> strTypeInput = inputs->addStringValueInput("stringType", "This is item : ", "");
                strTypeInput->isReadOnly(true);

                Ptr<StringValueCommandInput> strIndexInput = inputs->addStringValueInput("stringIndex", "index", "");
                strIndexInput->isReadOnly(true);
            }
        }
    }

    void OnInputChangedEventHander::notify(const Ptr<InputChangedEventArgs> & eventArgs)
 {
        Ptr<CommandInputs> inputs = eventArgs->inputs();
        if (!inputs)
            return;

        Ptr<CommandInput> cmdInput = eventArgs->input();
        if (!cmdInput)
            return;

        Ptr<SelectionCommandInput> selectionInput = inputs->itemById("selection");
        if (!selectionInput)
            return;

        Ptr<StringValueCommandInput> stringTypeInput = inputs->itemById("stringType");
        if (!stringTypeInput)
            return;

        Ptr<StringValueCommandInput> stringIndexInput = inputs->itemById("stringIndex");
        if (!stringIndexInput)
            return;

        if (cmdInput->id() == "selection")
        {
            auto selection = selectionInput->selection(0);
            if (!selection)
                return;

            Ptr<Base> selectedEnt = selection->entity();
            if (!selectedEnt)
                return;

            if (selectedEnt->objectType() == BRepEdge::classType())
            {
                Ptr<BRepEdge> edge = selectedEnt;
                auto edges = edge->body()->edges();
                std::size_t count = edges->count();
                for (std::size_t i = 0; i < count; ++i)
                {
                    if (edge == edges->item(i))
                    {
                        stringTypeInput->value("Edge");
                        stringIndexInput->value(std::to_string(i));
                        break;
                    }
                }
            }
            else if (selectedEnt->objectType() == BRepFace::classType())
            {
                Ptr<BRepFace> face = selectedEnt;
                auto faces = face->body()->faces();
                std::size_t count = faces->count();
                for (std::size_t i = 0; i < count; ++i)
                {
                    if (face == faces->item(i))
                    {
                        stringTypeInput->value("Face");
                        stringIndexInput->value(std::to_string(i));
                        break;
                    }
                }
            }
            else
            {
                stringTypeInput->value("");
                stringIndexInput->value("");
            }
        }
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
