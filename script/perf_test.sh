#!/bin/bash

cd ../cmake-build-debug
perf stat -e cache-references -e cache-misses -e L1-dcache-loads -e L1-dcache-load-misses -e L1-dcache-stores -e L1-dcache-store-misses -e branch-instructions -e branch-misses -e instructions -e cycles -e page-faults ./PokeRpg
