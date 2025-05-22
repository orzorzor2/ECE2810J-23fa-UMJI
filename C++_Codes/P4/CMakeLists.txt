cmake_minimum_required(VERSION 3.26)
project(P4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(P4
        card.cpp
        card.h
        deck.h
        hand.h
        player.h
        rand.cpp
        rand.h
        deck.cpp
        deck.cpp
        hand.cpp
        hand.cpp
        player.cpp
        player.cpp
        blackjack.cpp
        blackjack.cpp)
