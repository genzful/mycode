#!/bin/bash
# install_mygit_universal.sh

# Определяем реального пользователя
REAL_USER="$USER"
if [ -z "$REAL_USER" ]; then
    REAL_USER=$(id -un)
fi

SOURCE_DIR="/home/$REAL_USER/mycode/myproj_on_cpp/mygit"
BINARY_NAME="mygit"
SOURCE_BINARY="$SOURCE_DIR/source_code/mygit"
TARGET_BINARY="/usr/local/bin/$BINARY_NAME"  # Используем /usr/local/bin вместо /usr/bin

echo "Installing mygit as system binary..."
echo "User: $REAL_USER"
echo "Source: $SOURCE_BINARY"
echo "Target: $TARGET_BINARY"
echo ""

# Проверяем, существует ли бинарник
if [ ! -f "$SOURCE_BINARY" ]; then
    echo "ERROR: Binary not found at $SOURCE_BINARY"
    echo "Please build/compile mygit first!"
    exit 1
fi

# Функция для проверки прав
check_permissions() {
    local target_dir="/usr/local/bin"
    
    # Проверяем, можем ли писать в /usr/local/bin
    if [ -w "$target_dir" ]; then
        echo "You have write permissions to $target_dir"
        return 0
    else
        echo "Need elevated privileges to write to $target_dir"
        return 1
    fi
}

# Функция для установки с sudo
install_with_sudo() {
    echo "Requesting sudo privileges..."
    
    # Копируем с sudo
    sudo cp "$SOURCE_BINARY" "$TARGET_BINARY"
    
    # Устанавливаем права
    sudo chown root:root "$TARGET_BINARY"
    sudo chmod 755 "$TARGET_BINARY"
}

# Функция для установки без sudo
install_without_sudo() {
    echo "Installing without sudo..."
    
    # Пробуем создать symbolic link в ~/.local/bin
    LOCAL_BIN="$HOME/.local/bin"
    mkdir -p "$LOCAL_BIN"
    
    # Создаем symlink
    ln -sf "$SOURCE_BINARY" "$LOCAL_BIN/$BINARY_NAME"
    
    # Устанавливаем права
    chmod +x "$SOURCE_BINARY"
    
    TARGET_BINARY="$LOCAL_BIN/$BINARY_NAME"
}

# Основная логика
if check_permissions; then
    # Есть права - устанавливаем напрямую
    cp "$SOURCE_BINARY" "$TARGET_BINARY"
    chmod 755 "$TARGET_BINARY"
else
    # Выбор способа установки
    echo ""
    echo "Choose installation method:"
    echo "  1) Install system-wide with sudo (requires password)"
    echo "  2) Install for current user only (no sudo needed)"
    echo "  3) Cancel installation"
    echo ""
    
    read -p "Enter choice [1-3]: " choice
    
    case $choice in
        1)
            install_with_sudo
            ;;
        2)
            install_without_sudo
            ;;
        3)
            echo "Installation cancelled."
            exit 0
            ;;
        *)
            echo "Invalid choice. Using user installation."
            install_without_sudo
            ;;
    esac
fi

# Проверяем результат
if [ $? -eq 0 ]; then
    echo ""
    echo "✓ Success! mygit has been installed."
    echo "  Binary location: $TARGET_BINARY"
    echo ""
    
    # Проверяем доступность в PATH
    if command -v "$BINARY_NAME" > /dev/null 2>&1; then
        echo "Verification:"
        echo "  Command found at: $(which $BINARY_NAME)"
        
        # Пробуем получить версию
        echo -n "  Version: "
        "$BINARY_NAME" --version 2>/dev/null || echo "not available"
    else
        echo "Note: The binary might not be in your PATH yet."
        echo ""
        
        # Показываем, как добавить в PATH если нужно
        if [[ "$TARGET_BINARY" == *".local/bin"* ]]; then
            echo "To add to PATH, add this line to your shell config (~/.bashrc, ~/.zshrc):"
            echo "  export PATH=\"\$HOME/.local/bin:\$PATH\""
            echo ""
            echo "Then reload: source ~/.bashrc"
        fi
    fi
    
    echo ""
    echo "You can now use: $BINARY_NAME"
    
else
    echo "✗ ERROR: Installation failed!"
    exit 1
fi