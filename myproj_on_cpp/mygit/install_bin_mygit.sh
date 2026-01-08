#!/bin/bash

REAL_USER="$USER"
[ -z "$REAL_USER" ] && REAL_USER=$(id -un)

SOURCE_DIR="$HOME/mycode/myproj_on_cpp/mygit"
BINARY_NAME="mygit"
SOURCE_BINARY="$SOURCE_DIR/source_code/mygit"
TARGET_BINARY="/usr/local/bin/$BINARY_NAME"

# func for make a bill-like
print_box() {
    local title="$1"
    local content="$2"
    
    # finding max width
    local max_len=0
    while IFS= read -r line; do
        local len=${#line}
        [ $len -gt $max_len ] && max_len=$len
    done <<< "$content"
    
    [ -n "$title" ] && {
        local title_len=${#title}
        [ $title_len -gt $max_len ] && max_len=$title_len
    }
    
    # min width
    [ $max_len -lt 40 ] && max_len=40
    local width=$((max_len + 4))
    
    echo ""

    echo "+$(printf '%*s' $((width-2)) | tr ' ' '-')+"
    
    # title
    if [ -n "$title" ]; then
        local title_len=${#title}
        local left_padding=$(( (width - title_len - 2) / 2 ))
        local right_padding=$(( width - title_len - 2 - left_padding ))
        
        printf "|%*s%s%*s|\n" $left_padding "" "$title" $right_padding ""
        echo "+$(printf '%*s' $((width-2)) | tr ' ' '-')+"
    fi
    
    # main
    echo "$content" | while IFS= read -r line; do
        printf "| %-*s |\n" $((width-4)) "$line"
    done

    echo "+$(printf '%*s' $((width-2)) | tr ' ' '-')+"
    echo ""
}

DOC="mygit - Custom Git version control system
Author: genz
Source: $SOURCE_DIR

Features:
+ Commit tracking
+ Repository storage in text files
+ Revert to previous commits
+ Viewing commits and repositories

Installation options:
1. System-wide (/usr/local/bin)
2. User-only (~/.local/bin)
3. Cancel installation"

print_box "Documentation" "$DOC"

echo "Installing mygit..."
echo "  User: $REAL_USER"
echo "  Source: $SOURCE_BINARY"
echo ""

# check exists of bin
[ ! -f "$SOURCE_BINARY" ] && {
    ERROR_MSG="Binary not found at:
$SOURCE_BINARY

Please build with:
cd $SOURCE_DIR
make"
    
    print_box "ERROR!" "$ERROR_MSG"
    exit 1
}

# check permission
if [ -w "/usr/local/bin" ]; then
    cp "$SOURCE_BINARY" "$TARGET_BINARY"
    chmod 755 "$TARGET_BINARY"
    echo "Installed to $TARGET_BINARY"
else
    print_box "Installation Method" "1) System-wide (requires sudo)
2) User-only (no sudo)
3) Cancel installation"
    
    read -p "Choice [1-3]: " choice
    
    case $choice in
        1)
            echo "Requesting sudo privileges..."
            sudo cp "$SOURCE_BINARY" "$TARGET_BINARY" && \
            sudo chown root:root "$TARGET_BINARY" && \
            sudo chmod 755 "$TARGET_BINARY" && {
                echo "System installation complete"
            } || {
                echo "Installation failed, Check permissions or disk space."
                exit 1
            }
            ;;
        2)
            LOCAL_BIN="$HOME/.local/bin"
            mkdir -p "$LOCAL_BIN"
            cp "$SOURCE_BINARY" "$LOCAL_BIN/$BINARY_NAME"
            chmod +x "$LOCAL_BIN/$BINARY_NAME"
            TARGET_BINARY="$LOCAL_BIN/$BINARY_NAME"
            echo "Installed to $TARGET_BINARY"
            
            # check path
            if [[ ":$PATH:" != *":$LOCAL_BIN:"* ]]; then
                echo ""
                echo "Note: ~/.local/bin is not in your PATH"
                echo "Add this to ~/.bashrc or ~/.zshrc:"
                echo "export PATH=\"\$HOME/.local/bin:\$PATH\""
                echo "Then run: source ~/.bashrc"
            fi
            ;;
        3)
            echo "Installation cancelled."
            exit 0
            ;;
        *)
            echo "Invalid choice, using user install..."
            LOCAL_BIN="$HOME/.local/bin"
            mkdir -p "$LOCAL_BIN"
            cp "$SOURCE_BINARY" "$LOCAL_BIN/$BINARY_NAME"
            chmod +x "$LOCAL_BIN/$BINARY_NAME"
            TARGET_BINARY="$LOCAL_BIN/$BINARY_NAME"
            ;;
    esac
fi

# check successful installation
if [ $? -eq 0 ]; then
    RESULT="Location: $TARGET_BINARY"
    
    if command -v "$BINARY_NAME" >/dev/null 2>&1; then
        RESULT="$RESULT
PATH: $(which "$BINARY_NAME")"
    else
        RESULT="$RESULT
Not in PATH - add to ~/.bashrc:
export PATH=\"\$HOME/.local/bin:\$PATH\""
    fi
    
    print_box "Installation Result" "$RESULT"
    echo "Installation successful! Try: $BINARY_NAME --help"
else
    print_box "Installation Failed" "Something went wrong during installation."
    exit 1
fi