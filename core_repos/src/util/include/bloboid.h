/*
 *      IMPORTANT--READ CAREFULLY: The use, reproduction, modification, and
 *      creation of derivative works of this Source Code ("Document") is
 *      governed by a TECHNOLOGY LICENSE AGREEMENT("Agreement"), a legal
 *      agreement between you (either an individual or a single entity) and
 *      No Wires Needed B.V. ("NWN").  By reproducing, modifying, creating
 *      derivative works, accepting, installing, viewing, accessing,
 *      transforming or otherwise using this Document, you agree to be bound
 *      by the terms of the Agreement.  If you do not agree to the terms of
 *      the Agreement, NWN is unwilling to license the rights to use,
 *      reproduce, modify, and create derivative works of this Document to you.
 *      In such event, you may not use, reproduce, modify, create derivative
 *      works, install, view, access, transport, transform or circulate this
 *      Document, and you should promptly contact NWN or the licensor from
 *      which you acquired this Document for instructions on returning or
 *      destroying this Document.
 *
 *      CONFIDENTIAL, PROPRIETARY AND TRADE SECRET INFORMATION:  This Source
 *      Code software contains confidential, proprietary and trade secret
 *      information of No Wires Needed B.V. and should be treated in a
 *      confidential manner.  Furthermore, this Source Code software is
 *      protected by United States copyright laws and international treaties.
 *      Unauthorized use, reproduction, modification, creation of derivative
 *      works or circulation is strictly prohibited.
 *
 *      Copyright (C) 1994-2000 by No Wires Needed B.V. (NWN), The Netherlands,
 *      ALL RIGHTS RESERVED
 *
 */

/*
 * Generic OIDs
 */

#define GEN_OID_MACADDRESS              "0x00000000"
#define GEN_OID_LINKSTATE               "0x00000001"
#define GEN_OID_WATCHDOG                "0x00000002"
#define GEN_OID_MIBOP                   "0x00000003"
#define GEN_OID_OPTIONS                 "0x00000004"
#define GEN_OID_LEDCONFIG               "0x00000005"

#define GEN_OID_MSDUTXSUCCESSFUL        "0x01000000"
#define GEN_OID_MSDUTXMULTICAST         "0x01000001"
#define GEN_OID_MSDUTXDROPPED           "0x01000002"
#define GEN_OID_MSDUTXFAILED            "0x01000003"
#define GEN_OID_MSDURXSUCCESSFUL        "0x01000004"
#define GEN_OID_MSDURXMULTICAST         "0x01000005"
#define GEN_OID_MSDURXDROPPED           "0x01000006"
#define GEN_OID_MSDURXFAILED            "0x01000007"


/*
 * Blob OIDs
 */

#define BLOB_OID_80000000
#define BLOB_OID_80000001
#define BLOB_OID_80000002
#define BLOB_OID_80000003
#define BLOB_OID_TIMESTAMP              "0x80000004"
#define BLOB_OID_GPIOBANK               "0x80000005"
#define BLOB_OID_GPIOWM                 "0x80000006"
#define BLOB_OID_GPIODATA               "0x80000007"
#define BLOB_OID_GPIOSTATUS             "0x80000008"
#define BLOB_OID_GPIODDR                "0x80000009"
#define BLOB_OID_RANDOMDATA             "0x80000010"

#define BLOB_OID_NVID                   "0x81000000"
#define BLOB_OID_NVOFFSET               "0x81000001"
#define BLOB_OID_NVSIZE                 "0x81000002"
#define BLOB_OID_NVDATA                 "0x81000003"

/*
 * Host/DS definitions
 */

#define HOSTDS_OPTION_WDS               "0x00000001"

/*
 * 802.11 definitions
 */

#define DOT11_SCAN_PASSIVE              "0"
#define DOT11_SCAN_ACTIVE               "1"
#define DOT11_SCAN_SELECTIVE		"2"

#define DOT11_SCAN_MASK_ACTIVE		"0x8000"

#define DOT11_BSSTYPE_NONE              "0"
#define DOT11_BSSTYPE_INFRA             "1"
#define DOT11_BSSTYPE_IBSS              "2"
#define DOT11_BSSTYPE_ANY               "3"

#define DOT11_STATE_NONE                "0"
#define DOT11_STATE_AUTHING             "1"
#define DOT11_STATE_AUTH                "2"
#define DOT11_STATE_ASSOCING            "3"
#define DOT11_STATE_ASSOC               "5"
#define DOT11_STATE_IBSS                "6"
#define DOT11_STATE_WDS			"7"

