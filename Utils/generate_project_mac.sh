#!/bin/bash
# This script should cleanup project and regenerate project file for MacOS
#/Users/Shared/Epic\ Games/UE_5.0/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh -game -project="/Users/efreyu/UnrealProjects/RapidFire/RapidFire.uproject"

PROJECT_NAME="RapidFire"

uprojectFile="${PROJECT_NAME}.uproject"
if [[ -f ${uprojectFile} ]]; then
  rm -rf RapidFire.xcworkspace
  rm -rf Saved
  rm -rf Intermediate
  currentPath=$(eval pwd)
  /Users/Shared/Epic\ Games/UE_5.0/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh -game -project="${currentPath}/${uprojectFile}"
  exit 0
else
	echo "Source folder didn't found"
	exit 1
fi

