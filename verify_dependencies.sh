#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  DICE Dependencies Verification Tool  ${NC}"
echo -e "${BLUE}========================================${NC}"
echo ""

PASSED=0
FAILED=0
WARNINGS=0

# Функция для проверки команды
check_command() {
    if command -v $1 &> /dev/null; then
        echo -e "${GREEN}✓${NC} $1 найден: $(command -v $1)"
        ((PASSED++))
        return 0
    else
        echo -e "${RED}✗${NC} $1 не найден"
        ((FAILED++))
        return 1
    fi
}

# Функция для проверки библиотеки
check_library() {
    if pkg-config --exists $1 2>/dev/null; then
        VERSION=$(pkg-config --modversion $1)
        echo -e "${GREEN}✓${NC} $1 установлена (версия: $VERSION)"
        ((PASSED++))
        return 0
    else
        echo -e "${RED}✗${NC} $1 не найдена"
        ((FAILED++))
        return 1
    fi
}

# Функция для проверки директории
check_directory() {
    if [ -d "$1" ]; then
        echo -e "${GREEN}✓${NC} Директория найдена: $1"
        ((PASSED++))
        return 0
    else
        echo -e "${YELLOW}⚠${NC} Директория не найдена: $1"
        ((WARNINGS++))
        return 1
    fi
}

# Функция для проверки файла
check_file() {
    if [ -f "$1" ]; then
        echo -e "${GREEN}✓${NC} Файл найден: $1"
        ((PASSED++))
        return 0
    else
        echo -e "${YELLOW}⚠${NC} Файл не найден: $1"
        ((WARNINGS++))
        return 1
    fi
}

echo -e "${YELLOW}Проверка системных инструментов...${NC}"
echo "----------------------------------------"
check_command gcc
check_command g++
check_command cmake
check_command make
check_command git
check_command pkg-config
echo ""

echo -e "${YELLOW}Проверка установленных библиотек...${NC}"
echo "----------------------------------------"
check_library sfml-all
check_command lua
check_command luac

# Проверка GTest
if [ -f "/usr/lib/libgtest.a" ] || [ -f "/usr/lib/x86_64-linux-gnu/libgtest.a" ]; then
    echo -e "${GREEN}✓${NC} Google Test установлен"
    ((PASSED++))
else
    echo -e "${RED}✗${NC} Google Test не найден"
    ((FAILED++))
fi

# Проверка OpenGL
if pkg-config --exists gl 2>/dev/null; then
    echo -e "${GREEN}✓${NC} OpenGL установлен"
    ((PASSED++))
else
    echo -e "${RED}✗${NC} OpenGL не найден"
    ((FAILED++))
fi

echo ""

echo -e "${YELLOW}Проверка header-only библиотек...${NC}"
echo "----------------------------------------"
check_directory "external/imgui"
check_directory "external/json"
check_directory "external/sol2"
check_directory "external/spdlog"
echo ""

echo -e "${YELLOW}Проверка структуры проекта...${NC}"
echo "----------------------------------------"
check_file "CMakeLists.txt"
check_directory "include/core"
check_directory "scr"
check_directory "tests"
check_directory "asset"
check_directory "scripts"
echo ""

echo -e "${YELLOW}Проверка версий компиляторов...${NC}"
echo "----------------------------------------"
if command -v gcc &> /dev/null; then
    GCC_VERSION=$(gcc --version | head -n1)
    echo -e "${BLUE}GCC:${NC} $GCC_VERSION"
fi

if command -v g++ &> /dev/null; then
    GPP_VERSION=$(g++ --version | head -n1)
    echo -e "${BLUE}G++:${NC} $GPP_VERSION"
fi

if command -v cmake &> /dev/null; then
    CMAKE_VERSION=$(cmake --version | head -n1)
    echo -e "${BLUE}CMake:${NC} $CMAKE_VERSION"
fi

if command -v lua &> /dev/null; then
    LUA_VERSION=$(lua -v 2>&1)
    echo -e "${BLUE}Lua:${NC} $LUA_VERSION"
fi
echo ""

# Проверка ImGui файлов
echo -e "${YELLOW}Проверка ImGui компонентов...${NC}"
echo "----------------------------------------"
if [ -d "external/imgui" ]; then
    check_file "external/imgui/imgui.cpp"
    check_file "external/imgui/imgui.h"
    check_file "external/imgui/backends/imgui_impl_opengl3.cpp"
    # check_file "external/imgui/backends/imgui_impl_sfml.cpp" 
else
    echo -e "${YELLOW}⚠${NC} Директория ImGui не найдена"
fi
echo ""

# Итоговая статистика
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}           Итоговая статистика         ${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "${GREEN}Успешно:${NC}     $PASSED"
echo -e "${RED}Ошибки:${NC}      $FAILED"
echo -e "${YELLOW}Предупреждения:${NC} $WARNINGS"
echo ""

# Рекомендации
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}⚠ ВНИМАНИЕ: Обнаружены отсутствующие зависимости!${NC}"
    echo ""
    echo "Рекомендуемые действия:"
    echo "1. Запустите: ./setup_libraries.sh"
    echo "2. Или установите отсутствующие пакеты вручную"
    echo ""
    exit 1
elif [ $WARNINGS -gt 0 ]; then
    echo -e "${YELLOW}⚠ Некоторые опциональные компоненты отсутствуют${NC}"
    echo "Проект может быть собран, но некоторые функции могут не работать"
    echo ""
    exit 0
else
    echo -e "${GREEN}✓ Все зависимости установлены корректно!${NC}"
    echo ""
    echo "Можно приступать к сборке проекта:"
    echo "  cd build"
    echo "  cmake .."
    echo "  make -j\$(nproc)"
    echo ""
    exit 0
fi
