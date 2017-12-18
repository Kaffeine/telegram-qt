import qbs
import "../../Generator.qbs" as Generator

Generator {
    Depends { name: "Qt"; submodules: ["core", "network", "test"] }
    type: "application"
    name: "tst_generator"
    files: name + ".cpp"
}
