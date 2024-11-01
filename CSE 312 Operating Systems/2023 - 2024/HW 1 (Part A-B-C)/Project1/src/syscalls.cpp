#include <syscalls.h>

using namespace myos;
using namespace myos::common;
using namespace myos::hardwarecommunication;

void printf(char *);
void printNum(int num);

// System call identifiers
enum SYSCALLS
{
    EXIT,
    GETPID,
    WAITPID,
    FORK,
    EXEC,
    PRINTF,
    ADDTASK
};
// Gets the process ID
int myos::getPid()
{
    int pId = 1;
    asm("int $0x80" : "=c"(pId) : "a"(SYSCALLS::GETPID));
    return pId;
}
// Waits for a child process with the given ID
void myos::waitpid(common::uint8_t wPid)
{
    asm("int $0x80" : : "a"(SYSCALLS::WAITPID), "b"(wPid));
}
// Exits the current process
void myos::sys_exit()
{
    asm("int $0x80" : : "a"(SYSCALLS::EXIT));
}
// Creates a child process (without returning the child's PID)
void myos::fork()
{
    asm("int $0x80" : : "a"(SYSCALLS::FORK));
}
// Creates a child process and returns the child's PID in the provided pointer
void myos::fork(int *pid)
{
    asm("int $0x80" : "=c"(*pid) : "a"(SYSCALLS::FORK));
}

int myos::exec(void entrypoint())
{
    int result;
    asm("int $0x80" : "=c"(result) : "a"(SYSCALLS::EXEC), "b"((uint32_t)entrypoint));
    return result;
}
// Adds a new task to the system
int myos::addTask(void entrypoint())
{
    int result;
    asm("int $0x80" : "=c"(result) : "a"(SYSCALLS::ADDTASK), "b"((uint32_t)entrypoint));
    return result;
}

SyscallHandler::SyscallHandler(InterruptManager *interruptManager, uint8_t InterruptNumber)
    : InterruptHandler(interruptManager, InterruptNumber + interruptManager->HardwareInterruptOffset())
{
}

SyscallHandler::~SyscallHandler()
{
}

uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    // Get a pointer to the CPU state structure from the stack pointerr
    CPUState *cpu = (CPUState *)esp;
    // Switch statement to handle different system calls based on the value in cpu->eax
    switch (cpu->eax)
    {
    case SYSCALLS::EXEC:
        esp = InterruptHandler::sys_exec(cpu->ebx);
        break;
    case SYSCALLS::FORK:
        cpu->ecx = InterruptHandler::sys_fork(cpu);
        return InterruptHandler::HandleInterrupt(esp);
        break;
    case SYSCALLS::PRINTF:
        printf((char *)cpu->ebx);
        break;
    case SYSCALLS::EXIT:
        if (InterruptHandler::sys_exit())
        {
            return InterruptHandler::HandleInterrupt(esp);
        }
        break;
    case SYSCALLS::WAITPID:
        if (InterruptHandler::sys_waitpid(esp))
        {
            return InterruptHandler::HandleInterrupt(esp);
        }
    case SYSCALLS::GETPID:
        cpu->ecx = InterruptHandler::sys_getpid();
        break;
    case SYSCALLS::ADDTASK:
        cpu->ecx = InterruptHandler::sys_addTask(cpu->ebx);
        break;
    default:
        break;
    }
    return esp;
}
