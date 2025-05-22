#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "simulation.h"
#include "world_type.h"

//是readSpecies的一个辅助函数
opcode_t convertOpNameToEnum(const std::string &opNameFromfile) {
    for (int i = 0; i < 9; ++i) {
        if (opName[i] == opNameFromfile) {
            return static_cast<opcode_t>(i);
        }
    }
    assert(false);  // 如果到达这一点，说明有错误发生
}

void readSpecies(world_t &world, const char *arg) {
    std::ifstream speciesFile(arg);
    if (speciesFile.fail()) {
        std::cout << "Error: Cannot open file " << arg << "!";//交的时候改一下
        exit(0); // 使用 exit 终止程序
    }
    std::string line;
    getline(speciesFile, line);  // 读取第一行，即文件夹名
    std::string folderName = line;

    world.numSpecies = 0;//先初始化

    while (getline(speciesFile, line)) {  // 读取剩下的行，即文件名
        std::string fileName = folderName;
        fileName.append("/");
        fileName.append(line);

        std::ifstream creatureFile(fileName);
        if (creatureFile.fail()) {
            std::cout << "Error: Cannot open file " << fileName << "!" << std::endl;
            exit(0); //
        }

        world.species[world.numSpecies].name = line;
        world.species[world.numSpecies].programSize = 0;//初始化

        std::string instructionLine;
        while (getline(creatureFile, instructionLine)) {  // 读取creature文件的每一行，在读取一个文件过程中，numSpecies是不变的
            std::istringstream iss(instructionLine);
            std::string command;
            iss >> command;
            // 检查命令是否需要被读取
            if (command == "hop" || command == "left" || command == "right" || command == "infect"
                || command == "ifempty" || command == "ifenemy" || command == "ifsame" || command == "ifwall" ||
                command == "go") {
                world.species[world.numSpecies].program[world.species[world.numSpecies].programSize].op = convertOpNameToEnum(
                        command);
                if (command == "ifempty" || command == "ifenemy" || command == "ifsame" || command == "ifwall" ||
                    command == "go") {
                    iss >> world.species[world.numSpecies].program[world.species[world.numSpecies].programSize].address;  // 如果命令后面有参数，读取参数
                }
                world.species[world.numSpecies].programSize++;
            }
        }
        checkNumProgram(world.species[world.numSpecies].programSize,
                        world.species[world.numSpecies].name);//调用了第5个函数,传入单个物种的指令数和名字
        checkIllegal(world, world.species[world.numSpecies].programSize);
        world.numSpecies++;
    }

    speciesFile.close();

    checkNumSpecies(world.numSpecies);//调用了第4个函数
}


species_t *getSpecies(world_t &world, const std::string &name) {
    for (unsigned int i = 0; i < world.numSpecies; ++i) {
        if (world.species[i].name == name) {
            return &world.species[i];
        }
    }
    std::cout << "Error: Species " << name << " not found!\n";
    exit(0); // 如果没有找到匹配的物种，打印错误信息并终止程序
}

direction_t getDirection(const std::string &direction) {
    if (direction == "east") return EAST;
    else if (direction == "south") return SOUTH;
    else if (direction == "west") return WEST;
    else if (direction == "north") return NORTH;
    else {
        std::cout << "Error: Direction " << direction << " is not recognized!\n";
        exit(0); // 如果方向字符串无法识别，打印错误信息并终止程序
    }
}

