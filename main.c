#include <stdint.h>
#include <stdbool.h>

#include <exynos9830.h>
#include <memory.h>
#include <bootrom_funcs.h>
#include <pmu.h>
#include <epbl_info.h>
#include <epbl_checks.h>
#include <bl1_info.h>

uint32_t load_epbl_usb(void)
{
	uint32_t ret;

	unknown_func_lol(IRAM_UNK2);
	set_status_bit(1, 0x1000000);
	usb_send("Ready to rx EPBL");

	ret = usb_receive(get_epbl_load_address(), 0x02071000 - get_epbl_load_address());
	if(ret & 0xFF)
	{
		usb_send("EPBL rx done");
		ret = epbl_head_check();
		if(!ret)
			usb_send("EPBL Header fail");
		else
			usb_send("EPBL Header pass");
	}
	else
	{
		usb_send("EPBL rx fail");
		ret = 0;
	}
	
	unknown_func_lol(IRAM_UNK3);

	if(ret)
		set_status_bit(0, 0x4000000);

	return ret;
}

void jump_to_epbl(void)
{
    ((void(*)(void))get_epbl_load_address() + 0x0010)();
}

int main(void)
{
	usb_send("OpenMiniBL1 - Started");

	// TODO check if this is actually the boot flag
	uint32_t ret = 0;
	uint32_t bl1_boot_flag = get_bl1_boot_flag();
	set_ps_hold();
	set_epbl_load_address();
	ret = load_epbl_usb();
	if(!ret)
		while(1);

	ret = check_epbl_integ_and_auth(bl1_boot_flag);
	if(!ret)
		while(1);

	set_status_bit(0,0x80000000);
	usb_send("OpenMiniBL1 - Bye!");
	jump_to_epbl();
}