#define DOT11_NODE_UNKNOWN              "0"
#define DOT11_NODE_AP                   "1"
#define DOT11_NODE_CLIENT               "2"

#define DOT11_AUTH_NONE                 "0x0000"
#define DOT11_AUTH_OS                   "0x0001"
#define DOT11_AUTH_SK                   "0x0002"
#define DOT11_AUTH_BOTH                 "0x0003"

#define DOT11_AUTHALGNR_OS              "0"
#define DOT11_AUTHALGNR_SK              "1"

/* Key type */
#define DOT11_PRIV_WEP                  "0"
#define DOT11_PRIV_TKIP			"1"

#define DOT11_PSM_ACTIVE                "0"
#define DOT11_PSM_POWERSAVE             "1"
#define DOT11_PSM_DYNAMIC               "2"

#define DOT11_RP_NONE                   "0"
#define DOT11_RP_DOT11G                 "1"
#define DOT11_RP_DOT11A                 "2"

#define DOT11_RATEMASK                  "0x7f"
#define DOT11_BASICRATE                 "0x80"

#define DOT11_MLME_AUTO                 "0"
#define DOT11_MLME_INTERMEDIATE         "1"
#define DOT11_MLME_EXTENDED             "2"

#define DOT11_ALOFT_RATEMASK            "0x3f"
#define DOT11_ALOFT_RTS                 "0x40"

#define DOT11_DIVERSITY_NONE            "0"
#define DOT11_DIVERSITY_RX              "1"
#define DOT11_DIVERSITY_TX              "2"
#define DOT11_DIVERSITY_BOTH            "3"

#define DOT11_CCA_ED                    "0x0001"
#define DOT11_CCA_CS                    "0x0002"
#define DOT11_CCA_EDANDCS               "0x0004"

#define DOT11_PREAMBLESETTING_LONG      "0"
#define DOT11_PREAMBLESETTING_SHORT     "1"
#define DOT11_PREAMBLESETTING_DYNAMIC   "2"

#define DOT11_ACTIVITY_ED		"0x01"
#define DOT11_ACTIVITY_ERRORS		"0x02"
#define DOT11_ACTIVITY_ERRORLESS	"0x04"
#define DOT11_ACTIVITY_IBSS		"0x08"
#define DOT11_ACTIVITY_INFRA		"0x10"

#define DOT11_NONERP_NEVER              "0"
#define DOT11_NONERP_ALWAYS             "1"
#define DOT11_NONERP_DYNAMIC            "2"

#define DOT11_SLOTSETTING_LONG          "0"
#define DOT11_SLOTSETTING_SHORT         "1"
#define DOT11_SLOTSETTING_DYNAMIC       "2"

#define DOT11_PROFILE_B_ONLY            "0"
#define DOT11_PROFILE_MIXED             "1"
#define DOT11_PROFILE_MIXED_LONG        "2"
#define DOT11_PROFILE_G_ONLY            "3"
#define DOT11_PROFILE_TEST		"4"
#define DOT11_PROFILE_B_WIFI            "5"
#define DOT11_PROFILE_A_ONLY            "6"
#define DOT11_PROFILE_MIXED_SHORT       "7"

#define DOT11_DOT1X_AUTHENABLED         "1"
#define DOT11_DOT1X_KEYTXENABLED        "2"

#define DOT11_ERPSTAT_NONERPPRESENT     "0x01"
#define DOT11_ERPSTAT_USEPROTECTION     "0x02"


/* 7.3.1.7 This Reason Code is used to indicate the reason that an */
/* unsolicited notification Management frame of Type Disassociation */
/* or Deauthentication was generated. */

/* Unspecified Reason */
#define DOT11_RC_UNSPECIFIED                    "1"

/* Previous Authentication no longer valid */
#define DOT11_RC_PREV_AUTH_NOT_VALID            "2"

/* Deauthenticated because sending station */
/* is leaving (has left) IBSS or ESS */
#define DOT11_RC_DEAUTH_BECAUSE_LEFT_SS         "3"

/* Disassociated due to inactivity */
#define DOT11_RC_DISASSOC_INACTIVITY            "4"

/* Disassociated because AP is unable to */
/* handle all currently associated stations */
#define DOT11_RC_DISASSOC_CANNOT_HANDLE_ASSOCS  "5"

