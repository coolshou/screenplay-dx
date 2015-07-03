#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0xc906a5e1, "struct_module" },
	{ 0xf31fd6bb, "register_netdevice" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x9afe9c91, "__mod_timer" },
	{ 0xf9a482f9, "msleep" },
	{ 0x1c55c6fe, "usb_buffer_alloc" },
	{ 0x8e9eceaa, "complete_and_exit" },
	{ 0xad5381d9, "__invoke_copy_to_user_dma" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x6f7da10b, "alloc_etherdev" },
	{ 0x75b38522, "del_timer" },
	{ 0x97255bdf, "strlen" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x78c0ffec, "__down_interruptible" },
	{ 0x6337d4ed, "malloc_sizes" },
	{ 0x36e47222, "remove_wait_queue" },
	{ 0x267fc65b, "__tasklet_hi_schedule" },
	{ 0xf34bcee6, "skb_clone" },
	{ 0xae76a19, "dev_get_by_name" },
	{ 0x1e36b86a, "skb_copy" },
	{ 0xb63c7bcc, "usb_buffer_free" },
	{ 0x6a963dd8, "usb_kill_urb" },
	{ 0xfc23d580, "filp_close" },
	{ 0x3fe5fc36, "__up" },
	{ 0x2fd1d81c, "vfree" },
	{ 0x3d804915, "__invoke_copy_from_user_dma" },
	{ 0x1d26aa98, "sprintf" },
	{ 0x7d11c268, "jiffies" },
	{ 0xc83f347e, "netif_rx" },
	{ 0xffd5a395, "default_wake_function" },
	{ 0x25fa6f17, "wait_for_completion" },
	{ 0x2bc95bd4, "memset" },
	{ 0x1ae0453e, "usb_deregister" },
	{ 0xdd132261, "printk" },
	{ 0x6f336f4f, "free_netdev" },
	{ 0xcaaf8f41, "register_netdev" },
	{ 0xe67e56f, "wireless_send_event" },
	{ 0x9d98881a, "usb_control_msg" },
	{ 0x2b6a4676, "dev_close" },
	{ 0xa5808bbf, "tasklet_init" },
	{ 0x20187c7, "mod_timer" },
	{ 0x874361f8, "cpu_data" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x53cddf70, "dev_kfree_skb_any" },
	{ 0xd79b5a02, "allow_signal" },
	{ 0x61651be, "strcat" },
	{ 0x79ad224b, "tasklet_kill" },
	{ 0xa641da9a, "skb_over_panic" },
	{ 0x3ff62317, "local_bh_disable" },
	{ 0x2b2f4588, "skb_copy_expand" },
	{ 0xbac83868, "usb_submit_urb" },
	{ 0xde1ebd5e, "kmem_cache_alloc" },
	{ 0x733cc626, "__alloc_skb" },
	{ 0xc76cfcb7, "usb_get_dev" },
	{ 0xd54d4778, "usb_put_dev" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0x799aca4, "local_bh_enable" },
	{ 0x2114eb9, "skb_under_panic" },
	{ 0x15e6b344, "eth_type_trans" },
	{ 0xd43e33a6, "pskb_expand_head" },
	{ 0x6cb34e5, "init_waitqueue_head" },
	{ 0x35fe47a1, "init_timer" },
	{ 0xfd8dba4c, "add_wait_queue" },
	{ 0x37a0cba, "kfree" },
	{ 0x932da67e, "kill_proc" },
	{ 0x11f7ce5e, "memcpy" },
	{ 0x8085c7b1, "prepare_to_wait" },
	{ 0x9f22848e, "usb_register_driver" },
	{ 0x51493d94, "finish_wait" },
	{ 0x7ca341af, "kernel_thread" },
	{ 0x204cf6f1, "unregister_netdev" },
	{ 0xb742fd7, "simple_strtol" },
	{ 0xcdb96621, "tangox_udelay" },
	{ 0xa218bf61, "complete" },
	{ 0x25da070, "snprintf" },
	{ 0xdee2153d, "__netif_schedule" },
	{ 0xaa39f95c, "memmove" },
	{ 0x4eb56f72, "usb_free_urb" },
	{ 0xdc43a9c8, "daemonize" },
	{ 0x41cb395, "usb_alloc_urb" },
	{ 0xea673de1, "filp_open" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

