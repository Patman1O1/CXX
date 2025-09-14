#!/bin/bash

# ===============================
# Chmod all
# ===============================
ARG="$1"

chmod "$@" ./scripts/new-lib.sh
chmod "$@" ./scripts/detect-distro.sh
chmod "$@" ./scripts/pkg-mgr.sh
