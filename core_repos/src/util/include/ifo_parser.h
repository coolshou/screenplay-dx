/*

Parse file: VTS_0x_0.IFO (x: can be 0, 1, ....)

Read Video Title Set Information Management Table(VTSI_MAT) from VTS_xx_0.IFO

 1. What does the Video attribute of the DVD?

	data offset: 512 ~ 513 ==> Video attribute of VTS(VTS_V_ATR) , Number of bytes: 2 bytes

	b15 ~ b14: Video compression mode
			00b: Complies with MPEG-1
			01b: Complies with MPEG-2
			Others: reserved
	
	b13 ~ b12: TV system
			00b: 525/60
			01b: 625/60
			Others: reserved

	b11 ~ b10: Aspect ratio
			00b:  4:3
			11b: 16:9
			Others: reserved
	
	b9 ~ b8: Display mode (Describes the permitted display mode on 4:3 monitor)
			When the "Aspect ratio" is '00b' (4:3), enter '11b'
			When the "Aspect ratio" is '11b' (16:9), enter '00b', '01b' or '10b'
			00b: Both Pan-scan* and Letterbox
			01b: Only Pan-scan*
			10b: Only Letterbox
			11b: reserved
			*: Pan-scan means the 4:3 aspect ratio window taken from decoded picture.

	b7: line21_switch_1

	b8: line21_switch_2

	b5 ~ b3: Source picture resolution
			000b: 720 x 480 (525/60 system), 720 x 576 (625/50 system)
			001b: 704 x 480 (525/60 system), 704 x 576 (625/50 system)
			010b: 352 x 480 (525/60 system), 352 x 576 (625/50 system)
			011b: 352 x 240 (525/60 system), 352 x 288 (625/50 system)
			Others: reserved

	b2: Source picture letterboxed

	b1: reserved

	b0: Film camera mode
			

2. How many audio stream in the DVD?

	data offset: 514 ~ 515 ==> Number of Audio streams of VTS(VTS_AST_Ns) , Number of bytes: 2 bytes

	b15 ~ b6: reserved
	b5  ~ b0: Number of Audio streams

3. What does Audio stream attribute of the DVD?

	data offset: 516 ~ 579 ==> Audio streams attribute table of VTS(VTS_AST_ATRT) , Number of bytes: 64 bytes

	data offset: 516 ~ 523 ==> VTS_AST_ATR of Audio stream #0, Number of bytes: 8 bytes
	data offset: 524 ~ 531 ==> VTS_AST_ATR of Audio stream #1, Number of bytes: 8 bytes
	data offset: 532 ~ 539 ==> VTS_AST_ATR of Audio stream #2, Number of bytes: 8 bytes
	data offset: 540 ~ 547 ==> VTS_AST_ATR of Audio stream #3, Number of bytes: 8 bytes
	data offset: 548 ~ 555 ==> VTS_AST_ATR of Audio stream #4, Number of bytes: 8 bytes
	data offset: 556 ~ 563 ==> VTS_AST_ATR of Audio stream #5, Number of bytes: 8 bytes
	data offset: 564 ~ 571 ==> VTS_AST_ATR of Audio stream #6, Number of bytes: 8 bytes
	data offset: 572 ~ 579 ==> VTS_AST_ATR of Audio stream #7, Number of bytes: 8 bytes

	The content of one VTS_AST_ATR is follows:

	b63 ~ b61: Audio coding mode
			000b: Dolby AC-3
			010b: MPEG-1 or MPEG-2 without extension bitstream
			011b: MPEG-2 with extension bitstream
			100b: Linear PCM audio
			110b: DTS(option)
			111b: SDDS(option)
			Others: reserved

	b60: Multichannel extension

	b59 ~ b58: Audio type

	b57 ~ b56: Audio application mode

	b55 ~ b54: Quantization/DRC

	b53 ~ b52: fs
			00b: 48kHz
			01b: 96kHz
			Others: reserved

	b51: reserved

	b50 ~ b48: Number of Audio channels
			000b: 1ch (mono)
			001b: 2ch (strereo)
			010b: 3ch ---|
			011b: 4ch ---|
			100b: 5ch ---|---(multichannel)
			101b: 6ch ---|
			110b: 7ch ---|
			111b: 8ch ---|

	b47 ~ b40: Specific code (upper bits)

	b39 ~ b32: Specific code (lower bits)

	b31 ~ b24: reserved (for Specific code)

	b23 ~ b16: Specific code extension

	b15 ~ b8: reserved

	b7 ~ b0: Application Information
	

4. How many subtitle stream in the DVD?

	data offset: 596 ~ 597 ==> Number of Sub-picture streams of VTS(VTS_SPST_Ns) , Number of bytes: 2 bytes

	b15 ~ b6: reserved
	b5  ~ b0: Number of Sub-picture streams

5. What does the Subtitle stream attribute of the DVD?

	data offset: 598 ~ 789 ==> Sub-picture stream attribute table of VTS(VTS_SPST_ATRT) , Number of bytes: 192 bytes

	data offset: 598 ~ 603 ==> VTS_SPST_ATR of Sub-picture stream #0, Number of bytes: 6 bytes
	data offset: 604 ~ 609 ==> VTS_SPST_ATR of Sub-picture stream #1, Number of bytes: 6 bytes
	data offset: 610 ~ 615 ==> VTS_SPST_ATR of Sub-picture stream #2, Number of bytes: 6 bytes
						.
						.
						.
						.
						.
						.
	data offset: 784 ~ 789 ==> VTS_SPST_ATR of Sub-picture stream #31, Number of bytes: 6 bytes

	The content of one VTS_SPST_ATR is follows:

	b47 ~ b45: Sub-picture coding mode
			000b: Run-length for 2 bits/pixel
			010b: reserved (for extended Sub-picture)
			Others: reserved

	b41 ~ b40: Sub-picture type
			00b: Not specified
			01b: Language
			Others: reserved

	b39 ~ b32: reserved

	b31 ~ b24: Specific code (upper bits)

	b23 ~ b16: Specific code (lower bits)

	b15 ~ b8: reserved (for Specific code)

	b7 ~ b0: Specific code extension

6. How long does the film of the DVD?
	
	6.1 Get 'Start address of VTS_PGCIT' first.
		data offset: 204 ~ 207 ==> Start address of Video Title Set Program Chain Information Table(VTS_PGCIT) , Number of bytes: 4 bytes
	6.2 Get VTS_PGCIT Information(VTS_PGCITI)
		data offset: (VTS_PGCIT * 2048) ~ (VTS_PGCIT * 2048) + 8 , Number of bytes: 8 bytes

		Number of VTS_PGCI_SRPs(VTP_PGCI_SRP_Ns) , Number of Bytes: 2 bytes
		reserved				 , Number of Bytes: 2 bytes
		End address of VTS_PGCIT(VTS_PGCIT_EA)   , Number of Bytes: 4 bytes
	6.3 Skip VTS_PGCI_SRP data to get GPC General Information(PGC_GI)
		data offset: VTS_PGCITI + 8 + (VTP_PGCI_SRP_Ns * 8)
	6.4 Get PGC Playback Time in PGC_GI

		The content of PGC_GI is follow:

		0 ~ 3: PGC Contents(PGC_CNT) , Number of bytes: 4 bytes
		4 ~ 7: PGC Playback Time(PGC_PB_TM) , Number of bytes: 4 bytes
						.
						.
						.
						.
						.
						.

		Struct of PGC Playback Time(PGC_PB_TM):

		b31 ~ b28: Hour(ten's), Describes any number between '0' and '9'
		b27 ~ b24: Hour(units), Describes any number between '0' and '9'
		b23 ~ b20: Minute(ten's), Describes any number between '0' and '9'
		b19 ~ b16: Minutes(units), Describes any number between '0' and '9'
		b15 ~ b12: Second(ten's), Describes any number between '0' and '9'
		b11 ~ b8:  Second(units), Describes any number between '0' and '9'
		b7  ~ b6:  tc_flag, Decrites the type of Video frame.
				00b: reserved
				01b: 25 frames/s
				10b: reserved
				11b: 30 frames/s non-drop frame
*/

