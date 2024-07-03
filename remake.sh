#!/bin/bash

trash build/
cmake -S src/ -B build/ && sleep 2 && cd build && make