void readWorld(world_t &world, const char *arg) {
    // 初始化creatures数组，如果不初始化的话，访问没存进的数组元素，就会出来一些很随机的值
//    for (int i = 0; i < MAXCREATURES; ++i) {
//        world.creatures[i].species = nullptr;
//        world.creatures[i].direction = EAST; // 或者其他默认方向
//        world.creatures[i].location.r = 0;
//        world.creatures[i].location.c = 0;
//        world.creatures[i].programID = 0;
//    }

    std::ifstream file(arg); // 使用arg作为文件名
    if (!file) {
        std::cout << "Error: Cannot open file " << arg << "!";
        exit(0);
    }

    file >> world.grid.height >> world.grid.width;
    checkGridSize(world.grid.height, world.grid.width);
    std::string creatureName, direction;
    int x, y;
    world.numCreatures = 0;

    while (file >> creatureName >> direction >> x >> y) {
        creature_t creature;

        creature.species = getSpecies(world, creatureName);
        creature.direction = getDirection(direction);

        creature.location.r = x;
        creature.location.c = y;

        // 检查生物是否在网格内
        if (x < 0 || x >= static_cast<int>(world.grid.height) || y < 0 || y >= static_cast<int>(world.grid.width)) {
            std::cout << "Error: Creature (" << creatureName << " " << direction << " " << x << " " << y
                      << ") is out of bound!\n";
            std::cout << "The grid size is " << world.grid.height << "-by-" << world.grid.width << ".\n";
            exit(0);
        }


        // 检查生物是否与其他生物重叠
        for (unsigned int i = 0; i < world.numCreatures; i++) {
            if (world.creatures[i].location.r == x && world.creatures[i].location.c == y) {
                std::cout << "Error: Creature (" << creatureName << " " << direction << " " << x << " " << y
                          << ") overlaps with creature ("
                          << world.creatures[i].species->name << " " << directName[world.creatures[i].direction] << " "
                          << world.creatures[i].location.r << " " << world.creatures[i].location.c << ")!\n";
                exit(0);
            }
        }

        world.creatures[world.numCreatures] = creature;
        world.numCreatures++;
    }
    checkNumCreature(world.numCreatures);

    file.close();

}

//1  check the number of the argument and issue the error
void checkArgument(int num) {
    if (num < 3) {
        std::cout << "Error: Missing arguments!" << std::endl;
        std::cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << std::endl;
    }
    //else应该不用了吧
}

//2  check if the number of round is negative
//这里的字符串是main函数里argv[3]
void checkRounds(std::string round) {
    if (std::stoi(round) < 0) {
        std::cout << "Error: Number of simulation rounds is negative!" << std::endl;
    }
}


//4
void checkNumSpecies(const unsigned int num) {
    if (num > MAXSPECIES) {
        std::cout << "Error: Too many species!" << std::endl;
        std::cout << "Maximal number of instructions is " << MAXSPECIES << "." << std::endl;
        exit(0); // 使用 exit 终止程序
    }
}

//5  要读取例如flytrap文件中的instruction行数，如果超过40 ，就报错，还需要一个参数来反映   物种名字
void checkNumProgram(const unsigned int num, const std::string name) {
    if (num > MAXPROGRAM) {
        std::cout << "Error: Too many instructions for species" << name << "!" << std::endl;
        std::cout << "Maximal number of instructions is " << MAXPROGRAM << "." << std::endl;
        exit(0); // 使用 exit 终止程序
    }
}


