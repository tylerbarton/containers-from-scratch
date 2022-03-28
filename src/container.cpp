//
// Created by Tyler Barton on 3/27/22.
//
#define _GNE_SOURCE
#include <cstdio>
#include <sched.h>
#include <sys/wait.h>
#include <iostream>

// Container Types
const int DEFAULT       = SIGCHLD | CLONE_NEWNS;
const int PID_Flags     = SIGCHLD | CLONE_NEWPID;
const int MNT_Flags     = SIGCHLD | CLONE_NEWNS;
const int NET_Flags     = SIGCHLD | CLONE_NEWNET;
const int USER_Flags    = SIGCHLD | CLONE_NEWUSER;
const int UTS_Flags     = SIGCHLD | CLONE_NEWUTS;
const int IPC_Flags     = SIGCHLD | CLONE_NEWIPC;

// Change this to modify the container type
static int clone_flags = DEFAULT;

typedef struct clone_args{
    char **argv;
} cloneArgs;

int main(int argc, char* argv[]){
    struct clone_args args;
    args.argv = &argv[1];

    std::cout << args.argv;
}