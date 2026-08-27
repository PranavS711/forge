#pragma once

#include <string>
#include <chrono>
#include <sys/types.h>

// Stores all information Forge tracks about a job
struct Job {
    int id;
    pid_t pid;
    std::string program;
    std::string status;

    std::chrono::steady_clock::time_point startTime;
    double runtimeSeconds;
};