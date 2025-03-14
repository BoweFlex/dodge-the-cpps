# Dodge the CPPs

A very basic 2d game, reimplementing Godot's [Dodge the Creeps](https://github.com/godotengine/godot-demo-projects/tree/master/2d/dodge_the_creeps) demo but in C++ rather than GDScript.

## Setup

To compile the game, scons must be installed (this is handled by direnv if you have that installed). You can run the following to compile the `src/` folder, as well as the godot-cpp library if it is not already compiled.

```bash
scons platform=linux

# If you want to use Clang for compilation rather than g++
scons platform=linux use_llvm=yes
```

If you are compiling for the first time and want to use ClangD as an LSP, you need to generate a `compile_commands.json`. Otherwise, objects and include statements from the GDExtension will not be recognized. To generate this file:

```bash
scons platform=linux use_llvm=yes compiledb=yes
```

This will create the `compile_commands.json`, make sure that it is in the root directory of the project.
