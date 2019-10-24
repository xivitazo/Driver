import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "/home/javi/Documents/of_v20190324_linux64gcc6_release/libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: '/home/javi/Documents/of_v20190324_linux64gcc6_release'

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }

        files: [
            "../src/Master/Link/Link.cpp",
            "../src/Master/Link/Link.h",
            "../src/Master/Link/LinkStack.cpp",
            "../src/Master/Link/LinkStack.h",
            "../src/Master/Master.cpp",
            "../src/Master/Master.h",
            "../src/Master/Matrix/Boton.cpp",
            "../src/Master/Matrix/Boton.h",
            "../src/Master/Matrix/MatrixMod.cpp",
            "../src/Master/Matrix/MatrixMod.h",
            "../src/Master/Matrix/Matriz.cpp",
            "../src/Master/Matrix/Matriz.h",
            "../src/Master/Matrix/Potenciometro.cpp",
            "../src/Master/Matrix/Potenciometro.h",
            "../src/Master/Modulos/AllAudioMod.h",
            "../src/Master/Modulos/AudioMod.cpp",
            "../src/Master/Modulos/AudioMod.h",
            "../src/Master/Modulos/Gain/GainMod.cpp",
            "../src/Master/Modulos/Gain/GainMod.h",
            "../src/Master/Modulos/Mixer/MixerMod.cpp",
            "../src/Master/Modulos/Mixer/MixerMod.h",
            "../src/Master/conexion.cpp",
            "../src/Master/conexion.h",
            "../src/main.cpp",
            "../src/ofApp.cpp",
            "../src/ofApp.h",
        ]

        of.addons: [

        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
        // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // create a console window when the application start
        consoleApplication: false

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
    // will compile OF only once for all your projects
    // otherwise compiled per project with qbs


    property bool precompileOfMain: false  // precompile ofMain.h
    // faster to recompile when including ofMain.h
    // but might use a lot of space per project

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
