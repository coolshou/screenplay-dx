include $(RT28xx_DIR)/os/linux/config.mk


#ifdef CONFIG_STA_SUPPORT
ifeq ($(RT28xx_MODE), STA)
MOD_NAME = rt$(CHIPSET)sta
DAT_PATH = /etc/Wireless/RT$(CHIPSET_DAT)STA
DAT_FILE_NAME = RT$(CHIPSET_DAT)STA.dat
endif
#endif // CONFIG_STA_SUPPORT //


obj-m := $(MOD_NAME).o


#ifdef CONFIG_STA_SUPPORT
rt$(CHIPSET)sta-objs := \
	../../common/crypt_md5.o\
	../../common/crypt_sha2.o\
	../../common/crypt_hmac.o\
	../../common/crypt_aes.o\
	../../common/crypt_arc4.o\
	../../common/mlme.o\
	../../common/cmm_wep.o\
	../../common/action.o\
	../../common/cmm_data.o\
	../../common/rtmp_init.o\
	../../common/rtmp_init_inf.o\
	../../common/cmm_tkip.o\
	../../common/cmm_aes.o\
	../../common/cmm_sync.o\
	../../common/eeprom.o\
	../../common/cmm_sanity.o\
	../../common/cmm_info.o\
	../../common/cmm_cfg.o\
	../../common/cmm_wpa.o\
	../../common/dfs.o\
	../../common/spectrum.o\
	../../common/rtmp_timer.o\
	../../common/rt_channel.o\
	../../common/cmm_profile.o\
	../../common/cmm_asic.o\
	../../common/cmm_cmd.o\
	../../os/linux/rt_profile.o\
	../../chips/rtmp_chip.o\
	../../sta/assoc.o\
	../../sta/auth.o\
	../../sta/auth_rsp.o\
	../../sta/sync.o\
	../../sta/sanity.o\
	../../sta/rtmp_data.o\
	../../sta/connect.o\
	../../sta/wpa.o\
	../../sta/ags.o\
	../../sta/sta_cfg.o

ifeq ($(OSABL),NO)
rt$(CHIPSET)sta-objs += \
	../../common/rt_os_util.o\
	../../os/linux/sta_ioctl.o\
	../../os/linux/rt_linux.o\
	../../os/linux/rt_main_dev.o
else
rt$(CHIPSET)sta-objs += \
	../../os/linux/rt_symb.o
endif

#ifdef DOT11_N_SUPPORT
ifeq ($(HAS_DOT11_N_SUPPORT),y)
rt$(CHIPSET)sta-objs += \
	../../common/ba_action.o
endif
#endif // DOT11_N_SUPPORT //

#ifdef ADHOC_WPA2PSK_SUPPORT
rt$(CHIPSET)sta-objs += \
	../../common/cmm_wpa_adhoc.o
#endif // ADHOC_WPA2PSK_SUPPORT //

#ifdef WSC_INCLUDED
ifeq ($(HAS_WSC),y)
rt$(CHIPSET)sta-objs += \
	../../common/wsc.o\
	../../common/wsc_tlv.o\
	../../common/crypt_biginteger.o\
	../../common/crypt_dh.o
endif
ifeq ($(HAS_WSC_V2),y)
rt$(CHIPSET)sta-objs += ../../common/wsc_v2.o
endif
#endif // WSC_INCLUDED //



ifeq ($(HAS_BLOCK_NET_IF),y)
rt$(CHIPSET)sta-objs += ../../common/netif_block.o
endif

ifeq ($(HAS_QOS_DLS_SUPPORT),y)
rt$(CHIPSET)sta-objs += ../../sta/dls.o
endif

#ifdef DOT11Z_TDLS_SUPPORT
ifeq ($(HAS_DOT11Z_TDLS_SUPPORT),y)
rt$(CHIPSET)sta-objs += \
	../../sta/tdls.o\
	../../sta/tdls_ctrl.o\
	../../sta/tdls_tlv.o\
	../../sta/tdls_link_mng.o
