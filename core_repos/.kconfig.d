deps_config := \
	config/Config_features_IOS_APP.in \
	config/Config_external_packages.in \
	config/Config_firmware_maker.in \
	config/Config_rootfs_primary_system_installer.in \
	config/Config_rootfs_installer.in \
	config/Config_features_rally.in \
	config/Config_features_drm.in \
	config/Config_features_dlna.in \
	Config.in

.config include/autoconf.h: $(deps_config)

$(deps_config):
