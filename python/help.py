from audio import playSoundByFilename


help_dict = {
    "main": "",
    "units_tests": "",
    "unit": "",
    "test": "",
    "notes": "",
    "alphabet": "",
    "clock": "",
    "calculator": "",
}


def instantHelp(menuID):
    playSoundByFilename(help_dict[menuID])