//6!!!!  读文件读取到了world.species[].program[].op中，表示操作的是opName[ world.species[].program[].op ]
void checkIllegal(const world_t world, int numInstruction) {
    std::string instructionsRead[numInstruction];
    for (int i = 0; i < numInstruction; i++) {
        instructionsRead[i] = opName[world.species[world.numSpecies].program[i].op];
    }
    for (int k = 0; k < numInstruction; k++) {
        bool found = false;
        for (int j = 0; j < 9; j++) {
            if (instructionsRead[k] == opName[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Error: Instruction " << instructionsRead[k] << " is not recognized!" << std::endl;
            exit(0); // 使用 exit 终止程序
        }
    }
}


//7
void checkNumCreature(const unsigned int num) {
    if (num > MAXCREATURES) {
        std::cout << "Error: Too many creatures!" << std::endl;
        std::cout << "Maximal number of creatures is " << MAXCREATURES << "." << std::endl;
        exit(0);
    }
}

//10 11 从world file中读下来的
void checkGridSize(const unsigned int height, const unsigned int width) {
    if ((height < 1) || (height > MAXHEIGHT)) {
        std::cout << "Error: The grid height is illegal!" << std::endl;
        exit(0);
    } else if ((width < 1) || (width > MAXWIDTH)) {
        std::cout << "Error: The grid width is illegal!" << std::endl;
        exit(0);
    }
}


//完成2个readfile中未完成的初始化，并将initial的grid打印出来。
void initWorld(world_t &world) {
    //初始化指针数组
    for (auto & square : world.grid.squares) {
        for (auto & j : square) {
            j = nullptr;
        }
    }
    //将world file中读取的creature信息存到squares数组中
    for (unsigned int i = 0; i < world.numCreatures; i++) {
        world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c] = &world.creatures[i];
    }

    for (unsigned int i = 0; i < world.numCreatures; i++) {
        world.creatures[i].programID = 0;//counter都设置为0
    }
    std::cout << "Initial state" << std::endl;
    printGrid(world.grid);//最开始的打印出来
}

void printGrid(const grid_t &grid) {
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            if (grid.squares[i][j] == nullptr) {
                std::cout << "____ ";
            } else {
                std::cout << (((grid.squares[i][j])->species)->name).substr(0, 2) << "_"
                          << directShortName[grid.squares[i][j]->direction] << " ";
            }
        }
        std::cout << "\n";
    }
}


bool ifVerbose(const char *arg) {
    if (arg != nullptr) {
        std::string argStr = arg;
        if (argStr == "v" || argStr == "verbose") {
            return true;
        }
    }
    return false;
}

void output(bool verbose, world_t &world, int round) {
    if (verbose) {
        verOutput(world, round);
    } else {
        conOutput(world, round);
    }
}

void conOutput(world_t &world, int round) {
    for (int k = 1; k <= round; k++) {
        std::cout << "Round " << k << std::endl;
        for (unsigned int i = 0; i < world.numCreatures; i++) { //生物按顺序来运行
            // 获取当前这只生物的指针，所有信息都到了creature变量中
            creature_t &cre = world.creatures[i];
            // 输出当前生物的信

            opcode_t action;
            std::string actionName;
            int initr = cre.location.r;
            int initc = cre.location.c;
            std::string initdir = directName[cre.direction];
            while (true) {
                action = cre.species->program[cre.programID].op;
                actionName = opName[action]; //这里把与ID相对应的操作取出来了
                // 输出2类的Instruction: hop 或者 ifenemy 4

                if (actionName == "left") {
                    left(world.grid, cre.location.r, cre.location.c);
//                    std::cout << "Instruction " << cre.programID + 1 << ": " << actionName << std::endl;
//                    printGrid(world.grid);
                    cre.programID++;
                    break;
                } else if (actionName == "right") {
                    right(world.grid, cre.location.r, cre.location.c);
//                    std::cout << "Instruction " << cre.programID + 1 << ": " << actionName << std::endl;
//                    printGrid(world.grid);
                    cre.programID++;
                    break;
                } else if (actionName == "hop") {
                    hop(cre, cre.location.r, cre.location.c, world.grid);
//                    std::cout << "Instruction " << cre.programID + 1 << ": " << actionName << std::endl;
//                    printGrid(world.grid);
                    cre.programID++;
                    break;
                } else if (actionName == "infect") {
                    infect(world.grid, cre.location.r, cre.location.c);
//                    std::cout << "Instruction " << cre.programID + 1 << ": " << actionName << std::endl;
//                    printGrid(world.grid);
                    cre.programID++;
                    break;
                } else if (actionName == "ifempty") {
                    ifEmptyCon(world.grid, cre, cre.species->program[cre.programID].address);
                } else if (actionName == "ifwall") {
                    ifWallCon(world.grid, cre, cre.species->program[cre.programID].address);
                } else if (actionName == "ifenemy") {
                    ifEnemyCon(world.grid, cre, cre.species->program[cre.programID].address);
                } else if (actionName == "ifsame") {
                    ifSameCon(world.grid, cre, cre.species->program[cre.programID].address);
                } else if (actionName == "go") {
                    goCon(cre, cre.species->program[cre.programID].address);
                }
            }
//            printGrid(world.grid);
            std::cout << "Creature (" << cre.species->name << " " << initdir << " "
                      << initr << " " << initc << ") takes action: " << actionName << std::endl;

        }
        printGrid(world.grid);
    }
}