#define IFO_ERROR		-1
#define IFO_FRAME_RESERVED1	0
#define IFO_FRAME_25		1
#define IFO_FRAME_RESERVED2	2
#define IFO_FRAME_30		3

#define IFO_AST_CODING_AC3	0
#define IFO_AST_CODING_MPEG12	2
#define IFO_AST_CODING_MPEG2	3
#define IFO_AST_CODING_PCM	4
#define IFO_AST_CODING_DTS	6
#define IFO_AST_CODING_SDDS	7

#define IFO_PCM_BPS_16BITS	0	// Just apply when "Audio coding mode" is "Linear PCM audio"
#define IFO_PCM_BPS_20BITS	1	// Just apply when "Audio coding mode" is "Linear PCM audio"
#define IFO_PCM_BPS_24BITS	2	// Just apply when "Audio coding mode" is "Linear PCM audio"

#define IFO_SAMPLE_RATE_48K	0
#define IFO_SAMPLE_RATE_96K	1

#define IFO_AST_CH_NS_1		0
#define IFO_AST_CH_NS_2		1
#define IFO_AST_CH_NS_3		2
#define IFO_AST_CH_NS_4		3
#define IFO_AST_CH_NS_5		4
#define IFO_AST_CH_NS_6		5
#define IFO_AST_CH_NS_7		6
#define IFO_AST_CH_NS_8		7

