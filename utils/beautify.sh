#!/bin/bash
# This script beautify the C++ files using clang-format with llvm style
# and javascript file using js-beautify (install it using "sudo pip3 install jsbeautify")
find . \( -name '*.cpp' -o -name '*.h' \) | xargs clang-format -i -style=llvm
cd plugins
find . -name '*.js' -exec sh -c 'js-beautify -o "{}" "{}"' \;
