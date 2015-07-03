#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0xc906a5e1, "struct_module" },
	{ 0xad5381d9, "__invoke_copy_to_user_dma" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x78c0ffec, "__down_interruptible" },
	{ 0xffaf7bbb, "__wake_up_sync" },
	{ 0x229b67c0, "remove_proc_entry" },
	{ 0x3fe5fc36, "__up" },
	{ 0x3d804915, "__invoke_copy_from_user_dma" },
	{ 0x7d11c268, "jiffies" },
	{ 0x2bc95bd4, "memset" },
	{ 0x874361f8, "cpu_data" },
	{ 0x7dceceac, "capable" },
	{ 0x1000e51, "schedule" },
	{ 0x762c562a, "create_proc_entry" },
	{ 0x6cb34e5, "init_waitqueue_head" },
	{ 0xb6c70a7d, "__wake_up" },
	{ 0x8085c7b1, "prepare_to_wait" },
	{ 0x51493d94, "finish_wait" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

