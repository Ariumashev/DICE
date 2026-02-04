RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${GREEN}=== DICE Project Setup Script ===${NC}"
echo "Установка всех необходимых библиотек для проекта DICE"
echo ""

# Проверка, что скрипт запущен в корне проекта
if [ ! -f "CMakeLists.txt" ]; then
    echo -e "${RED}Ошибка: Запустите скрипт из корневой директории проекта!${NC}"
    exit 1
fi

# Обновление системы
echo -e "${YELLOW}Обновление системных пакетов...${NC}"
sudo apt update

# Установка базовых инструментов
echo -e "${YELLOW}Установка базовых инструментов разработки...${NC}"
sudo apt install -y build-essential cmake git pkg-config

# Установка SFML
echo -e "${YELLOW}Установка SFML...${NC}"
sudo apt install -y libsfml-dev

# Установка Lua
echo -e "${YELLOW}Установка Lua...${NC}"
sudo apt install -y lua5.3 liblua5.3-dev

# Установка Google Test
echo -e "${YELLOW}Установка Google Test...${NC}"
sudo apt install -y libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp lib/*.a /usr/lib
cd -

# Установка OpenGL
echo -e "${YELLOW}Установка OpenGL...${NC}"
sudo apt install -y libgl1-mesa-dev libglu1-mesa-dev

# Создание директории external если её нет
echo -e "${YELLOW}Создание директории external...${NC}"
mkdir -p external
cd external

# Установка Dear ImGui
if [ ! -d "imgui" ]; then
    echo -e "${YELLOW}Клонирование Dear ImGui...${NC}"
    git clone --depth 1 --branch v1.89.9 https://github.com/ocornut/imgui.git
else
    echo -e "${GREEN}ImGui уже установлен${NC}"
fi

# Установка nlohmann/json
if [ ! -d "json" ]; then
    echo -e "${YELLOW}Клонирование nlohmann/json...${NC}"
    git clone --depth 1 --branch v3.11.3 https://github.com/nlohmann/json.git
else
    echo -e "${GREEN}nlohmann/json уже установлен${NC}"
fi

# Установка sol2
if [ ! -d "sol2" ]; then
    echo -e "${YELLOW}Клонирование sol2...${NC}"
    git clone --depth 1 --branch v3.3.0 https://github.com/ThePhD/sol2.git
else
    echo -e "${GREEN}sol2 уже установлен${NC}"
fi

# Установка spdlog
if [ ! -d "spdlog" ]; then
    echo -e "${YELLOW}Клонирование spdlog...${NC}"
    git clone --depth 1 --branch v1.12.0 https://github.com/gabime/spdlog.git
else
    echo -e "${GREEN}spdlog уже установлен${NC}"
fi

cd ..

# Создание директорий для проекта если их нет
echo -e "${YELLOW}Создание структуры директорий проекта...${NC}"
mkdir -p scr/core scr/editor
mkdir -p include/core
mkdir -p tests
mkdir -p asset
mkdir -p scripts
mkdir -p build

echo ""
echo -e "${GREEN}=== Установка завершена! ===${NC}"
echo ""
