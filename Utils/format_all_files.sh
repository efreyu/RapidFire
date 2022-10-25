#!/bin/bash

if [[ -f ".clang-format-ignore" ]]; then
	EXCLUDES=`cat .clang-format-ignore`
	echo Excluding : $EXCLUDES
else
	EXCLUDES=""
	echo "No .clang-format-ignore found"
fi

findSources() { 
  find $1/ -name "*.$2"
}

runFormat() {
  for F in `findSources "$1" "$2"`; do
  	DOFMT=TRUE
  	if [[ -n $EXCLUDES ]]; then
  		while read -r EXCL; do
  			if [[ -n $EXCL && $EXCL != /#* ]]; then
  				if [[ $F == $EXCL ]]; then
  					DOFMT=FALSE
  					break
  				fi
  			fi
  		done <<< "$EXCLUDES"
  	fi
  	if [[ $DOFMT == TRUE ]]; then
  		if [[ -f $F ]]; then
  			if [[ $2 == "--test" ]]; then
  				echo "Would format $F"
  			else
  				clang-format -i -verbose -style=file "$F"
  			fi
  		fi
  	fi
  done
}

if [[ -d "Source/" ]]; then
  runFormat "Source" "cpp"
  runFormat "Source" "h"
  exit 0
else
	echo "Source folder didn't found"
	exit 1
fi