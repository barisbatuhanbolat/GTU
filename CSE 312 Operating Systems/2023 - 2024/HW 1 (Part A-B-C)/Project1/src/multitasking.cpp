
#include <multitasking.h>

using namespace myos;
using namespace myos::common;
common::uint32_t Task::pIdCounter = 0;
void printf(char *);
void printNum(int num);
Task::Task()
{
}
Task::Task(GlobalDescriptorTable *gdt, void entrypoint())
{
    cpustate = (CPUState *)(stack + 4096 - sizeof(CPUState));

    cpustate->eax = 0;
    cpustate->ebx = 0;
    cpustate->ecx = 0;
    cpustate->edx = 0;

    cpustate->esi = 0;
    cpustate->edi = 0;
    cpustate->ebp = 0;

    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */

    // cpustate -> error = 0;

    // cpustate -> esp = ;
    cpustate->eip = (uint32_t)entrypoint;
    cpustate->cs = gdt->CodeSegmentSelector();
    // cpustate -> ss = ;
    cpustate->eflags = 0x202;
    pId = (Task::pIdCounter)++;
}
common::uint32_t Task::getId()
{
    return pId;
}
Task::~Task()
{
}
TaskManager::TaskManager()
{
}
TaskManager::TaskManager(GlobalDescriptorTable *gdt)
{
    taskCount = 0;
    currentTask = -1;
    timeQuantum = 10;
    this->gdt = gdt;
}

TaskManager::~TaskManager()
{
}

// ForkTask creates a new process.
// It checks for available slots and copies the parent task's state.
// On success, it returns the new task's process ID (pId).
common::uint32_t TaskManager::ForkTask(CPUState *cpustate)
{
    if (taskCount >= 256)
    {
        printf("There are 256 processes are active. No more can be created.\n");
        return 0;
    }
    tasks[taskCount].taskState = READY;
    tasks[taskCount].pPId = tasks[currentTask].pId;
    tasks[taskCount].pId = (Task::pIdCounter)++;

    // Copy the parent task's stack to the new task's stack
    for (int i = 0; i < sizeof(tasks[currentTask].stack); i++)
    {
        tasks[taskCount].stack[i] = tasks[currentTask].stack[i];
    }

    // Calculate the offset of the CPU state within the parent task's stack
    common::uint32_t currentTaskOffset = (((common::uint32_t)cpustate - (common::uint32_t)tasks[currentTask].stack));

    // Set the new task's CPU state pointer based on the offset and its own stack
    tasks[taskCount].cpustate = (CPUState *)(((common::uint32_t)tasks[taskCount].stack) + currentTaskOffset);

    // Initialize specific CPU register (ECX) to 0
    tasks[taskCount].cpustate->ecx = 0;
    taskCount++;

    // Set the new task's time slice (timeRemaining)
    tasks[taskCount].timeRemaining = timeQuantum;
    return tasks[taskCount - 1].pId;
}

// AddTask adds a new task with the provided task object.
// It checks for available slots and copies the state from the provided task.
// On success, it returns true.
bool TaskManager::AddTask(Task *task)
{
    if (taskCount >= 256)
        return false;
    tasks[taskCount].taskState = READY;
    tasks[taskCount].pId = task->pId;
    // Set the new task's CPU state pointer to the top of its stack with an offset for CPUState size
    tasks[taskCount].cpustate = (CPUState *)(tasks[taskCount].stack + 4096 - sizeof(CPUState));

    // Copy specific CPU registers (EAX, EBX, ECX, EDX) from the provided task
    tasks[taskCount].cpustate->eax = task->cpustate->eax;
    tasks[taskCount].cpustate->ebx = task->cpustate->ebx;
    tasks[taskCount].cpustate->ecx = task->cpustate->ecx;
    tasks[taskCount].cpustate->edx = task->cpustate->edx;

    // Copy additional CPU registers (ESI, EDI, EBP) from the provided task
    tasks[taskCount].cpustate->esi = task->cpustate->esi;
    tasks[taskCount].cpustate->edi = task->cpustate->edi;
    tasks[taskCount].cpustate->ebp = task->cpustate->ebp;

    // Copy program counter (EIP) and code segment (CS) from the provided task
    tasks[taskCount].cpustate->eip = task->cpustate->eip;
    tasks[taskCount].cpustate->cs = task->cpustate->cs;

    // Copy status flags (EFLAGS) from the provided task
    tasks[taskCount].cpustate->eflags = task->cpustate->eflags;
    // Set the new task's time slice (timeRemaining)
    tasks[taskCount].timeRemaining = timeQuantum;
    taskCount++;
    return true;
}

