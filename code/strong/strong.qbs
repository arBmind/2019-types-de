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
        name: "strong"
        Depends { name: "cpp17" }
        files: [
            "OpaqueHand.cpp",
            "OpaqueHand.h",
            "OpaqueMacro.cpp",
            "OpaqueMacro.h",
            "Strong.cpp",
            "Strong.h",
        ]

        Export { Depends { name: "cpp17" } }
    }
    Application {
        name: "strong_test"
        consoleApplication: true
        Depends { name: "strong" }
        files: [
            "StrongTest.cpp",
        ]
    }
}
