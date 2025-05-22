#include <iostream>
#include "simulation.h"

//这里只包含主函数，
int main(int argc, char* argv[]) {
    world_t world;
    checkArgument(argc);
    checkRounds(argv[3]);
    readSpecies(world, argv[1]);//上交的时候记住在这里把第二个参数加上去
    readWorld(world, argv[2]);
//    std::cout << (*world.creatures[0].species).name << std::endl;
    initWorld(world);
    output(ifVerbose(argv[4]),world, atoi(argv[3]));
//    output(world, ifVerbose(argv[4]), atoi(argv[3]));
    return 0;
}
