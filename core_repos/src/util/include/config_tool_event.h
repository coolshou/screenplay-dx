#ifndef CONFIG_TOOL_EVENT_H
#define CONFIG_TOOL_EVENT_H

typedef enum {
	CONFIG_TOOL_CMD_UNKNOWN=0,
	CONFIG_TOOL_CMD_START,
	CONFIG_TOOL_CMD_STOP,
	CONFIG_TOOL_CMD_DEAD
}CONFIG_TOOL_CMD;

#define EPCONFIGTOOL_RD_FIFO  "configtool_rd_fifo"    /* it's half-way chanel, only [other process]->config_tool */
#define EPCONFIGTOOL_WR_FIFO  "configtool_wr_fifo"    /* it's not  usable, only for event proxy*/ 
#endif
