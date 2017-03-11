#! /bin/bash

pandoc -w markdown intro.rst | tail -n +7 > intro.md
sed -i 's/ {.sourceCode .bash}/bash/' intro.md
sed -i 's/ {.sourceCode .python}/python/' intro.md

