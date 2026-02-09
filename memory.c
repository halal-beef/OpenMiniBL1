#include <stdint.h>

void writel(uint32_t value, uint32_t addr)
{
	*(volatile uint32_t*)addr = value;
}

uint32_t readl(uint32_t addr)
{
	return *(volatile uint32_t*)addr;
}