#define IFO_MPEG_VERSION_MPEG1	0
#define IFO_MPEG_VERSION_MPEG2	1

#define IFO_VIDEO_FORMAT_NTSC	0
#define IFO_VIDEO_FORMAT_PAL	1

#define IFO_ASPECT_RATIO_4_3	0
#define IFO_ASPECT_RATIO_16_9	3

#define IFO_RESOLUTION_720_480	0
#define IFO_RESOLUTION_704_480	1
#define IFO_RESOLUTION_352_480	2
#define IFO_RESOLUTION_352_240	3


#define IFO_MAX_AUDIO_NUMBER 8
#define IFO_MAX_SUBTITLE_NUMBER 32
int IFO_init(const char *dvd_folder_path);
/*
 * Inital ifo parser
 *
 * Parameter:
 * 	dvd_folder_path: path of mount point of dvd iso file.
 *
 * Return:
 *	0: Initial Successful
 *	-1: Initial fail
 */

int IFO_get_aspect_ratio(int idx_film);
/*
 * Get Aspect ratio of the film.
 *
 * Return:
 *	IFO_ASPECT_RATIO_4_3 ==> 0, 4:3
 *	IFO_ASPECT_RATIO_16_9 ==> 3: 16:9
 *	IFO_ERROR ==> -1, error
 */

int IFO_get_resolution(int idx_film);
/*
 * Get Source resolution of the film.
 *
 * Return:
 *	IFO_RESOLUTION_720_480 ==> 0, 720 x 480 (525/60 system), 720 x 576 (625/50 system)
 *	IFO_RESOLUTION_704_480 ==> 1, 704 x 480 (525/60 system), 704 x 576 (625/50 system)
 *	IFO_RESOLUTION_352_480 ==> 2, 352 x 480 (525/60 system), 352 x 576 (625/50 system)
 *	IFO_RESOLUTION_352_240 ==> 3, 352 x 240 (525/60 system), 352 x 288 (625/50 system)
 *	IFO_ERROR ==> -1, error
 */

int IFO_get_main_film_ns();
/*
 * Get number of main films of DVD
 *
 * Return:
 *	number of main films
 */

int IFO_get_vob_ns(int idx_film);
/*
 * Get number of VOB files of the film
 *
 * Parameter:
 *	idx_film: index of film
 *
 * Return:
 *	number of VOB files
 */


int IFO_get_pgc_ns(int idx_film);
/*
 * Get number of PGC of VOB file
 *
 * Parameter:
 *	idx_film: index of film
 *
 * Return:
 *	number of audio streams
 */

char *IFO_get_vob_name(int idx_film, int idx_vob);
/*
 * Get file name of VOB by index of film
 *
 * Return:
 *	NULL: fail
 *	Others: file name of vob
 */

int IFO_get_ast_ns(int idx_film);
/*
 * Get number of audio streams of VOB file
 *
 * Parameter:
 *	idx_film: index of film
 *
 * Return:
 *	number of audio streams
 */

char *IFO_get_ast_lang(int idx_film, int idx_audio);
/*
 * Get language of index of audio stream of VOB file
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_audio: index of audio stream
 *
 * Return:
 *	language of audio stream
 */

int IFO_get_ast_coding(int idx_film, int idx_audio);
/*
 * Get audio coding mode of index of audio stream of VOB file
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_audio: index of audio stream
 *
 * Return:
 *	IFO_AST_CODING_AC3    ==> 0: Dolby AC-3
 *	IFO_AST_CODING_MPEG12 ==> 2: MPEG-1 or MPEG-2 without extension bitstream
 *	IFO_AST_CODING_MPEG2  ==> 3: MPEG-2 with extension bitstream
 *	IFO_AST_CODING_PCM    ==> 4: Linear PCM audio
 *	IFO_AST_CODING_DTS    ==> 6: DTS(option)
 *	IFO_AST_CODING_SDDS   ==> 7: SDDS(option)
 *	IFO_ERROR             ==> -1: error
 */

int IFO_get_ast_ch_ns(int idx_film, int idx_audio);
/*
 * Get number of audio channels of index of audio stream of VOB file
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_audio: index of audio stream
 *
 * Return:
 *	IFO_AST_CH_NS_1 ==> 0: 1ch mono
 *	IFO_AST_CH_NS_2 ==> 1: 2ch strereo
 *	IFO_AST_CH_NS_3 ==> 2: 3ch multichannel
 *	IFO_AST_CH_NS_4 ==> 3: 4ch multichannel
 *	IFO_AST_CH_NS_5 ==> 4: 5ch multichannel
 *	IFO_AST_CH_NS_6 ==> 5: 6ch multichannel
 *	IFO_AST_CH_NS_7 ==> 6: 7ch multichannel
 *	IFO_AST_CH_NS_8 ==> 7: 8ch multichannel
 *	IFO_ERROR	==> -1: error
 */