endif
#endif // DOT11Z_TDLS_SUPPORT //


#ifdef LED_CONTROL_SUPPORT
ifeq ($(HAS_LED_CONTROL_SUPPORT),y)
rt$(CHIPSET)sta-objs += \
	../../common/rt_led.o
endif
#endif // LED_CONTROL_SUPPORT //





#ifdef RT3070
ifeq ($(CHIPSET),2070)
rt$(CHIPSET)sta-objs += \
	../../common/cmm_mac_usb.o\
	../../common/rtusb_io.o\
	../../common/rtusb_data.o\
	../../common/cmm_data_usb.o\
	../../common/ee_prom.o\
	../../common/ee_efuse.o\
	../../common/rtmp_mcu.o\
	../../chips/rt30xx.o\
	../../common/rt_rf.o\
	../../common/rtusb_bulk.o\
	../../os/linux/rt_usb.o\
	../../chips/rt3070.o

ifeq ($(OSABL),NO)
rt$(CHIPSET)sta-objs += \
	../../common/rtusb_dev_id.o\
	../../os/linux/rt_usb_util.o\
	../../os/linux/usb_main_dev.o
endif
endif

ifeq ($(CHIPSET),3070)
rt$(CHIPSET)sta-objs += \
	../../common/cmm_mac_usb.o\
	../../common/rtusb_io.o\
	../../common/rtusb_data.o\
	../../common/cmm_data_usb.o\
	../../common/ee_prom.o\
	../../common/ee_efuse.o\
	../../common/rtmp_mcu.o\
	../../chips/rt30xx.o\
	../../common/rt_rf.o\
	../../common/rtusb_bulk.o\
	../../os/linux/rt_usb.o\
	../../chips/rt3070.o

ifeq ($(OSABL),NO)
rt$(CHIPSET)sta-objs += \
	../../common/rtusb_dev_id.o\
	../../os/linux/rt_usb_util.o\
	../../os/linux/usb_main_dev.o
endif
endif
#endif // RT3070 //





ifeq ($(HAS_ATE),y)
rt$(CHIPSET)sta-objs += ../../common/rt_ate.o
endif



#ifdef WAPI_SUPPORT
ifeq ($(HAS_WAPI_SUPPORT),y)
rt$(CHIPSET)sta-objs += \
	../../common/wapi.o
endif
#endif // WAPI_SUPPORT //



#ifdef P2P_SUPPORT
ifeq ($(OSABL),NO)
ifeq ($(HAS_P2P_SUPPORT),y)
rt$(CHIPSET)sta-objs += \
        ../../common/p2p_inf.o
endif
endif

ifeq ($(HAS_P2P_SUPPORT),y)
rt$(CHIPSET)sta-objs += \
	../../ap/ap_mbss.o\
	../../ap/ap.o\
	../../ap/ap_assoc.o\
	../../ap/ap_auth.o\
	../../ap/ap_connect.o\
	../../ap/ap_mlme.o\
	../../ap/ap_sanity.o\
	../../ap/ap_sync.o\
	../../ap/ap_wpa.o\
	../../ap/ap_data.o\
	../../ap/ap_uapsd.o\
	../../ap/ap_autoChSel.o\
	../../ap/ap_qload.o\
	../../sta/p2pcli.o \
	../../sta/p2pcli_ctrl.o \
	../../sta/p2pcli_sync.o \
	../../sta/p2pcli_auth.o \
	../../sta/p2pcli_assoc.o \
	../../common/cmm_mat.o \
	../../common/cmm_mat_iparp.o \
	../../common/cmm_mat_pppoe.o \
	../../common/cmm_mat_ipv6.o \
	../../common/p2p_dbg.o\
	../../common/p2p_cfg.o\
	../../common/p2p.o\
	../../common/p2p_packet.o\
	../../common/p2p_action.o\
	../../common/p2p_table.o\
	../../common/p2p_ctrl.o\
	../../common/p2p_disc_mng.o\
	../../common/p2p_nego_mng.o\
	../../common/p2p_dbg.o\
	../../common/p2p.o\
	../../common/p2p_packet.o\
	../../common/p2p_action.o\
	../../common/p2p_table.o\
	../../common/p2p_ctrl.o\
	../../common/p2p_disc_mng.o\
	../../common/p2p_nego_mng.o\
	../../common/wsc.o\
	../../common/wsc_tlv.o\
	../../common/wsc_ufd.o\
	../../common/crypt_biginteger.o\
	../../common/crypt_dh.o	

