
#ifndef __MYOS__MULTITASKING_H
#define __MYOS__MULTITASKING_H

#include <common/types.h>
#include <gdt.h>

namespace myos
{
    namespace hardwarecommunication
    {
        class InterruptHandler;
    }
    struct CPUState
    {
        common::uint32_t eax;
        common::uint32_t ebx;
        common::uint32_t ecx;
        common::uint32_t edx;

        common::uint32_t esi;
        common::uint32_t edi;
        common::uint32_t ebp;

        /*
        common::uint32_t gs;
        common::uint32_t fs;
        common::uint32_t es;
        common::uint32_t ds;
        */
        common::uint32_t error;

        common::uint32_t eip;
        common::uint32_t cs;
        common::uint32_t eflags;
        common::uint32_t esp;
        common::uint32_t ss;
    } __attribute__((packed));

    enum TaskState
    {
        READY,
        WAITING,
        FINISHED
    };

    class Task
    {
        friend class TaskManager;
        static common::uint32_t pIdCounter;

    private:
        common::uint8_t stack[4096];
        common::uint32_t pId = 0;
        common::uint32_t pPId = 0;
        TaskState taskState;
        common::uint32_t waitPid = 0;
        CPUState *cpustate;
        int timeRemaining;

    public:
        Task(GlobalDescriptorTable *gdt, void entrypoint());
        Task();
        common::uint32_t getId();
        ~Task();
    };

    class TaskManager
    {
        friend class hardwarecommunication::InterruptHandler;

    private:
        Task tasks[256];
        int taskCount;
        int currentTask;
        GlobalDescriptorTable *gdt = nullptr;
        int getIndex(common::uint32_t pid);
        int timeQuantum;

    protected:
        common::uint32_t AddTask(void entrypoint());
        common::uint32_t ExecTask(void entrypoint());
        common::uint32_t GetPID();
        common::uint32_t ForkTask(CPUState *cpustate);
        bool ExitCurrentTask();
        bool WaitTask(common::uint32_t pid);

    public:
        void PrintProcessTable();
        TaskManager(GlobalDescriptorTable *gdt);
        TaskManager();
        ~TaskManager();
        bool AddTask(Task *task);
        CPUState *Schedule(CPUState *cpustate);
    };

}

#endif