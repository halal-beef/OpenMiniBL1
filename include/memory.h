#pragma once
#include <stdint.h>

void writel(uint32_t value, uint32_t addr);
uint32_t readl(uint32_t addr);