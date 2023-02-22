# soft_template_repo_cmake_cpp
use this repo as template for new subprojects written in cpp and using cmake as build tool.
use this folder structure to let cmake handles path and naming for you.
```text
git_root_
     |_ CMakeLists.txt : parent cmake
     |_ src/
     |_ includes/
     |_ dependencies/_
     |                |_ .CMakeLists.txt : include all dependecies here
     |                |_ git_submodule_dep1/ : same as folder structure as parent
     |_ docs/
     |_ tests/
     |_ cmake/ 
     |_ scripts/
     |_ pkg/
```

# src
place sources here *.c *.cpp etc
# includes
place headers here *h *.hpp etc
# dependencies
place git submodules here. dependencies may follow same structure
# docs
place documentation here
# build
auto generated files are created here by cmake.
# tests
place your tests here 
# cmake
place external .cmake here
# scripts
optional: place any scripts here like python or bash
# pkg
optional: generate installer pkg here