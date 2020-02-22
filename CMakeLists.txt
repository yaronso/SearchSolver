cmake_minimum_required(VERSION 3.15)
project(part2)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(part2 main.cpp ClientHandler.h MyTestClientHandler.h Solver.h CacheManager.h Server.h
        MySerialServer.h MySerialServer.cpp ClientHandler.h
        mySocket.h StringReverser.h FileCacheManager.h ISearchable.h State.h
        Isearcher.h QueueSearcher.h CompareCost.h StackSearcher.h PrioritySearcher.h BestFirstSearch.h
        DFS.h MatrixProblem.h MyClientHandler.h  AStar.h MatrixSolverBestFS.h
        BFS.h  myParallelServer.cpp myParallelServer.h)
