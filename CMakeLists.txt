cmake_minimum_required(VERSION 3.30)
project(bank)

set(CMAKE_CXX_STANDARD 20)

add_executable(bank
        main.cpp
        account.cpp
        database.cpp
        utils.cpp
        transaction.cpp)