ifneq '$(filter -DEM86XX_MODE=EM86XX_MODEID_STANDALONE, $(RMCFLAGS))' ''

ifneq '$(filter -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3,$(RMCFLAGS))' ''

ifeq '$(filter android, $(COMPILKIND))' ''
lib_ext    := so
else
lib_ext := a
endif

else
ifneq '$(filter -DEM86XX_CHIP=EM86XX_CHIPID_TANGO2,$(RMCFLAGS))' ''

lib_ext    := so

else  # CHIPID_TANGO2

lib_ext    := a

endif # CHIPID_TANGO2
endif

else  # MODEID_STANDALONE
ifneq '$(filter -DEM86XX_MODE=EM86XX_MODEID_WITHHOST,$(RMCFLAGS))' ''

ifndef RMPLATFORM
RMPLATFORM := RMPLATFORMID_PCLINUX
export RMPLATFORM
endif
LINKER  := g++
lib_ext := so

else  # MODEID_WITHHOST

$(error EM86XX_MODE is not set in RMCFLAGS: refer to emhwlib/include/emhwlib_modes.h)

endif # MODEID_WITHHOST
endif # MODEID_STANDALONE

COMPILKIND += withoutdbg
RMCFLAGS +=                      \
    -DMAMBO=1                    \
    -DRMVDEMUX_LOCAL_RMOBJECT=1  \
    -DBASIC_MPEG4_FRAMEWORK=1    \
    -DBASIC_DETECTOR_FRAMEWORK=1 \
    -D_FILE_OFFSET_BITS=64

.PHONY: all
all:

libdcc     := libdcc.$(lib_ext)
libdcc_lib := ../MRUA_src/dcc/src/$(libdcc)
$(libdcc): $(libdcc_lib)

librmmonitoring     := librmmonitoring.$(lib_ext)
librmmonitoring_lib := ../MRUA_src/librmmonitoring/src/$(librmmonitoring)
$(librmmonitoring): $(librmmonitoring_lib)

librmjpeg     := librmjpeg.$(lib_ext)
librmjpeg_lib := ../MRUA_src/rmlibjpeg/src/$(librmjpeg)
$(librmjpeg): $(librmjpeg_lib)

librmpng     := librmpng.$(lib_ext)
librmpng_lib := ../MRUA_src/rmlibpng/src/$(librmpng)
$(librmpng): $(librmpng_lib)

librmungif     := librmungif.$(lib_ext)
librmungif_lib := ../MRUA_src/rmlibungif/src/$(librmungif)
$(librmungif): $(librmungif_lib)

librmzlib     := librmzlib.$(lib_ext)
librmzlib_lib := ../MRUA_src/rmzlib/src/$(librmzlib)
$(librmzlib): $(librmzlib_lib)

librmhttp     := librmhttp.$(lib_ext)
librmhttp_lib := ../MRUA_src/rmlibhttp/src/$(librmhttp)
$(librmhttp): $(librmhttp_lib)

librmcurl     := librmcurl.$(lib_ext)
librmcurl_lib := ../MRUA_src/rmlibcurl/src/$(librmcurl)
$(librmcurl): $(librmcurl_lib)

librmflv     := librmflv.$(lib_ext)
librmflv_lib := ../MRUA_src/rmflv/src/$(librmflv)
$(librmflv): $(librmflv_lib)

librmcw     := librmcw.$(lib_ext)
librmcw_lib := ../MRUA_src/rmlibcw/src_linux/$(librmcw)
$(librmcw): $(librmcw_lib)

librmpthreadw     := librmpthreadw.$(lib_ext)
librmpthreadw_lib := ../MRUA_src/librmpthreadw/$(librmpthreadw)
$(librmpthreadw): $(librmpthreadw_lib)

librmrtk     := librmrtk86.$(lib_ext)
librmrtk_lib := ../MRUA_src/rmrtk/src_86/$(librmrtk)
$(librmrtk): $(librmrtk_lib)

librmcore     := librmcore.$(lib_ext)
librmcore_lib := ../MRUA_src/rmcore/src/$(librmcore)
$(librmcore): $(librmcore_lib)

