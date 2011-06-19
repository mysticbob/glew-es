#!/bin/bash
#Move all the file from $2 to $1. And remove folder $2.
 
cp -t $1 $2/*
rm -rf $2