/* Class 2 frame received from non- */
/* Authenticated station */
#define DOT11_RC_CLASS2_RECEIVED                "6"

/* Class 3 frame received from non- */
/* Associated station */
#define DOT11_RC_CLASS3_RECEIVED                "7"

/* Disassociated because sending station */
/* is leaving (has left) IBSS or ESS */
#define DOT11_RC_DISASSOC_BECAUSE_LEFT_SS       "8"

/* Station requesting (Re)Association is not */
/* Authenticated with responding station */
#define DOT11_RC_NOT_AUTHENTICATED              "9"


/* 7.3.1.9 This Status Code is used in a response management frame */
/* to indicate the success or failure of a requested operation. */


/* Successful */
#define DOT11_SC_SUCCESSFUL                     "0"

/* Unspecified Failure */
#define DOT11_SC_UNSPECIFIED                    "1"

/* Cannot support all requested capabilities */
/* in the Capability Information Field */
#define DOT11_SC_UNSUPPORTED_CAPABILITIES       "10"

/* Reassociation denied due to inability to */
/* confirm that Association exists */
#define DOT11_SC_NO_ASSOCIATION                 "11"

/* Association denied due to reason outside */
/* the scope of this standard */
#define DOT11_SC_OUTSIDE_SCOPE                  "12"

/* Responding station does not support the */
/* specified Authentication Algorithm */
#define DOT11_SC_UNSUPPORTED_AUTH_ALG           "13"

/* Received an Authentication Frame with */
/* Authentication Transaction Sequence */
/* Number out of expected sequence */
#define DOT11_SC_OUT_OF_SEQUENCE                "14"

/* Authentication rejected because of */
/* challenge failure */
#define DOT11_SC_CHALLENGE_FAILURE              "15"

/* Authentication rejected due to timeout */
/* waiting for next frame in sequence */
#define DOT11_SC_TIMEOUT                        "16"

/* Association denied because AP is unable */
/* to handle additional associated stations */
#define DOT11_SC_CANNOT_HANDLE_ASSOCS           "17"

/* Association denied due to requesting */
/* station not supporting all of the data rates */
/* in the BSSBasicRateSet parameter */
#define DOT11_SC_UNSUPPORTED_BASIC_RATES        "18"

/* Association denied because the requesting */
/* station does not support short preamble */
#define DOT11_SC_UNSUPPORTED_SHORT_PREAMBLE     "19"

/*
 * 802.11 structures
 */

struct obj_ssid
{
    char length;
    char octets[33];
};

struct obj_vdcf
{
    short cwmin;
    short cwmax;
    short pfact;
    short aifs;
};

struct obj_aloft
{
    short nr;
    short initial;
    short array[1];
};

struct obj_key
{
    char type;
    char length;
    char key[32];
};

#define DOT11_STAKEY_OPTION_DEFAULTKEY          "0x0001"

struct obj_stakey
{
    char address[6];

    char keyid;
    char reserved;

    short options;

    char type;
    char length;
    char key[32];
};

struct obj_sta
{
    char address[6];
    char pad[2];

    char state;
    char flags;
    short age;

    char quality;
    char rssi;
};

struct obj_stasc
{
    char address[6];

    char keyid;
    char tx_sc;

    unsigned long sc_high;
    unsigned short sc_low;
};

struct obj_bss
{
    char    address[6];
    char    pad[2];

    char    state;
    char    reserved;
    short   age;

    char    quality;
    char    rssi;

    char    ssid[34];
    short   channel;
    char    beacon_period;
    char    dtim_period;
    short   capinfo;
    short   rates;
    short   basic_rates;
    short   pad2;
};

struct obj_bsslist
{
    long nr;
    struct obj_bss bsslist[1];
};

struct obj_attachment
{
    char type;
    char reserved;
    short id;
    short size;
    char data[1];
};

struct obj_mlme
{
    char address[6];
    short id;
    short state;
    short code;
};

struct obj_mlmeex
{
    char address[6];
    short id;
    short state;
    short code;
    short size;
    char data[1];
};

struct obj_scan
{
    short sweep;

    short type;
    short min;
    short max;
    short interval;

    short nr;
    unsigned short mhz[32];
};

struct obj_frequencies
{
    short nr;
    unsigned short mhz[1];
};

struct obj_rssivector
{
    long a;
    long b;
};

struct obj_buffer
{
    long size;
    void *base;
};

