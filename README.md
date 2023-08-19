# Hogwarts Legacy C++ Mod Examples

## Setup

### Cloning (and pulling)

1. Clone this repo
2. `git submodule update --init --recursive` (Make sure your Github account is linked to your Epic Games account for UE source access.)

*When pulling new changes, run step `2` again*

### Code Editor

There are a few choices for opening the project in Visual Studio, you can either generate Visual Studio 2022 project files **OR** Install the [CMake Plugin](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170) for Visual Studio (I found this much easier).

If you want to use the first, following the [UE4SS Documentation](https://docs.ue4ss.com/guides/creating-a-c++-mod.html) open a command prompt in the cloned directory and run `cmake -S . -G "Visual Studio 17 2022" -B Output` then open `Output/HLCPPTutorial.sln`

Alternatively, if you have CLion, just open the folder

## Building / Running Notes
If you're mod seems to cause a crash on load for no reason, try building UE4SS youreself and using those dlls instead of the official release.

The output files of mods will be in `Output/Mods/<ModName>/Debug` or `Output/Mods/<ModName>/Release`

Then in the `Mods` folder of your UE4SS install create a folder with the same name as the mod, and then inside, an empty file called `enabled.txt` and a folder called `dlls`, place the built files in the `dlls` folder.