void verOutput(world_t &world, int round) {
    for (int k = 1; k <= round; k++) {
        std::cout << "Round " << k << std::endl;
        for (unsigned int i = 0; i < world.numCreatures; i++) { //生物按顺序来运行
            // 获取当前这只生物的指针，所有信息都到了creature变量中
            creature_t &cre = world.creatures[i];
            // 输出当前生物的信息
            std::cout << "Creature (" << cre.species->name << " " << directName[cre.direction] << " "
                      << cre.location.r << " " << cre.location.c << ") takes action:" << std::endl;

            opcode_t action;
            std::string actionName;

            while (true) {
                action = cre.species->program[cre.programID].op;
                actionName = opName[action]; //这里把与ID相对应的操作取出来了
                // 输出2类的Instruction: hop 或者 ifenemy 4

                if (actionName == "left") {
                    left(world.grid, cre.location.r, cre.location.c);
                    std::cout << "Instruction " << cre.programID + 1 << ": " << actionName << std::endl;
                    printGrid(world.grid);
                    cre.programID++;
                    break;
                } else if (actionName == "right") {
                    right(world.grid, cre.location.r, cre.location.c);
                    std::cout << "Instruction " << cre.programID + 1 << ": " << actionName << std::endl;
                    printGrid(world.grid);
                    cre.programID++;
                    break;
                } else if (actionName == "hop") {
                    hop(cre, cre.location.r, cre.location.c, world.grid);
                    std::cout << "Instruction " << cre.programID + 1 << ": " << actionName << std::endl;
                    printGrid(world.grid);
                    cre.programID++;
                    break;
                } else if (actionName == "infect") {
                    infect(world.grid, cre.location.r, cre.location.c);
                    std::cout << "Instruction " << cre.programID + 1 << ": " << actionName << std::endl;
                    printGrid(world.grid);
                    cre.programID++;
                    break;
                } else if (actionName == "ifempty") {
                    ifEmpty(world.grid, cre, cre.species->program[cre.programID].address);
                } else if (actionName == "ifwall") {
                    ifWall(world.grid, cre, cre.species->program[cre.programID].address);
                } else if (actionName == "ifenemy") {
                    ifEnemy(world.grid, cre, cre.species->program[cre.programID].address);
                } else if (actionName == "ifsame") {
                    ifSame(world.grid, cre, cre.species->program[cre.programID].address);
                } else if (actionName == "go") {
                    go(cre, cre.species->program[cre.programID].address);
                }
            }
//            printGrid(world.grid);

        }
    }
}


void left(grid_t &grid, unsigned int r, unsigned int c) {
    if (grid.squares[r][c]->direction == EAST) {
        grid.squares[r][c]->direction = NORTH;
    } else if (grid.squares[r][c]->direction == NORTH) {
        grid.squares[r][c]->direction = WEST;
    } else if (grid.squares[r][c]->direction == WEST) {
        grid.squares[r][c]->direction = SOUTH;
    } else if (grid.squares[r][c]->direction == SOUTH) {
        grid.squares[r][c]->direction = EAST;
    }
}

void right(grid_t &grid, unsigned int r, unsigned int c) {
    if (grid.squares[r][c]->direction == EAST) {
        grid.squares[r][c]->direction = SOUTH;
    } else if (grid.squares[r][c]->direction == NORTH) {
        grid.squares[r][c]->direction = EAST;
    } else if (grid.squares[r][c]->direction == WEST) {
        grid.squares[r][c]->direction = NORTH;
    } else if (grid.squares[r][c]->direction == SOUTH) {
        grid.squares[r][c]->direction = WEST;
    }
}

