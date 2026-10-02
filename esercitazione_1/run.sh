#!/usr/bin/env bash

gcc esercitazione.c -o esercitazione && \
printf "\t\e[1mC output:\e[0m\n"
./esercitazione && \
printf "\t\e[1mPython output:\e[0m\n" && \
python3 esercitazione.py