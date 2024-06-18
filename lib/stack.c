#include <stack.h>

void stack_push(u8 data)
{
    cpu_get_regs()->sp--;
    bus_write(cpu_get_regs()->sp, data);
}

void stack_push16(u16 data)
{
    // Top half of data
    stack_push((data >> 8) & 0xFF);
    // Bottom half of data
    stack_push(data & 0xFF);
}

u8 stack_pop()
{
    // Increment after returning to restore stack
    return bus_read(cpu_get_regs()->sp++);
}

u16 stack_pop16()
{
    u8 low = stack_pop();
    u8 high = stack_pop();
    return (high << 8) | low;
}
