#!/bin/bash

# Create the binary directory if it doesn't exist
if [ ! -d "binary" ]; then
    mkdir binary
fi

cd binary

# Create the retdec directory if it doesn't exist
if [ ! -d "retdec" ]; then
    mkdir retdec
fi

# Change to the retdec directory
cd retdec

# Download Retdec v5.0 release archive for Linux
wget https://github.com/avast/retdec/releases/download/v5.0/RetDec-v5.0-Linux-Release.tar.xz

# Unarchive the downloaded file in the current directory
tar -xf RetDec-v5.0-Linux-Release.tar.xz

# Remove the archive file
rm RetDec-v5.0-Linux-Release.tar.xz