struct obj_power
{
    signed char set_point;
    unsigned char accumulator;
};

struct obj_powertable
{
    unsigned short frequency;
    struct obj_power cck;
    struct obj_power bpsk;
    struct obj_power qpsk;
    struct obj_power qam16;
    struct obj_power qam64;
};

/*
 * 802.11 OIDs
 */

#define DOT11_OID_BSSTYPE               "0x10000000"
#define DOT11_OID_BSSID                 "0x10000001"
#define DOT11_OID_SSID                  "0x10000002"
#define DOT11_OID_STATE                 "0x10000003"
#define DOT11_OID_AID                   "0x10000004"
#define DOT11_OID_COUNTRYSTRING         "0x10000005"
#define DOT11_OID_SSIDOVERRIDE          "0x10000006"

#define DOT11_OID_MEDIUMLIMIT           "0x11000000"
#define DOT11_OID_BEACONPERIOD          "0x11000001"
#define DOT11_OID_DTIMPERIOD            "0x11000002"
#define DOT11_OID_ATIMWINDOW            "0x11000003"
#define DOT11_OID_LISTENINTERVAL        "0x11000004"
#define DOT11_OID_CFPPERIOD             "0x11000005"
#define DOT11_OID_CFPDURATION           "0x11000006"

#define DOT11_OID_AUTHENABLE            "0x12000000"
#define DOT11_OID_PRIVACYINVOKED        "0x12000001"
#define DOT11_OID_EXUNENCRYPTED         "0x12000002"
#define DOT11_OID_DEFKEYID              "0x12000003"
#define DOT11_OID_DEFKEY1               "0x12000004"
#define DOT11_OID_DEFKEY2               "0x12000005"
#define DOT11_OID_DEFKEY3               "0x12000006"
#define DOT11_OID_DEFKEY4               "0x12000007"
#define DOT11_OID_STAKEY                "0x12000008"
#define DOT11_OID_REKEYTHRESHOLD        "0x12000009"
#define DOT11_OID_STASC                 "0x1200000a"

#define DOT11_OID_PRIVTXREJECTED        "0x1a000000"
#define DOT11_OID_PRIVRXPLAIN           "0x1a000001"
#define DOT11_OID_PRIVRXFAILED          "0x1a000002"
#define DOT11_OID_PRIVRXNOKEY           "0x1a000003"

#define DOT11_OID_RTSTHRESH             "0x13000000"
#define DOT11_OID_FRAGTHRESH            "0x13000001"
#define DOT11_OID_SHORTRETRIES          "0x13000002"
#define DOT11_OID_LONGRETRIES           "0x13000003"
#define DOT11_OID_MAXTXLIFETIME         "0x13000004"
#define DOT11_OID_MAXRXLIFETIME         "0x13000005"
#define DOT11_OID_AUTHRESPTIMEOUT       "0x13000006"
#define DOT11_OID_ASSOCRESPTIMEOUT      "0x13000007"

#define DOT11_OID_ALOFT_TABLE           "0x1d000000"
#define DOT11_OID_ALOFT_CTRL_TABLE      "0x1d000001"
#define DOT11_OID_ALOFT_RETREAT         "0x1d000002"
#define DOT11_OID_ALOFT_PROGRESS        "0x1d000003"
#define DOT11_OID_ALOFT_FIXEDRATE       "0x1d000004"
#define DOT11_OID_ALOFT_RSSIGRAPH       "0x1d000005"
#define DOT11_OID_ALOFT_CONFIG          "0x1d000006"

#define DOT11_OID_VDCF0                 "0x1b000000"
#define DOT11_OID_VDCF1                 "0x1b000001"
#define DOT11_OID_VDCF2                 "0x1b000002"
#define DOT11_OID_VDCF3                 "0x1b000003"
#define DOT11_OID_VDCF4                 "0x1b000004"
#define DOT11_OID_VDCF5                 "0x1b000005"
#define DOT11_OID_VDCF6                 "0x1b000006"
#define DOT11_OID_VDCF7                 "0x1b000007"
#define DOT11_OID_MAXFRAMEBURST         "0x1b000008"

#define DOT11_OID_PSM                   "0x14000000"
#define DOT11_OID_CAMTIMEOUT            "0x14000001"
#define DOT11_OID_RECEIVEDTIMS          "0x14000002"
#define DOT11_OID_ROAMPREFERENCE        "0x14000003"

