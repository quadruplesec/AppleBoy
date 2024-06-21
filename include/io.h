#pragma once

#include <common.h>
#include <timer.h>
#include <cpu.h>

u8 io_read(u16 address);
void io_write(u16 address, u8 value);
