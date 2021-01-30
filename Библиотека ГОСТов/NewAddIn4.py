#Author-
#Description-

import adsk.core, adsk.fusion, adsk.cam, traceback

handlers = []
app = adsk.core.Application.get()
ui  = app.userInterface

def run(context):
    ui = None
    try:
        app = adsk.core.Application.get()
        ui  = app.userInterface
        ui.messageBox('Hello addin')
        workSpace = ui.workspaces.itemById('FusionSolidEnvironment')
        tbPanels = workSpace.toolbarPanels
                

        tbPanel = tbPanels.itemById('NewPanel')
        if tbPanel:
            tbPanel.deleteMe()
        tbPanel = tbPanels.add('NewPanel', 'Библиотека гостов', 'SelectPanel', False)
        cmdDef = ui.commandDefinitions.itemById('NewCommand')
        if cmdDef:
            cmdDef.deleteMe()
        cmdDef = ui.commandDefinitions.addButtonDefinition('NewCommand', 'Добавить деталь', 'Добавляет новую деталь','.//resource')
        tbPanel.controls.addCommand(cmdDef)
           # Connect to the command created event.
        sampleCommandCreated = SampleCommandCreatedEventHandler()
        cmdDef.commandCreated.add(sampleCommandCreated)
        handlers.append(sampleCommandCreated)
    except:
        if ui:
            ui.messageBox('Failed:\n{}'.format(traceback.format_exc()))
# Event handler for the commandCreated event.
class SampleCommandCreatedEventHandler(adsk.core.CommandCreatedEventHandler):
    def __init__(self):
        super().__init__()
    def notify(self, args):
        eventArgs = adsk.core.CommandCreatedEventArgs.cast(args)
        cmd = eventArgs.command

        # Connect to the execute event.
        onExecute = SampleCommandExecuteHandler()
        cmd.execute.add(onExecute)
        handlers.append(onExecute)


# Event handler for the execute event.
class SampleCommandExecuteHandler(adsk.core.CommandEventHandler):
    def __init__(self):
        super().__init__()
    def notify(self, args):
        try:
            app = adsk.core.Application.get()
            ui  = app.userInterface
            # Create and display the palette.
            palette = ui.palettes.itemById('myExport')
            if palette:
                palette.deleteMe()
            if not palette:
                #make the [close] button invisible
                palette = ui.palettes.add('myExport', 'Библиотека Гостов', 'Test.html', True, True, True, 800, 200)

                # Dock the palette to the right side of Fusion window.
                palette.dockingState = adsk.core.PaletteDockingStates.PaletteDockStateRight
    
                # Add handler to HTMLEvent of the palette.
                # onHTMLEvent = MyHTMLEventHandler()
                # palette.incomingFromHTML.add(onHTMLEvent)   
                # handlers.append(onHTMLEvent)
    
                
                # Add handler to CloseEvent of the palette.
                #onClosed = MyCloseEventHandler()
                #palette.closed.add(onClosed)
                #handlers.append(onClosed) 
            else: 
                palette.isVisible = True  
        except:
            _ui.messageBox('Command executed failed: {}'.format(traceback.format_exc()))

   
    
        
def stop(context):
    ui = None
    try:
        
        ui.messageBox('Stop addin')

    except:
        if ui:
            ui.messageBox('Failed:\n{}'.format(traceback.format_exc()))
