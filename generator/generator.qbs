import qbs
import qbs.Probes

Product {
    type: "application"
    name: "generator"
    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: ["core", "network"] }

    Probes.PkgConfigProbe {
        id: zlibProbe
        name: "zlib"
    }

    cpp.cxxLanguageVersion: "c++11"
    cpp.dynamicLibraries: {
        var dynamicLibraries = base;
        dynamicLibraries += zlibProbe.libraries
        return dynamicLibraries;
    }

    cpp.includePaths : {
        var includePaths = base;
        includePaths += zlibProbe.includePaths
        return includePaths;
    }

    files: [
        "main.cpp",
        "Generator.cpp",
        "Generator.hpp",
    ]
}