#define DOT11_OID_BRIDGELOCAL           "0x15000000"
#define DOT11_OID_CLIENTS               "0x15000001"
#define DOT11_OID_CLIENTSASSOCIATED     "0x15000002"
#define DOT11_OID_CLIENT1               "0x15000003"
/*
 * All intermediate definitions are left out as an
 * exercise to the implementor.
 */
#define DOT11_OID_CLIENT2007            "0x150007D9"

#define DOT11_OID_CLIENTFIND            "0x150007DB"
#define DOT11_OID_WDSLINKADD            "0x150007DC"
#define DOT11_OID_WDSLINKREMOVE         "0x150007DD"
#define DOT11_OID_EAPAUTHSTA		"0x150007DE"
#define DOT11_OID_EAPUNAUTHSTA		"0x150007DF"
#define DOT11_OID_DOT1XENABLE           "0x150007E0"
#define DOT11_OID_MICFAILURE            "0x150007E1"
#define DOT11_OID_REKEYINDICATE         "0x150007E2"

#define DOT11_OID_MPDUTXSUCCESSFUL      "0x16000000"
#define DOT11_OID_MPDUTXONERETRY        "0x16000001"
#define DOT11_OID_MPDUTXMULTIPLERETRIES "0x16000002"
#define DOT11_OID_MPDUTXFAILED          "0x16000003"
#define DOT11_OID_MPDURXSUCCESSFUL      "0x16000004"
#define DOT11_OID_MPDURXDUPS            "0x16000005"
#define DOT11_OID_RTSSUCCESSFUL         "0x16000006"
#define DOT11_OID_RTSFAILED             "0x16000007"
#define DOT11_OID_ACKFAILED             "0x16000008"
#define DOT11_OID_FRAMERECEIVES         "0x16000009"
#define DOT11_OID_FRAMEERRORS           "0x1600000a"
#define DOT11_OID_FRAMEABORTS           "0x1600000b"
#define DOT11_OID_FRAMEABORTSPHY        "0x1600000c"

#define DOT11_OID_SLOTTIME              "0x17000000"
#define DOT11_OID_CWMIN                 "0x17000001"
#define DOT11_OID_CWMAX                 "0x17000002"
#define DOT11_OID_ACKWINDOW             "0x17000003"
#define DOT11_OID_ANTENNARX             "0x17000004"
#define DOT11_OID_ANTENNATX             "0x17000005"
#define DOT11_OID_ANTENNADIVERSITY      "0x17000006"
#define DOT11_OID_CHANNEL               "0x17000007"
#define DOT11_OID_EDTHRESHOLD           "0x17000008"
#define DOT11_OID_PREAMBLESETTINGS      "0x17000009"
#define DOT11_OID_RATES                 "0x1700000a"
#define DOT11_OID_CCAMODESUPPORTED      "0x1700000b"
#define DOT11_OID_CCAMODE               "0x1700000c"
#define DOT11_OID_RSSIVECTOR            "0x1700000d"
#define DOT11_OID_OUTPUTPOWERTABLE      "0x1700000e"
#define DOT11_OID_OUTPUTPOWER           "0x1700000f"
#define DOT11_OID_SUPPORTEDRATES        "0x17000010"
#define DOT11_OID_FREQUENCY             "0x17000011"
#define DOT11_OID_SUPPORTEDFREQUENCIES  "0x17000012"
#define DOT11_OID_NOISEFLOOR            "0x17000013"
#define DOT11_OID_FREQUENCYACTIVITY     "0x17000014"
#define DOT11_OID_IQCALIBRATIONTABLE	"0x17000015"
#define DOT11_OID_NONERPPROTECTION      "0x17000016"
#define DOT11_OID_SLOTSETTINGS          "0x17000017"
#define DOT11_OID_NONERPTIMEOUT         "0x17000018"
#define DOT11_OID_PROFILES		"0x17000019"
#define DOT11_OID_EXTENDEDRATES         "0x17000020"
#define DOT11_OID_17000021

