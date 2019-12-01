cmake_minimum_required(VERSION 3.15)
project(qser C)

set(CMAKE_C_STANDARD 99)

add_executable(qser src/main.c src/mainThread/mainThread.c src/mainThread/mainThread.h src/userInterface/userInterface.c src/userInterface/userInterface.h src/quanserInterface/quanserInterface.c src/quanserInterface/quanserInterface.h src/helpers/helpers.c src/helpers/helpers.h src/pidController/pidController.c src/pidController/pidController.h)