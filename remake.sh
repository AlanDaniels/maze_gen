#!/bin/bash

trash build/
cmake -S . -B build/ && sleep 2 && cd build && make
