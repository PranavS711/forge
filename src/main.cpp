#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <signal.h>

struct Job {
    int id;
    pid_t pid;  // stores the process ID
    std::string program;
    std::string status;
};

int main() {
    std::cout << "Forge starting..." << std::endl;

    std::string command;
    std::string program;
    int nextJobId = 1;

    std::vector<Job> jobs;
    while (true) {
        std::cout << "forge> ";
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Shutting down Forge" << std::endl;
            break;
        }
        else if(command == "help"){
            std::cout << "Available commands: "<<std::endl;
            std::cout << " help\n run <program>\n status\n exit\n" << std::endl;
        }
        else if(command == "status"){
            std::cout << "Forge status" << std::endl;
            std::cout << "Jobs: " << jobs.size() << std::endl;
            for (Job& job : jobs) {
                if(job.status != "running"){
                    continue;
                }
                int childStatus;
                int result = waitpid(job.pid, &childStatus, WNOHANG);

                if (result == job.pid) {
                  if (WIFEXITED(childStatus) && WEXITSTATUS(childStatus) == 0) {
                        job.status = "completed";
                  }
                else {
                    job.status = "failed";
                }
             }
            } // Check whether the child has finished without blocking Forge
            // Check whether the child exited normally and successfully
            for (const Job& job : jobs) {
                std::cout << "Job " << job.id
                  << " | PID: " << job.pid
                  << " | Program: " << job.program
                  << " | Status: " << job.status
                  << std::endl;
                }
        }
        else if(command == "kill"){
            int jobId;
            std::cin >> jobId;

            bool found = false; // Track whether the requested job ID exists


            for(Job& job: jobs){
                if(job.id == jobId){
                    bool found = true;
                    // Send SIGTERM to the process for this job
                    kill(job.pid, SIGTERM);  // SIGTERM asks the operating system to terminate the process
                    job.status = "terminated";

                    std::cout<< "Job "<< job.id << " Terminated" << std::endl; 
                }
            }
            if (!found) {
                std::cout << "Job " << jobId << " not found" << std::endl;
            }    
    }
        
        else if(command == "run"){
            std::cin >> program;
            pid_t pid = fork();  // Create a child process; fork() returns 0 to the child  and the child's PID to the parent

            if (pid == 0) { // This code is running in the child process
                execl(program.c_str(), program.c_str(), nullptr);   // Replace the child process with the program the user requested
                // c_str() converts the C++ string into the C-style string exec expects
                std::cout << "Failed to run program." << std::endl;
                return 1;
            }
            else { // Parent process
                        Job job;
                        job.id = nextJobId;
                        job.pid = pid;
                        job.program = program;
                        job.status = "running";
                        std::cout << "Job " << job.id << " started (PID: "
                                << job.pid << ")" << std::endl;

                        jobs.push_back(job);  // Store the job so Forge can track it after this command finishes


                         nextJobId++; // increment the ID so the next job gets a unique one
            }
        }
        else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }

    return 0;
}
