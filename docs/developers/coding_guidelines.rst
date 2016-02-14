Coding guidelines
=================

We use the llvm code formating guidelines using clang-format.

We made a small script that will format any C++/javascript source file in the project to fit the style guidelines::

    sh scripts/beautify.sh

To run this tool, you need to install the following packages:

- **clang-format**: ``sudo pacman -S clang``
- **jsbeautifier**: ``sudo pip3 install jsbeautifier``


**Please, run this script before submitting a pull request!**
