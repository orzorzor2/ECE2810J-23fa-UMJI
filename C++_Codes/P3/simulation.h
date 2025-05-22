#ifndef P3_SIMULATION_H
#define P3_SIMULATION_H
#include "world_type.h"

opcode_t convertOpNameToEnum(const std::string& opNameFromfile);

void readSpecies(world_t &world, const char *arg);


direction_t getDirection(const std::string& direction);

species_t* getSpecies(world_t& world, const std::string& name);

void readWorld(world_t &world, const char* arg);

void checkArgument(int num);

void checkRounds(std::string round);


void checkNumSpecies(const unsigned int num); //读完整个文件夹再执行

void checkNumProgram(const unsigned int num, const std::string name); //读完一个文件执行一次

void checkIllegal(const world_t world, int numInstruction);//在读每一行的时候都执行一次

void checkNumCreature(const unsigned int num);

void checkGridSize(const unsigned int height, const unsigned int width);

/*以下都是模拟相关的函数*/
/*                 */

void initWorld(world_t& world);

void printGrid(const grid_t& grid);

bool ifVerbose(const char *arg);

void output(bool verbose, world_t &world, int round) ;

void conOutput(world_t &world, int round);

void verOutput(world_t &world, int round);

void left(grid_t& grid, unsigned int r, unsigned int c);

void right(grid_t& grid, unsigned int r, unsigned int c);

void hop(creature_t& cre,  unsigned int r, unsigned int c, grid_t& grid);

void infect(grid_t &grid, unsigned int r, unsigned int c);

void ifEmpty(grid_t &grid, creature_t &creature, unsigned int n);

void ifWall(grid_t &grid, creature_t &creature, unsigned int n);

void ifEnemy(grid_t &grid, creature_t &creature, unsigned int n);

void ifSame(grid_t &grid, creature_t &creature, unsigned int n);

void go(creature_t &creature, unsigned int n);

void ifEmptyCon(grid_t &grid, creature_t &creature, unsigned int n);

void ifWallCon(grid_t &grid, creature_t &creature, unsigned int n);

void ifEnemyCon(grid_t &grid, creature_t &creature, unsigned int n);

void ifSameCon(grid_t &grid, creature_t &creature, unsigned int n);

void goCon(creature_t &creature, unsigned int n);

#endif //P3_SIMULATION_H
