#!/bin/bash

cd ..
find . -name "*.swp" | xargs -I{} rm -rvf {}

