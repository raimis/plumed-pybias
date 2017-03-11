#! /bin/bash

# Documentation generator

# Convert README.md to index.md for GitHub Pages
tail -n +5 README.md > index.md

# Convert README.md to docs/intro.rst for Read The Docs.
tail -n +3 README.md | pandoc -r markdown -o docs/intro.rst