void hop(creature_t& cre, unsigned int r, unsigned int c, grid_t& grid) {
    unsigned int x = r;
    unsigned int y = c;
    direction_t dir = cre.direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格内并且没有其他生物
    if (x >= 0 && x < grid.height && y >= 0 && y < grid.width && grid.squares[x][y] == nullptr) {
        // 更新生物的位置
        cre.location.r = x;
        cre.location.c = y;
        grid.squares[x][y] = &cre;

        grid.squares[r][c] = nullptr;
    }
    // 如果新位置在网格外或者有其他生物，hop 指令不做任何事情
}

void infect(grid_t &grid, unsigned int r, unsigned int c) {
    unsigned int x = r;
    unsigned int y = c;
    direction_t dir = grid.squares[r][c]->direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格内并且有其他种类的生物
    if (x >= 0 && x < grid.height && y >= 0 && y < grid.width && grid.squares[x][y] != nullptr &&
        grid.squares[x][y]->species != grid.squares[r][c]->species) {
        // 感染生物
        grid.squares[x][y]->species = grid.squares[r][c]->species;
        grid.squares[x][y]->programID = 0;  // 开始执行新种类的程序，从第一步开始
    }
    // 如果新位置在网格外、为空，或者有同种类的生物，infect 指令不做任何事情
}

void ifEmpty(grid_t &grid, creature_t &creature, unsigned int n) {
    int x = creature.location.r;
    int y = creature.location.c;
    direction_t dir = creature.direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格内并且为空
    if (x >= 0 && static_cast<unsigned int>(x) < grid.height && y >= 0 && static_cast<unsigned int>(y) < grid.width && grid.squares[static_cast<unsigned int>(x)][static_cast<unsigned int>(y)] == nullptr) {
        // 跳转到程序的第 n 步
        std::cout << "Instruction " << creature.programID + 1 << ": "
                  << opName[creature.species->program[creature.programID].op] << " "
                  << creature.species->program[creature.programID].address << std::endl;
        creature.programID = n - 1;
    } else {
        std::cout << "Instruction " << creature.programID + 1 << ": "
                  << opName[creature.species->program[creature.programID].op] << " "
                  << creature.species->program[creature.programID].address << std::endl;
        creature.programID++;
    }
}


void ifEmptyCon(grid_t &grid, creature_t &creature, unsigned int n) {
    int x = creature.location.r;
    int y = creature.location.c;
    direction_t dir = creature.direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格内并且为空
    if (static_cast<unsigned int>(x) >= 0 && static_cast<unsigned int>(x) < grid.height && static_cast<unsigned int>(y) >= 0 && static_cast<unsigned int>(y) < grid.width && grid.squares[static_cast<unsigned int>(x)][static_cast<unsigned int>(y)] == nullptr) {
        // 跳转到程序的第 n 步
        creature.programID = n - 1;
    } else {
        creature.programID++;
    }
}

void ifWall(grid_t &grid, creature_t &creature, unsigned int n) {
    int x = creature.location.r;
    int y = creature.location.c;
    direction_t dir = creature.direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格外
    if (static_cast<unsigned int>(x) < 0 || static_cast<unsigned int>(x) >= grid.height || static_cast<unsigned int>(y) < 0 || static_cast<unsigned int>(y) >= grid.width) {
        // 跳转到程序的第 n 步
        std::cout << "Instruction " << creature.programID + 1 << ": "
                  << opName[creature.species->program[creature.programID].op] << " "
                  << creature.species->program[creature.programID].address << std::endl;
        creature.programID = n - 1;
    } else {
        std::cout << "Instruction " << creature.programID + 1 << ": "
                  << opName[creature.species->program[creature.programID].op] << " "
                  << creature.species->program[creature.programID].address << std::endl;
        creature.programID++;
    }
}