librmdemuxwritekeyapi := librmdemuxwritekeyapi.$(lib_ext)
librmdemuxwritekeyapi_lib := ../MRUA_src/rmdemuxwritekey/$(librmdemuxwritekeyapi)
$(librmdemuxwritekeyapi): $(librmdemuxwritekeyapi_lib)

librmremote     := librmremote.$(lib_ext)
librmremote_lib := ../MRUA_src/rmremoteapi/externalapi/$(librmremote)
$(librmremote): $(librmremote_lib)

librmasfdemux     := librmasfdemux.$(lib_ext)
librmasfdemux_lib := ../MRUA_src/rmasfdemux/src/$(librmasfdemux)
$(librmasfdemux): $(librmasfdemux_lib)

librmcssinterface     := librmcssinterface.$(lib_ext)
librmcssinterface_lib := ../MRUA_src/rmcss/$(librmcssinterface)
$(librmcssinterface): $(librmcssinterface_lib)

librmcprminterface     := librmcprminterface.$(lib_ext)
librmcprminterface_lib := ../MRUA_src/rmcprm/src/$(librmcprminterface)
$(librmcprminterface): $(librmcprminterface_lib)

librmbluraycps     := librmbluraycps.$(lib_ext)
librmbluraycps_lib := ../MRUA_src/rmbluraycps/src/$(librmbluraycps)
$(librmbluraycps): $(librmbluraycps_lib)

librmspdcapi     := librmspdcapi.$(lib_ext)
librmspdcapi_lib := ../MRUA_src/rmspdcapi/src/$(librmspdcapi)
$(librmspdcapi): $(librmspdcapi_lib)

librmaacsapi     := librmaacsapi.$(lib_ext)
librmaacsapi_lib := ../MRUA_src/rmaacsapi/src/$(librmaacsapi)
$(librmaacsapi): $(librmaacsapi_lib)

libgbus     := libgbus.$(lib_ext)
libgbus_lib := ../MRUA_src/gbuslib/src/$(libgbus)
$(libgbus): $(libgbus_lib)

librmppf     := librmppf.$(lib_ext)
librmppf_lib := ../MRUA_src/rmppf/src/$(librmppf)
$(librmppf): $(librmppf_lib)

ifneq '$(filter -DEM86XX_CHIP=EM86XX_CHIPID_TANGO2,$(RMCFLAGS))' ''
librmdtcpinterface        := librmdtcpinterface.$(lib_ext)
librmdtcpinterface_lib    := ../MRUA_src/rmdtcpapi/src/$(librmdtcpinterface)
$(librmdtcpinterface)     : $(librmdtcpinterface_lib)
else #TANGO2
ifneq '$(filter -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3,$(RMCFLAGS))' ''
librmdtcpapi     := librmdtcpapi.$(lib_ext)
librmdtcpapi_lib := ../MRUA_src/rmdtcpapi/src/$(librmdtcpapi)
$(librmdtcpapi): $(librmdtcpapi_lib)
endif #TANGO3
endif #TANGO2

librmxpurtcapi     := librmxpurtcapi.$(lib_ext)
librmxpurtcapi_lib := ../MRUA_src/rmxpurtcapi/src/$(librmxpurtcapi)
$(librmxpurtcapi): $(librmxpurtcapi_lib)

librmcapture     := librmcapture.$(lib_ext)
librmcapture_lib := ../MRUA_src/rmcapture/src/$(librmcapture)
$(librmcapture_lib): $(libgbus)
$(librmcapture): $(librmcapture_lib)

librmchannel    := librmchannel.$(lib_ext)
librmchannel_lib := ../MRUA_src/rmchannel/src/librmchannel/$(librmchannel)
$(librmchannel): $(librmchannel_lib)

librmi2c     := librmi2c.$(lib_ext)
librmi2c_lib := ../MRUA_src/rmi2c/src/$(librmi2c)
$(librmi2c): $(librmi2c_lib)

librmhdmi     := librmhdmi.$(lib_ext)
librmhdmi_lib := ../MRUA_src/rmhdmi/src/$(librmhdmi)
$(librmhdmi_lib): $(librmi2c_lib)
$(librmhdmi): $(librmhdmi_lib)

libruahdmi     := libruahdmi.$(lib_ext)
libruahdmi_lib := ../MRUA_src/rmhdmi/rua/src/$(libruahdmi)
$(libruahdmi): $(libruahdmi_lib)

