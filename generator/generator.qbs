import qbs
import qbs.Probes

Product {
    type: "application"
    name: "generator"
    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: ["core", "network"] }

    cpp.cxxLanguageVersion: "c++11"
    cpp.dynamicLibraries: {
        var dynamicLibraries = base;
        return dynamicLibraries;
    }

    cpp.includePaths : {
        var includePaths = base;
        return includePaths;
    }

    files: [
        "main.cpp",
        "Generator.cpp",
        "Generator.hpp",
    ]
}