#define DOT11_OID_DEAUTHENTICATE        "0x18000000"
#define DOT11_OID_AUTHENTICATE          "0x18000001"
#define DOT11_OID_DISASSOCIATE          "0x18000002"
#define DOT11_OID_ASSOCIATE             "0x18000003"
#define DOT11_OID_SCAN                  "0x18000004"
#define DOT11_OID_BEACON                "0x18000005"
#define DOT11_OID_PROBE                 "0x18000006"
#define DOT11_OID_DEAUTHENTICATEEX      "0x18000007"
#define DOT11_OID_AUTHENTICATEEX        "0x18000008"
#define DOT11_OID_DISASSOCIATEEX        "0x18000009"
#define DOT11_OID_ASSOCIATEEX           "0x1800000a"
#define DOT11_OID_REASSOCIATE           "0x1800000b"
#define DOT11_OID_REASSOCIATEEX         "0x1800000c"

#define DOT11_OID_NONERPSTATUS          "0x1e000000"

#define DOT11_OID_STATIMEOUT            "0x19000000"
#define DOT11_OID_MLMEAUTOLEVEL         "0x19000001"
#define DOT11_OID_BSSTIMEOUT            "0x19000002"
#define DOT11_OID_ATTACHMENT            "0x19000003"
#define DOT11_OID_PSMBUFFER             "0x19000004"

#define DOT11_OID_BSSS                  "0x1c000000"
#define DOT11_OID_BSS1                  "0x1c000001"
/*
 * All intermediate definitions are left out as an
 * exercise to the implementor.
 */
#define DOT11_OID_BSS64                 "0x1c000040"

#define DOT11_OID_BSSFIND               "0x1c000042"
#define DOT11_OID_BSSLIST               "0x1c000043"

#define DOT11_OID_1f000000
#define DOT11_OID_1f000001
#define DOT11_OID_1f000002


/*
 * Manufacturing structures
 */

struct obj_mt
{
    long    mode;

    long    channel;
    long    rate;
    long    preamble;
    long    length;
    long    modulation;
    long    scrambling;
    long    filter;
    long    antenna_rx;
    long    antenna_tx;
    long    power_loop;
    struct obj_key key;
    long    ccamode;
    long    autorespond;

    unsigned char *mpdu;
};

/*
 * Manufacturing OIDs
 */

#define MT_OID_MTMODE                   "0x90000000"
#define MT_OID_MTCMD                    "0x90000001"

#define MT_OID_BBREGNR                  "0x90000010"
#define MT_OID_BBREGDATA                "0x90000011"
#define MT_OID_SYNTHNR                  "0x90000012"
#define MT_OID_SYNTHDATA                "0x90000013"

#define MT_OID_RSSI                     "0x90000020"
#define MT_OID_SQI                      "0x90000021"
#define MT_OID_SQ                       "0x90000022"
#define MT_OID_POWERCONTROL             "0x90000023"
#define MT_OID_POWERDETECTOR            "0x90000024"

#define MT_OID_REGISTER0                "0x90000100"
#define MT_OID_REGISTER1                "0x90000101"
#define MT_OID_REGISTER2                "0x90000102"
#define MT_OID_REGISTER3                "0x90000103"
#define MT_OID_REGISTER4                "0x90000104"
#define MT_OID_REGISTER5                "0x90000105"
#define MT_OID_REGISTER6                "0x90000106"
#define MT_OID_REGISTER7                "0x90000107"

// Driver specific oid definitions (NDIS driver)
#define OID_INL_TUNNEL                          "0xFF020000"
#define OID_INL_MEMADDR                         "0xFF020001"
#define OID_INL_MEMORY                          "0xFF020002"
#define OID_INL_MODE                            "0xFF020003"
#define OID_INL_COMPONENT_NR                    "0xFF020004"
#define OID_INL_VERSION                         "0xFF020005"
#define OID_INL_INTERFACE_ID                    "0xFF020006"
#define OID_INL_COMPONENT_ID                    "0xFF020007"
#define OID_INL_CONFIG                          "0xFF020008"

// Mode object definitions (OID_INL_MODE)
#define INL_MODE_NONE                           "-1"
#define INL_MODE_PROMISCUOUS                    "0"
#define INL_MODE_CLIENT                         "1"
#define INL_MODE_AP                             "2"
#define INL_MODE_SNIFFER                        "3"

// Config object definitions (OID_INL_CONFIG)
#define INL_CONFIG_MANUALRUN                    "0x01"
#define INL_CONFIG_FRAMETRAP                    "0x02"
#define INL_CONFIG_RXANNEX                      "0x04"
#define INL_CONFIG_TXANNEX                      "0x08"
#define INL_CONFIG_WDS                          "0x10"

#define PRIVACYINVOKED_DISABLE			"0"
#define PRIVACYINVOKED_ENABLE			"1"