ifeq ($(HAS_QOS_DLS_SUPPORT),y)
rt$(CHIPSET)sta-objs += ../../ap/ap_dls.o
endif

endif

ifeq ($(HAS_P2P_SUPPORT),y)
ifeq ($(OSABL),NO)
rt$(CHIPSET)sta-objs += \
        ../../ap/ap_mbss_inf.o\
        ../../common/rt_os_util.o\
        ../../os/linux/ap_ioctl.o\
        ../../os/linux/sta_ioctl.o\
        ../../os/linux/rt_linux.o\
        ../../os/linux/rt_main_dev.o
else
rt$(CHIPSET)sta-objs += \
        ../../os/linux/rt_symb.o
endif
endif
#endif // P2P_SUPPORT //

#ifdef CRDA_SUPPORT
ifeq ($(OSABL),NO)
ifeq ($(HAS_CFG80211_SUPPORT),y)
rt$(CHIPSET)sta-objs += \
	../../os/linux/cfg80211.o \
	../../os/linux/cfg80211drv.o
endif
endif

ifeq ($(OSABL),YES)
ifeq ($(HAS_CFG80211_SUPPORT),y)
rt$(CHIPSET)sta-objs += \
	../../os/linux/cfg80211drv.o
endif
endif
#endif // CRDA_SUPPORT //


#endif // CONFIG_STA_SUPPORT //

PHONY := clean install uninstall

clean:
	rm -f ../../common/*.o
	rm -f ../../common/.*.{cmd,flags,d}
	rm -f ../../os/linux/*.{o,ko,mod.{o,c}}
	rm -f ../../os/linux/.*.{cmd,flags,d}
	rm -fr ../../os/linux/.tmp_versions
#Must clean Module.symvers; or you will suffer symbol version not match
#when OS_ABL = YES.
	rm -f ../../os/linux/Module.symvers
	rm -f ../../os/linux/Modules.symvers
	rm -f ../../os/linux/Module.markers
	rm -f ../../os/linux/modules.order
	rm -f ../../chips/*.o
	rm -f ../../chips/.*.{cmd,flags,d}
ifeq ($(RT28xx_MODE),AP)
	rm -f ../../ap/*.o
	rm -f ../../ap/.*.{cmd,flags,d}
else
ifeq ($(RT28xx_MODE),STA)
	rm -f ../../sta/*.o
	rm -f ../../sta/.*.{cmd,flags,d}
else
ifeq ($(RT28xx_MODE),APSTA)
	rm -f ../../ap/*.o
	rm -f ../../ap/.*.{cmd,flags,d}
	rm -f ../../sta/*.o
	rm -f ../../sta/.*.{cmd,flags,d}
endif
endif
endif

install:
	rm -rf $(DAT_PATH)
	$(shell [ ! -f /etc/Wireless ] && mkdir /etc/Wireless)
	mkdir $(DAT_PATH)
	cp $(RT28xx_DIR)/../$(DAT_FILE_NAME) $(DAT_PATH)/.
	install -d $(LINUX_SRC_MODULE)
	install -m 644 -c $(addsuffix .ko,$(MOD_NAME)) $(LINUX_SRC_MODULE)
	/sbin/depmod -a ${shell uname -r}

uninstall:
#	rm -rf $(DAT_PATH)
	rm -rf $(addprefix $(LINUX_SRC_MODULE),$(addsuffix .ko,$(MOD_NAME)))
	/sbin/depmod -a ${shell uname -r}

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)
