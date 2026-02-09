#include <stdint.h>
#include <exynos9830.h>
#include <memory.h>

uint32_t get_bl1_size(void)
{
	return readl(IRAM_BL1_SIZE); // Will always return 0x3000 cause of the previous BL1 loaded.
}