// AddTask adds a new task with the provided entry point function.
// It checks for available slots, allocates memory for the CPU state,
// and initializes the task with the entry point and code segment selector.
// On success, it returns the new task's process ID.
common::uint32_t TaskManager::AddTask(void entrypoint())
{
    tasks[taskCount].taskState = READY;
    tasks[taskCount].pId = (Task::pIdCounter)++;
    // Set the new task's CPU state pointer to the top of its stack with an offset for CPUState size
    tasks[taskCount].cpustate = (CPUState *)(tasks[taskCount].stack + 4096 - sizeof(CPUState));

    // Initialize specific CPU registers (EAX, EBX, ECX, EDX) to 0
    tasks[taskCount].cpustate->eax = 0;
    tasks[taskCount].cpustate->ebx = 0;
    tasks[taskCount].cpustate->ecx = 0;
    tasks[taskCount].cpustate->edx = 0;

    // Initialize additional CPU registers (ESI, EDI, EBP) to 0
    tasks[taskCount].cpustate->esi = 0;
    tasks[taskCount].cpustate->edi = 0;
    tasks[taskCount].cpustate->ebp = 0;

    // Set the program counter (EIP) to the entry point function address
    tasks[taskCount].cpustate->eip = (uint32_t)entrypoint;
    // Set the code segment selector from the global descriptor table (gdt)
    tasks[taskCount].cpustate->cs = gdt->CodeSegmentSelector();
    // Set specific status flags (EFLAGS)
    tasks[taskCount].cpustate->eflags = 0x202;
    taskCount++;
    tasks[taskCount].timeRemaining = timeQuantum;
    return tasks[taskCount - 1].pId;
}
// GetPID returns the process ID of the current task.
common::uint32_t TaskManager::GetPID()
{
    return tasks[currentTask].pId;
}

// ExecTask replaces the current task's state with the provided entry point function.
// It initializes the CPU state and sets the task to running.
// It likely returns a pointer to the CPU state for context switching.
common::uint32_t TaskManager::ExecTask(void entrypoint())
{
    tasks[currentTask].taskState - READY;
    // Set the current task's CPU state pointer to the top of its stack with an offset for CPUState size
    tasks[currentTask].cpustate = (CPUState *)(tasks[currentTask].stack + 4096 - sizeof(CPUState));

    // Initialize specific CPU registers (EAX, EBX, ECX, EDX) to 0
    tasks[currentTask].cpustate->eax = 0;
    tasks[currentTask].cpustate->ebx = 0;
    tasks[currentTask].cpustate->ecx = tasks[currentTask].pId;
    tasks[currentTask].cpustate->edx = 0;

    // Initialize additional CPU registers (ESI, EDI, EBP) to 0
    tasks[currentTask].cpustate->esi = 0;
    tasks[currentTask].cpustate->edi = 0;
    tasks[currentTask].cpustate->ebp = 0;

    // Set the program counter (EIP) to the entry point function address
    tasks[currentTask].cpustate->eip = (uint32_t)entrypoint;
    // Set the code segment selector from the global descriptor table (gdt)
    tasks[currentTask].cpustate->cs = gdt->CodeSegmentSelector();
    // Set specific status flags (EFLAGS)
    tasks[currentTask].cpustate->eflags = 0x202;
    return (uint32_t)tasks[currentTask].cpustate;
}
// ExitCurrentTask marks the current task as finished.
bool TaskManager::ExitCurrentTask()
{
    tasks[currentTask].taskState = FINISHED;
    PrintProcessTable();
    return true;
}
// getIndex finds the index of a task based on its process ID (pId).
// It returns -1 if the task is not found.
int TaskManager::getIndex(common::uint32_t pid)
{
    int index = -1;
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i].pId == pid)
        {
            index = i;
            break;
        }
    }
    return index;
}
// WaitTask suspends the current task until another task with the specified process ID (pid) finishes.
// It prevents a task from waiting for itself and checks for invalid targets or finished tasks.
// On success, it returns true.
bool TaskManager::WaitTask(common::uint32_t esp)
{
    CPUState *cpustate = (CPUState *)esp;
    // Extract the process ID to wait for from a CPU register (EBX)
    common::uint32_t pid = cpustate->ebx;
    if (tasks[currentTask].pId == pid || pid == 0) // prevention self waiting
        return false;
    int index = getIndex(pid);
    // Check if the target task exists and isn't already finished
    if (index == -1)
        return false;
    if (taskCount <= index || tasks[index].taskState == FINISHED)
        return false;
    tasks[currentTask].cpustate = cpustate;
    tasks[currentTask].waitPid = pid;
    tasks[currentTask].taskState = WAITING;
    return true;
}

