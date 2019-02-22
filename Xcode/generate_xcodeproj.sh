#!/bin/sh

PROJECT_NAME=compiler-workout-llvm
SCRIPT_PATH=`realpath $0`
SCRIPT_DIR=`dirname $SCRIPT_PATH`

if [ $SCRIPT_DIR != $(pwd) ]; then
    echo "This script must be run from the directory that it's in."
    exit 1
fi

cmake .. -G Xcode
mkdir -p $PROJECT_NAME.xcodeproj/xcshareddata
cp IDETemplateMacros.plist $PROJECT_NAME.xcodeproj/xcshareddata/IDETemplateMacros.plist