libemhwlibhdmi     := libemhwlibhdmi.$(lib_ext)
libemhwlibhdmi_lib := ../MRUA_src/rmhdmi/emhwlib/src/$(libemhwlibhdmi)
$(libemhwlibhdmi): $(libemhwlibhdmi_lib)

librmedid     := librmedid.$(lib_ext)
librmedid_lib := ../MRUA_src/rmedid/src/$(librmedid)
$(librmedid): $(librmedid_lib)

libruai2c     := libruai2c.$(lib_ext)
libruai2c_lib := ../MRUA_src/rmi2c/rua_src/$(libruai2c)
$(libruai2c): $(libruai2c_lib)

libemhwlibi2c     := libemhwlibi2c.$(lib_ext)
libemhwlibi2c_lib := ../MRUA_src/rmi2c/emhwlib_i2c/$(libemhwlibi2c)
$(libemhwlibi2c): $(libemhwlibi2c_lib)

librmsha1     := librmsha1.$(lib_ext)
librmsha1_lib := ../MRUA_src/rmsha1/src/$(librmsha1)
$(librmsha1): $(librmsha1_lib)

librmcec     := librmcec.$(lib_ext)
librmcec_lib := ../MRUA_src/rmcec/src/$(librmcec)
$(librmcec): $(librmcec_lib)

librmhsi     := librmhsi.$(lib_ext)
librmhsi_lib := ../MRUA_src/rmhsi/src/$(librmhsi)
$(librmhsi): $(librmhsi_lib)

libruahsi     := libruahsi.$(lib_ext)
libruahsi_lib := ../MRUA_src/rmhsi/rua_src/src/$(libruahsi)
$(libruahsi_lib): $(librmhsi)
$(libruahsi): $(libruahsi_lib)

libemhsi     := libemhsi.$(lib_ext)
libemhsi_lib := ../MRUA_src/rmhsi/emhwlib_src/src/$(libemhsi)
$(libemhsi_lib): $(librmhsi)
$(libemhsi): $(libemhsi_lib)

libgbushsi     := libgbushsi.$(lib_ext)
libgbushsi_lib := ../MRUA_src/rmhsi/gbus_src/src/$(libgbushsi)
$(libgbushsi_lib): $(librmhsi)
$(libgbushsi): $(libgbushsi_lib)

librmdisplay     := librmdisplay.$(lib_ext)
librmdisplay_lib := ../MRUA_src/rmdisplay/src/$(librmdisplay)
$(librmdisplay): $(librmdisplay_lib)

libdisplayoutports     := libdisplayoutports.$(lib_ext)
libdisplayoutports_lib := ../MRUA_src/rmoutports/display_src/$(libdisplayoutports)
$(libdisplayoutports): $(libdisplayoutports_lib)

libaudiooutports     := libaudiooutports.$(lib_ext)
libaudiooutports_lib := ../MRUA_src/rmoutports/audio_src/$(libaudiooutports)
$(libaudiooutports): $(libaudiooutports_lib)

librmvideoout     := librmvideoout.$(lib_ext)
librmvideoout_lib := ../MRUA_src/rmvideoout/src/$(librmvideoout)
$(librmvideoout): $(librmvideoout_lib)

librmlibplay := librmlibplay.$(lib_ext)
librmlibplay_lib := ../MRUA_src/rmlibplay/src/$(librmlibplay)
ifneq '$(filter codesourcery, $(COMPILKIND))' ''
$(librmlibplay_lib): $(librmfontrender) $(librmzlib)
else
$(librmlibplay_lib): $(librmpng) $(librmzlib) $(librmungif) $(librmjpeg) $(librmfontrender)
endif
$(librmlibplay): $(librmlibplay_lib)

librmlibplay_t := librmlibplay_t.$(lib_ext)
librmlibplay_t_lib := ../MRUA_src/rmlibplay/src_t/$(librmlibplay_t)
ifneq '$(filter codesourcery, $(COMPILKIND))' ''
$(librmlibplay_t_lib): $(librmfontrender) $(librmzlib)
else
$(librmlibplay_t_lib): $(librmpng) $(librmzlib) $(librmungif) $(librmjpeg) $(librmfontrender)
endif
$(librmlibplay_t): $(librmlibplay_t_lib)