void TaskManager::PrintProcessTable()
{
    printf("\n^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("PID\tPPID\tSTATE\n");
    for (int i = 1; i < taskCount; i++)
    {
        printNum(tasks[i].pId);
        printf("\t  ");
        printNum(tasks[i].pPId);
        printf("\t  ");
        if (tasks[i].taskState == TaskState::READY)
        {
            if (i == currentTask)
                printf("RUNNING");
            else
                printf("READY");
        }
        else if (tasks[i].taskState == TaskState::WAITING)
        {
            printf("WAITING");
        }
        else if (tasks[i].taskState == TaskState::FINISHED)
        {
            printf("FINISHED");
        }
        printf("\n");
    }
    printf("\n^^^^^^^^^^^^^^^^^^^^^^^^\n");
    for (int i = 0; i < 10000; i++)
    {
        for (int i = 0; i < 10000; i++)
        {
            printf("");
        }
    }
}

CPUState *TaskManager::Schedule(CPUState *cpustate)
{
    // Check if there are no tasks to schedule
    if (taskCount <= 0)
    {
        return cpustate;
    }

    // Save the CPU state of the current task
    if (currentTask >= 0)
    {
        tasks[currentTask].cpustate = cpustate;
    }

    // Initialize the next task index to check
    int findTask = (currentTask + 1) % taskCount;
    // Loop until a ready task is found
    while (tasks[findTask].taskState != READY)
    {
        // Check for tasks waiting on another task to finish
        if (tasks[findTask].taskState == WAITING && tasks[findTask].waitPid > 0)
        {
            int waitTaskIndex = getIndex(tasks[findTask].waitPid);

            // If the waited-on task is done, update waiting task and continue
            if (waitTaskIndex > -1 && tasks[waitTaskIndex].taskState != WAITING)
            {
                if (tasks[waitTaskIndex].taskState == FINISHED)
                {
                    tasks[findTask].waitPid = 0;
                    tasks[findTask].taskState = READY;
                }
            }
        }

        // Move to the next task (circular fashion)
        findTask = (findTask + 1) % taskCount;
        // Break if we looped back to the current task (no ready tasks)
        if (findTask == currentTask)
        {
            break;
        }
    }
    // Handle time remaining for the current task
    if (tasks[currentTask].taskState == READY)
    {
        // If the task finishes its time quantum, reset and move to next task
        tasks[currentTask].timeRemaining -= timeQuantum;
        if (tasks[currentTask].timeRemaining <= 0)
        {
            tasks[currentTask].timeRemaining = timeQuantum;
            findTask = (currentTask + 1) % taskCount;
        }
    }
    // If current task wasn't ready, just move to the next one
    else
    {
        findTask = (currentTask + 1) % taskCount;
    }

    // Loop again until a ready task is found (in case previous loop didn't)
    while (tasks[findTask].taskState != READY)
    {
        if (tasks[findTask].taskState == WAITING && tasks[findTask].waitPid > 0)
        {
            int waitTaskIndex = getIndex(tasks[findTask].waitPid);
            if (waitTaskIndex > -1 && tasks[waitTaskIndex].taskState != WAITING)
            {
                if (tasks[waitTaskIndex].taskState == FINISHED)
                {
                    tasks[findTask].waitPid = 0;
                    tasks[findTask].taskState = READY;
                }
            }
        }
        findTask = (findTask + 1) % taskCount;
        if (findTask == currentTask)
        {
            break;
        }
    }
    // Update the current task index and return its CPU state
    currentTask = findTask;
    return tasks[currentTask].cpustate;
}
