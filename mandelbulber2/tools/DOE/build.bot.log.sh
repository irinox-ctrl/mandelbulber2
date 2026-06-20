#!/bin/bash
# Define a timestamp function
timestamp() {
	date +"%Y%m%d%H%M%S"
}

# Build Systems #
source $PWD/local.sh

filename=$build_logs/mandelbulber2-build_bot-$(timestamp).txt

cd $DOE && sh -x $DOE/build.bot.sh \
2>&1 \
| tee -a $filename
