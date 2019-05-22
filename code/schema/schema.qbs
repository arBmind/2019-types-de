import qbs

Project {
    minimumQbsVersion: "1.7.1"

    Product {
        name: "cpp17"

        Export {
            Depends { name: "cpp" }
            cpp.cxxLanguageVersion: "c++17"
            // cpp.cxxFlags: {
            //     if (qbs.toolchain.contains('msvc')) return ["/await", "/permissive-"];
            //     if (qbs.toolchain.contains('clang')) return ["-fcoroutines-ts"];
            // }
            // cpp.cxxStandardLibrary: {
            //     if (qbs.toolchain.contains('clang')) return "libc++";
            // }
            // cpp.staticLibraries: {
            //     if (qbs.toolchain.contains('clang')) return ["c++", "c++abi"];
            // }
        }
    }

    StaticLibrary {
        name: "schema"
        Depends { name: "cpp17" }
        files: [
            "Abstract.cpp",
            "Abstract.h",
            "Command.cpp",
            "Command.h",
            "Compute.cpp",
            "Compute.h",
            "NoAdlStorage.cpp",
            "NoAdlStorage.h",
            "PersonCompute.cpp",
            "PersonCompute.h",
            "PersonSchema.cpp",
            "PersonSchema.h",
            "Processor.cpp",
            "Processor.h",
            "Repository.cpp",
            "Repository.h",
            "Storage.cpp",
            "Storage.h",
        ]

        Export { Depends { name: "cpp17" } }
    }
    Application {
        name: "schema_test"
        consoleApplication: true
        Depends { name: "schema" }
        files: [
            "SchemaTest.cpp",
        ]
    }
}