int IFO_get_spst_ns(int idx_film);
/*
 * Get number of sub-picture streams of VOB file
 *
 * Parameter:
 *	idx_film: index of film
 *
 * Return:
 *	number of sub-picture streams
 */

char *IFO_get_spst_lang(int idx_film, int idx_sub_picture);
/*
 * Get language of index of sub-picture stream of VOB file
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_sub-picture: index of sub-picture stream
 *
 * Return:
 *	language of audio stream
 */

int IFO_get_playback_time(int idx_film);
/*
 * Get total presentation time of Programs in the PGC
 *
 * Parameter:
 *	idx_film: index of film
 *
 * Return:
 *	total presentation time measured in mini seconds
 */

int IFO_get_pgc_playback_time(int idx_film, int idx_pgc);
/*
 * Get palette of Programs in the PGC
 *
 * Parameter:
 *	idx_film: index of film
 *
 * Return:
 *	the pointer of uint32_t palette[16]	
 */

char *IFO_get_pgc_palette(int idx_film, int idx_pgc);
/*
 * Get presentation time of the index PGC
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_pgc: index of pgc
 *
 * Return:
 *	total presentation time measured in mini seconds
 */

int IFO_get_pgc_frame(int idx_film, int idx_pgc);
/* 
 * Get frame rate of Programs in the PGC
 *
 * Parameter:
 *	idx_film: index of film
 *
 * Return:
 *	IFO_FRAME_RESERVED1 ==> 0, reserved
 *	IFO_FRAME_25	    ==> 1, 25 frames/s
 *	IFO_FRAME_RESERVED2 ==> 2, reserved
 *	IFO_FRAME_30	    ==> 3, 30 frames/s non-drop frame
 */

int IFO_get_pgc_ast_is_present(int idx_film, int idx_pgc, int idx_ast);
/* 
 * Get is present of the audio stream of the index PGC
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_pgc: index of pgc
 *	idx_spst: index of audio
 *
 * Return:
 * 	1: present (available)
 * 	0: not present
 */

int IFO_get_pgc_spst_is_present(int idx_film, int idx_pgc, int idx_spst);
/* 
 * Get is present of the sub-picture stream of the index PGC
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_pgc: index of pgc
 *	idx_spst: index of sub-picture
 *
 * Return:
 * 	1: present (available)
 * 	0: not present
 */
int IFO_get_pgc_spst_start_id(int idx_film, int idx_pgc, int idx_spst);
/* 
 * Get is start id (pid) of the sub-picture stream of the index PGC
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_pgc: index of pgc
 *	idx_spst: index of sub-picture
 *
 * Return:
 * 	the id of subtitle
 */

int IFO_get_ast_pcm_bps(int idx_film, int idx_audio);
/*
 * Get Quantization/DRC of index of audio stream of VOB file
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_audio: index of audio stream
 *
 * Return:
 * 	IFO_PCM_BPS_16BITS	==> 0: 16bits
 * 	IFO_PCM_BPS_20BITS	==> 1: 16bits
 * 	IFO_PCM_BPS_24BITS	==> 2: 16bits
 *	IFO_ERROR	==> -1: error
 */

int IFO_get_ast_start_id(int idx_film, int idx_pgc,int idx_audio);
/*
 *
 * Get the s_auido(start id) of audio
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_pgc: index of pgc
 *	idx_audio: index of audio stream
 *
 * Return:
 *	error : return -1
 *
 */

int IFO_get_ast_sample_rate(int idx_film, int idx_audio);
/*
 * Get sample rate of index of audio stream of VOB file
 *
 * Parameter:
 *	idx_film: index of film
 *	idx_audio: index of audio stream
 *
 * Return:
 * 	IFO_SAMPLE_RATE_48K	==> 0: 48kHz
 * 	IFO_SAMPLE_RATE_96K	==> 1: 96kHz
 *	IFO_ERROR		==> -1: error
 */

int IFO_get_mpeg_version(int idx_film);
/*
 * Get mpeg version of the film
 *
 * Return:
 *	IFO_MPEG_VERSION_MPEG1	==> 0: Compiles with MPEG-1
 *	IFO_MPEG_VERSION_MPEG2	==> 1: Compiles with MPEG-2
 *	IFO_ERROR ==> -1, error
 */

int IFO_get_video_format(int idx_film);
/*
 * Get video format of the film
 *
 * Return:
 *	IFO_VIDEO_FORMAT_NTSC	==> 0: 525/60 system
 *	IFO_VIDEO_FORMAT_PAL	==> 1: 625/50 system
 *	IFO_ERROR ==> -1, error
 */

void free_gIFO_info();
/*
 * Free gIFO_info variable, just for test.
 */
