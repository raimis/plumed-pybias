#! /bin/bash

# Convert README.md to index.md for GitHub Pages
tail -n +3 README.md > index.md

# Convert index.md to docs/intro.rst for Read The Docs.
echo '# Introduction' | cat - index.md | pandoc -o docs/intro.rst