librmlibplay_default_plugin := librmlibplay_default_plugin.$(lib_ext)
librmlibplay_default_plugin_lib := ../MRUA_src/rmlibplay/plugins/default/$(librmlibplay_default_plugin)
$(librmlibplay_default_plugin_lib): $(librmlibplay)
$(librmlibplay_default_plugin): $(librmlibplay_default_plugin_lib)

librmlibplay_sample_plugin := librmlibplay_sample_plugin.$(lib_ext)
librmlibplay_sample_plugin_lib := ../MRUA_src/rmlibplay/plugins/sample/$(librmlibplay_sample_plugin)
$(librmlibplay_sample_plugin_lib): $(librmlibplay)
$(librmlibplay_sample_plugin): $(librmlibplay_sample_plugin_lib)

librmfp := librmfp.$(lib_ext)
librmfp_lib := ../MRUA_src/rmfp/src/$(librmfp)
$(librmfp_lib): $(librmlibplay)
$(librmfp): $(librmfp_lib)

librmfp_t := librmfp_t.$(lib_ext)
librmfp_t_lib := ../MRUA_src/rmfp/src_t/$(librmfp_t)
$(librmfp_t_lib): $(librmlibplay_t)
$(librmfp_t): $(librmfp_t_lib)

libsamples     := libsamples.$(lib_ext)
libsamples_lib := ../MRUA_src/samples/libsamples/$(libsamples)
$(libsamples_lib): $(librmdisplay) $(librmvideoout) $(libaudiooutports) $(libdisplayoutports) $(librmppf)
$(libsamples): $(libsamples_lib)

libsamples_t     := libsamples_t.$(lib_ext)
libsamples_t_lib := ../MRUA_src/samples/libsamples_t/$(libsamples_t)
$(libsamples_t_lib): $(librmdisplay) $(librmvideoout) $(libaudiooutports) $(libdisplayoutports) $(librmppf)
$(libsamples_t): $(libsamples_t_lib)


libs := \
    $(libdcc_lib)		\
    $(libsamples_lib)		\
    $(libsamples_t_lib)         \
    $(librmmonitoring_lib)	\
    $(librmzlib_lib)		\
    $(librmhttp_lib)		\
    $(librmcw_lib)		\
    $(librmpthreadw_lib)	\
    $(librmrtk_lib)		\
    $(librmcore_lib)		\
    $(librmremote_lib)		\
    $(librmasfdemux_lib)	\
    $(librmcapture_lib)

ifeq '$(filter codesourcery, $(COMPILKIND))' ''
libs += \
    $(librmjpeg_lib)		\
    $(librmungif_lib)		\
    $(librmpng_lib)
endif

ifneq '$(filter -DEM86XX_CHIP=EM86XX_CHIPID_TANGO2, $(RMCFLAGS))' ''
libs += \
    $(librmppf_lib)		\
    $(librmcssinterface_lib)	\
    $(librmcprminterface_lib)	\
    $(librmbluraycps_lib)	\
    $(librmspdcapi_lib)		\
    $(librmaacsapi_lib)		\
    $(librmdtcpinterface_lib) 	\
    $(librmxpurtcapi_lib)

ifneq '$(filter -DEM86XX_MODE=EM86XX_MODEID_STANDALONE, $(RMCFLAGS))' ''
libs += \
    $(librmdemuxwritekeyapi_lib)
endif
endif

ifneq '$(filter -DEM86XX_CHIP=EM86XX_CHIPID_TANGO2 -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3, $(RMCFLAGS))' ''
libs += \
    $(librmflv_lib)                     \
    $(librmlibplay_lib)                 \
    $(librmlibplay_t_lib)               \
    $(librmlibplay_default_plugin_lib)  \
    $(librmlibplay_sample_plugin_lib)   \
    $(librmfp_lib)                      \
    $(librmfp_t_lib)
endif

ifneq '$(filter -DEM86XX_CHIP=EM86XX_CHIPID_TANGO3, $(RMCFLAGS))' ''
libs += \
    $(librmchannel_lib)

ifneq '$(wildcard $(SMP86XX_ROOTFS_PATH)/cross_rootfs/include/curl/curl.h)' ''
libs += \
    $(librmcurl_lib)
