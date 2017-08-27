#!/bin/bash

Scripts/install_gcc.sh
Scripts/make_ass.sh &
Scripts/make_emu.sh &
wait
