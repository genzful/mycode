#!/bin/bash

SOURCE_FILE="$HOME/mycode/myproj_on_cpp/tiktaktoe/source_code/tiktaktoe"

if [ ! -f "$SOURCE_FILE" ]; then
    echo "error: file $SOURCE_FILE not found! recopy my rep mycode"
    exit 1
fi

if [ ! -x "$SOURCE_FILE" ]; then
    echo "file is not executable"
    chmod +x "$SOURCE_FILE"
fi

TARGET_DIR="/usr/local/bin"
TARGET_FILE="$TARGET_DIR/tiktaktoe"

if [ ! -w "$TARGET_DIR" ]; then
    echo "need root passwd $TARGET_DIR"
    sudo cp "$SOURCE_FILE" "$TARGET_FILE"

    if [ $? -eq 0 ]; then
        echo "successfully $TARGET_FILE"
        echo "command: tiktaktoe"
    else
        echo "error with copying"
        exit 1
    fi
else
    cp "$SOURCE_FILE" "$TARGET_FILE"
    
    if [ $? -eq 0 ]; then
        echo "bin was copyed to $TARGET_FILE"
        echo "command: tiktaktoe"
    else
        echo "error with copying"
        exit 1
    fi
fi