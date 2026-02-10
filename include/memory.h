#pragma once
#include <stdint.h>

#include <stdint.h>

inline void writel(uint32_t value, uint32_t addr)
{
	*(volatile uint32_t*)addr = value;
}

inline uint32_t readl(uint32_t addr)
{
	return *(volatile uint32_t*)addr;
}
