#define WPA_SUPPLICANT_CONFIG 	"/tmp/wpa_supplicant.conf"
#define WPA_SUPPLICANT_PIDFILE	"/tmp/wpa_supplicant.pid"

struct SITE_OBJ *wireless_driver_wext_get_scan_results(struct wireless_driver_ops *wlan, int *cnt, WIRELESS_MODE mode);
void wireless_driver_wext_scan_completed();
int wireless_driver_wext_set_ssid(struct wireless_driver_ops *wlan, const char *ssid, int ssid_len);
int wireless_driver_wext_scan(struct wireless_driver_ops *wlan, const char *ssid, int ssid_len);
int wireless_driver_wext_get_signal_strength(struct wireless_driver_ops *wlan, int *signal);
void wireless_driver_wext_down(struct wireless_driver_ops *wlan);
int wireless_driver_wext_do_assocate(struct wireless_driver_ops *wlan);
int wireless_driver_wext_getlinkstatus(struct wireless_driver_ops *wlan, int *status);
void wireless_driver_wext_set_scan_completed_cb(struct wireless_driver_ops *wlan, void (*cb)(void *user_data), void *user_data);
void wireless_driver_wext_linkup(struct wireless_driver_ops *wlan);
void wireless_driver_wext_linkdown(struct wireless_driver_ops *wlan);
void wireless_driver_wext_scan_completed_wrap(struct wireless_driver_ops *wlan);
void wireless_driver_wext_reset(struct wireless_driver_ops *wlan);
void wireless_driver_wext_init(struct wireless_driver_ops *wlan);
int wireless_driver_wext_wps_pin_enrollee_get_code(struct wireless_driver_ops *wlan, char *code, int len);