void ifWallCon(grid_t &grid, creature_t &creature, unsigned int n) {
    int x = creature.location.r;
    int y = creature.location.c;
    direction_t dir = creature.direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格外
    if (x < 0 || x >= static_cast<int>(grid.height) || y < 0 || y >= static_cast<int>(grid.width)) {
        // 跳转到程序的第 n 步
        creature.programID = n - 1;
    } else {
        creature.programID++;
    }
}


void ifEnemy(grid_t &grid, creature_t &creature, unsigned int n) {
    int x = creature.location.r;
    int y = creature.location.c;
    direction_t dir = creature.direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格内并且有敌人
    if (x >= 0 && x < static_cast<int>(grid.height) && y >= 0 && y < static_cast<int>(grid.width) && grid.squares[x][y] != nullptr &&
        grid.squares[x][y]->species != creature.species) {
        // 跳转到程序的第 n 步
        std::cout << "Instruction " << creature.programID + 1 << ": "
                  << opName[creature.species->program[creature.programID].op] << " "
                  << creature.species->program[creature.programID].address << std::endl;
        creature.programID = n - 1;
    } else {
        std::cout << "Instruction " << creature.programID + 1 << ": "
                  << opName[creature.species->program[creature.programID].op] << " "
                  << creature.species->program[creature.programID].address << std::endl;
        creature.programID++;
    }
}

void ifEnemyCon(grid_t &grid, creature_t &creature, unsigned int n) {
    int x = creature.location.r;
    int y = creature.location.c;
    direction_t dir = creature.direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格内并且有敌人
    if (x >= 0 && x < static_cast<int>(grid.height) && y >= 0 && y < static_cast<int>(grid.width) && grid.squares[x][y] != nullptr &&
        grid.squares[x][y]->species != creature.species) {
        // 跳转到程序的第 n 步
        creature.programID = n - 1;
    } else {
        creature.programID++;
    }
}

void ifSame(grid_t &grid, creature_t &creature, unsigned int n) {
    int x = creature.location.r;
    int y = creature.location.c;
    direction_t dir = creature.direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格内并且有同种类的生物
    if (x >= 0 && x < static_cast<int>(grid.height) && y >= 0 && y < static_cast<int>(grid.width) && grid.squares[x][y] != nullptr &&
        grid.squares[x][y]->species == creature.species) {
        // 跳转到程序的第 n 步
        std::cout << "Instruction " << creature.programID + 1 << ": "
                  << opName[creature.species->program[creature.programID].op] << " "
                  << creature.species->program[creature.programID].address << std::endl;
        creature.programID = n - 1;
    } else {
        std::cout << "Instruction " << creature.programID + 1 << ": "
                  << opName[creature.species->program[creature.programID].op] << " "
                  << creature.species->program[creature.programID].address << std::endl;
        creature.programID++;
    }
}

void ifSameCon(grid_t &grid, creature_t &creature, unsigned int n) {
    int x = creature.location.r;
    int y = creature.location.c;
    direction_t dir = creature.direction;

    switch (dir) {
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
        case NORTH:
            x--;
            break;
    }

    // 检查新位置是否在网格内并且有同种类的生物
    if (x >= 0 && x < static_cast<int>(grid.height) && y >= 0 && y < static_cast<int>(grid.width) && grid.squares[x][y] != nullptr &&
        grid.squares[x][y]->species == creature.species) {
        // 跳转到程序的第 n 步
        creature.programID = n - 1;
    } else {
        creature.programID++;
    }
}

void go(creature_t &creature, unsigned int n) {
    // 跳转到程序的第 n 步
    std::cout << "Instruction " << creature.programID + 1 << ": "
              << opName[creature.species->program[creature.programID].op] << " "
              << creature.species->program[creature.programID].address << std::endl;
    creature.programID = n - 1;
}


void goCon(creature_t &creature, unsigned int n) {
    // 跳转到程序的第 n 步

    creature.programID = n - 1;
}