endif

endif

libs += \
    $(libgbus_lib)
    
libs += \
   $(librmhdmi_lib) \
   $(librmedid_lib) \
   $(librmi2c_lib)  \
   $(libruai2c_lib) \
   $(libemhwlibi2c_lib) \
   $(librmsha1_lib) \
   $(librmcec_lib)  \
   $(libruahdmi_lib) \
   $(libemhwlibhdmi_lib) \
   $(librmhsi_lib) \
   $(libruahsi_lib) \
   $(libemhsi_lib) \
   $(libgbushsi_lib) \
   $(librmdisplay_lib)\
   $(libdisplayoutports_lib) \
   $(libaudiooutports_lib) \
   $(librmvideoout_lib) 

ifneq '$(filter android, $(COMPILKIND))' ''
libcore    := libcore.so
libcore_lib := ../MRUA_src/rmlibpack/libcore/src/$(libcore)
$(libcore): $(libcore_lib)

libdisplay    := libdisplay.so
libdisplay_lib := ../MRUA_src/rmlibpack/libdisplay/src/$(libdisplay)
$(libdisplay): $(libdisplay_lib)

libdrm    := libdrm.so
libdrm_lib := ../MRUA_src/rmlibpack/libdrm/src/$(libdrm)
$(libdrm): $(libdrm_lib)

libhw    := libhw.so
libhw_lib := ../MRUA_src/rmlibpack/libhw/src/$(libhw)
$(libhw): $(libhw_lib)

libplayback    := libplayback.so
libplayback_lib := ../MRUA_src/rmlibpack/libplayback/src/$(libplayback)
$(libplayback): $(libplayback_lib)

libs_pack = \
	$(libcore_lib) \
	$(libdisplay_lib) \
	$(libdrm_lib) \
	$(libhw_lib) \
	$(libplayback_lib)

libpack_targets := $(notdir $(libs_pack))
libpack_clean := $(libpack_targets:%=%_clean)
libpack_cleanall := $(libs_pack:%=%_cleanall)

endif

lib_targets  := $(notdir $(libs))
lib_clean    := $(lib_targets:%=%_clean)
lib_cleanall := $(libs:%=%_cleanall)

##
# Note: the dependency of target all on $(lib_list) was removed to resolve
# the request in bug #4102. It effectively renders the Makefile ineffectual
# (all the targets likely to be called by the Makefile system, 'all', 'clean'
# and 'cleanrelease' just do nothing, but the Makefile is still useful.
#ifeq '$(filter android, $(COMPILKIND))' ''
#all: $(lib_targets)
#else
#all: $(lib_targets) $(libpack_targets)
#endif

$(lib_targets):
	cp $< $@

$(libs): FORCE
	$(MAKE) -C $(@D)

ifneq '$(filter android, $(COMPILKIND))' ''
$(libpack_targets):
	cp $< $@

$(libs_pack): FORCE
	$(MAKE) -C $(@D)
endif

.PHONY: $(lib_clean)
$(lib_clean):
	$(RM) $(subst _clean,,$@)

.PHONY: $(lib_cleanall)
$(lib_cleanall):
	$(MAKE) -C $(@D) cleanall

ifneq '$(filter android, $(COMPILKIND))' ''
.PHONY: $(libpack_clean)
$(libpack_clean):
	$(RM) $(subst _clean,,$@)

.PHONY: $(libpack_cleanall)
$(libpack_cleanall):
	$(MAKE) -C $(@D) -f Makefile cleanall
endif

.PHONY: FORCE
FORCE:

.PHONY: clean
clean:

.PHONY: cleanall
cleanall: clean

##
# Note: because the all target does not build all the libs in this directory 
# (in order to address the request in bug #4102), the clean and cleanall
# targets cannot clean anything.
# As with the building of libraries, individual libraries can still be cleaned
# individually.
#ifeq '$(filter android, $(COMPILKIND))' ''
#clean: $(lib_clean)
#else
#clean: $(lib_clean) $(libpack_clean)
#endif
#
#ifeq '$(filter android, $(COMPILKIND))' ''
#cleanall: clean $(lib_cleanall)
#else
#cleanall: clean $(lib_cleanall) $(libpack_cleanall)
#endif

