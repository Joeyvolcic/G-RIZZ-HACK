/**
@file
	@brief Free-Wili wasm export header
Functions that are exposed from the WASM engine for use in Free-Wili WASM scripts
*/
#pragma once

#define WASM_IMPORT(NAME) __attribute__((import_module("wiliwasm"))) __attribute__((import_name(NAME)))
#define WASM_EXPORT extern "C" __attribute__((used)) __attribute__((visibility("default")))
#define WASM_EXPORT_AS(NAME) WASM_EXPORT __attribute__((export_name(NAME)))

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum _FWGuiEventType
	{
		FWGUI_EVENT_GRAY_BUTTON,
		FWGUI_EVENT_YELLOW_BUTTON,
		FWGUI_EVENT_GREEN_BUTTON,
		FWGUI_EVENT_BLUE_BUTTON,
		FWGUI_EVENT_RED_BUTTON,
		FWGUI_EVENT_IR_CODE,
		FWGUI_EVENT_GUI_BUTTON,
		FWGUI_EVENT_GUI_NUMEDIT,
		FWGUI_EVENT_GUI_TEXTEDIT,
		FWGUI_EVENT_GUI_AUDIO_DATA,
		FWGUI_EVENT_GUI_FFT_DATA,
		FWGUI_EVENT_GUI_I2C_RESPONSE,
		FWGUI_EVENT_EVENTFIFO_OVERFLOW,
		FWGUI_EVENT_GUI_RTC_RESPONSE,
		FWGUI_EVENT_GUI_SENSOR_DATA,
		FWGUI_EVENT_MAIN_APP_SEL,
		FWGUI_EVENT_PANEL_SHOW,
		FWGUI_EVENT_PICKLIST_SEL,
		FWGUI_EVENT_PANEL_HIDE,
		FWGUI_EVENT_MAIN_MENU_SHOWN,
		FWGUI_EVENT_STARTED,
		FWGUI_EVENT_CLR_STATS,
		FWGUI_EVENT_DIALOG_ACTION,
		FWGUI_EVENT_WASM_OVRFLOW,

		FWGUI_EVENT_DATA_MAX,
	} FWGuiEventType;

#define FWGUI_EVENT_NUMTYPE_INT 1
#define FWGUI_EVENT_NUMTYPE_UINT 2
#define FWGUI_EVENT_NUMTYPE_FLOAT 3

// Maximum amount of data for an event poll
#define FW_GET_EVENT_DATA_MAX 34

	typedef enum _LEDManagerLEDMode
	{
		ledsimplevalue,
		ledflash,
		ledpulse,
		ledflashfade,
		ledpulsefade,
	} LEDManagerLEDMode;

	typedef enum _ePanelColorLED
	{
		LEDColorRed,
		LEDColorGreen,
		LEDColorYellow,
		LEDColorBlue,
		LEDColorOrange,
		LEDColorAqua,
		LEDColorMagenta,
		LEDColorWhite,
	} ePanelColorLED;

	typedef enum _ePanelSizeLED
	{
		LEDSize32,
		LEDSize48,
		LEDSize64,
	} ePanelSizeLED;

	typedef enum _printOutDataType
	{
		printInt32 = 0,
		printUInt32,
		printInt16,
		printUInt16,
		printUint8,
		printInt8,
		printChar,
		printBool,
	} printOutDataType;

	typedef enum _printOutColor
	{
		printColorNormal = 0,
		printColorBlack,
		printColorBlue,
		printColorGreen,
		printColorCyan,
		printColorRed,
		printColorPurple,
		printColorBrown,
		printColorYellow,
		printColorWhite,
	} printOutColor;

	// ===============================================================================
	// General
	// ===============================================================================

	/**
	 * @brief wait for a number of milliseconds
	 * @param milliseconds the number of milliseconds to wait
	 */
	void waitms(int milliseconds) WASM_IMPORT("waitms");

	/**
	 * @brief return a random value
	 */
	int wilirand(void) WASM_IMPORT("wilirand");

	/**
	 * @brief return number of milliseconds since boot
	 */
	unsigned int millis(void) WASM_IMPORT("millis");

	// ===============================================================================
	// GPIO
	// ===============================================================================
	/**
	 * @brief set the state of a GPIO
	 * @param io the number of the GPIO
	 * @param on 1 for on, 0 for off
	 */
	void setIO(int io, int on) WASM_IMPORT("setIO");
	/**
	 * @brief get the state of a GPIO
	 * @param io the number of the GPIO
	 * @return 1 for on, 0 for off
	 */
	unsigned int getIO(int io) WASM_IMPORT("getIO");
	/**
	 * @brief get the state of all GPIO
	 * @return 1 for on, 0 for off for each bit position
	 */
	unsigned int getAllIO(void) WASM_IMPORT("getAllIO");

	// ===============================================================================
	// I2C
	// ===============================================================================
	/**
	 * @brief read from an I2C device
	 * @param address the I2C address
	 * @param reg the I2C register
	 * @param data pointer to the data to send
	 * @param length the length of the data to send
	 * @return 1 on success, 0 on failure
	 */
	int i2cRead(int address, int reg, unsigned char* data, int length) WASM_IMPORT("i2cRead");

	/**
	 * @brief write to an I2C device
	 * @param address the I2C address
	 * @param reg the I2C register
	 * @param data pointer to the data to send
	 * @param length the length of the data to send
	 * @return 1 on success, 0 on failure
	 */
	int i2cWrite(int address, int reg, unsigned char* data, int length) WASM_IMPORT("i2cWrite");

	// ===============================================================================
	// SPI
	// ===============================================================================
	/**
	 * @brief read and write data over SPI
	 * @param data_in pointer to the data to send
	 * @param length the length of the data to send
	 * @param data_out pointer to the data to receive
	 * @return 1 on success, 0 on failure
	 */
	int SPIReadWrite(unsigned char* data_in, int length, unsigned char* data_out) WASM_IMPORT("SPIReadWrite");

	// ===============================================================================
	// UART
	// ===============================================================================
	/**
	 * @brief Get the number of bytes in the UART receive buffer
	 * @return the number of bytes
	 */
	int UARTDataRxCount(void) WASM_IMPORT("UARTDataRxCount");
	/**
	 * @brief read data from the UART
	 * @param data pointer to the data to read
	 * @param length the length of the data to read
	 * @return 1 on success, 0 on failure
	 */
	int UARTDataRead(unsigned char* data, int length) WASM_IMPORT("UARTDataRead");
	/**
	 * @brief write data to the UART
	 * @param data pointer to the data to write
	 * @param length the length of the data to write
	 * @return length on success.
	 */
	int UARTDataWrite(unsigned char* data, int length) WASM_IMPORT("UARTDataWrite");

	// ===============================================================================
	// PWM
	// ===============================================================================
	/**
	 * @brief set the frequency and duty cycle of a PWM pin
	 * @param io the number of the PWM pin
	 * @param freq_hz the frequency of the PWM
	 * @param duty the duty cycle of the PWM
	 * @return 1 on success, 0 on failure
	 */
	int PWMSetFreqDuty(int io, float freq_hz, float duty) WASM_IMPORT("PWMSetFreqDuty");
	/**
	 * @brief stop PWM on a GPIO pin
	 * @param io the number of the GPIO pin
	 * @return 1 on success, 0 on failure
	 */
	int PWMStop(int io) WASM_IMPORT("PWMStop");

	// ===============================================================================
	// RADIO
	// ===============================================================================
	/**
	 * @brief write data to a radio
	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
	 * @param data pointer to the data to send
	 * @param length the length of the data to send
	 * @return 1 on success, 0 on failure
	 */
	int RadioWrite(int index, unsigned char* data, int length) WASM_IMPORT("RadioWrite");
	/**
	 * @brief read data from a radio
	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
	 * @param data pointer to the data to send
	 * @param length the length of the data to send
	 * @return number of bytes read on success, 0 on failure
	 */
	int RadioRead(int index, unsigned char* data, int length) WASM_IMPORT("RadioRead");
	/**
	 * @brief get the number of bytes in the radio receive buffer
	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
	 * @return the number of bytes
	 */
	int RadioGetRxCount(int index) WASM_IMPORT("RadioGetRxCount");
	/**
	 * @todo
	 */
	int RadioLoadConfig(int index, unsigned char* data, int length) WASM_IMPORT("RadioLoadConfig");
	/**
	 * @brief Transmit a sub file to a radio
	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
	 * @param sub_file the name of the sub file to transmit
	 * @return 1 on success, 0 on failure
	 */
	int RadioTxSubFile(int index, const char* sub_file) WASM_IMPORT("RadioTxSubFile");
	/**
	 * @brief Transmits a sub file to a radio. This function is non-blocking, see RadioSubFileIsTransmitting().
	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
	 * @return 1 on success, 0 on failure
	 */
	int RadioSetTx(int index) WASM_IMPORT("RadioSetTx");
	/**
	 * @brief set the radio to receive
	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
	 * @return 1 on success, 0 on failure
	 */
	int RadioSetRx(int index) WASM_IMPORT("RadioSetRx");
	/**
	 * @brief set the radio to idle
	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
	 * @return 1 on success, 0 on failure
	 */
	int RadioSetIdle(int index) WASM_IMPORT("RadioSetIdle");

	/**
	 * @brief get the RSSI of the radio
	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
	 * @return the RSSI
	 */
	int RadioGetRSSI(int index) WASM_IMPORT("RadioGetRSSI");
	/**
	 * @brief get the LQI of the radio
	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
	 * @return the LQI
	 */
	int RadioGetLQI(int index) WASM_IMPORT("RadioGetLQI");

	/**
	 * @brief check if the radio is currently transmitting
	 * @return 1 if transmitting, 0 if not
	 */
	int RadioSubFileIsTransmitting(void) WASM_IMPORT("RadioSubFileIsTransmitting");

	/**
	 * @brief Stop a sub-file transmission started with RadioTxSubFile().
	 */
	void RadioSubFileStop(void) WASM_IMPORT("RadioSubFileStop");

	/**
	 * @brief Performs a Frequency Scan on supported frequency and reports the frequency that surpassed the Rssi threshold
  	 * @param index the index of the radio. 1 for Radio 1, 2 for Radio 2.
    	 * @param RssiThreshold Threshold on when the frequency should be reported 
         * @param FoundPeak Flag to indicate a Frequency was found that surpassed RssiThreshold
	 * @param FrequencyResult Frequency that surpassed RssiThreshold
	 * @param RssiResult Rssi value match to frequency
	 */
	int RadioScan(int index, int RssiThreshold, unsigned int* FoundPeak, unsigned int* FrequencyResult, int* RssiResult) WASM_IMPORT("RadioScan");    

	// ===============================================================================
	// IR
	// ===============================================================================
	/**
	 * @brief send IR data
	 * @param data the IR data
	 */
	void sendIRData(unsigned int data) WASM_IMPORT("sendIRData");

	// ===============================================================================
	// LEDs
	// ===============================================================================
	/**
	 * @brief set the state of the tri-color LEDs
	 * @param led_index the index of the LED
	 * @param red the red value
	 * @param green the green value
	 * @param blue the blue value
	 * @param duration_ms the duration of the LED in milliseconds
	 * @param mode the mode of the LED. see LEDManagerLEDMode enum for more details.
	 */
	void setBoardLED(int led_index, int red, int green, int blue, int duration_ms, LEDManagerLEDMode mode) WASM_IMPORT("setBoardLED");
	/** @brief set the show mode of the LEDs.
	 * @param mode the show mode
	 * @todo
	 */
	void setLEDShowMode(int mode) WASM_IMPORT("setLEDShowMode");

	// ===============================================================================
	// Sound
	// ===============================================================================

	/// @brief
	/// @param file_name
	void playSoundFromFile(const char* file_name) WASM_IMPORT("playSoundFromFile");

	/// @brief
	/// @param name
	/// @param id
	void playSoundFromNameOrID(const char* name, int id) WASM_IMPORT("playSoundFromNameOrID");

	/// @brief
	/// @param bFloat
	/// @param iNumber
	/// @param fNumber
	/// @param iFloatDigits
	void playSoundFromNumber(int bFloat, int iNumber, float fNumber, int iFloatDigits) WASM_IMPORT("playSoundFromNumber");

	/// @brief Plays a tone of specified frequency and duration
	/// @param frequency frequency of the tone to play, in Hz
	/// @param duration duration of the tone to play, in seconds
	/// @param amplitude amplitude (1.0 is max, 0.2 recommended)
	/// @param wavetype
	void playSoundFromFrequencyAndDuration(float frequency, float duration, float amplitude, char wavetype)
		WASM_IMPORT("playSoundFromFrequencyAndDuration");


	// ===============================================================================
	// File IO
	// ===============================================================================
	int openFile(const char* file_name, int mode) WASM_IMPORT("OpenFile");
	int closeFile(int handle) WASM_IMPORT("closeFile");
	int writeFile(int handle, unsigned char* data, int data_bytes) WASM_IMPORT("writeFile");
	int preAllocateSpaceForFile(int handle, int size_in_bytes) WASM_IMPORT("preAllocateSpaceForFile");
	int readFile(int handle, unsigned char* data, int* data_bytes) WASM_IMPORT("readFile");
	int readFileLine(int handle, char* data, int* data_bytes) WASM_IMPORT("readFileLine");
	int setFilePosition(int handle, int position) WASM_IMPORT("setFilePosition");
	int getFilePosition(int handle) WASM_IMPORT("getFilePosition");
	int getFileSize(int handle) WASM_IMPORT("getFileSize");

	// ===============================================================================
	// File System
	// ===============================================================================
	int renameFileOrDirectory(const char* name, const char* new_name) WASM_IMPORT("renameFileOrDirectory");
	int fileExists(const char* file_name) WASM_IMPORT("fileExists");
	int makeDirectory(const char* file_name) WASM_IMPORT("makeDirectory");
	int changeDirectory(const char* file_name) WASM_IMPORT("changeDirectory") WASM_IMPORT("changeDirectory");
	int getDirectoryItemByIndex(const char* directory, const char* file_name, int include_extension, int index)
		WASM_IMPORT("getDirectoryItemByIndex");
	void getVolumeInfo(int* free, int* total) WASM_IMPORT("getVolumeInfo");
	int removeFileOrDirectory(const char* file_name) WASM_IMPORT("removeFileOrDirectory");

	// ===============================================================================
	// User Interface
	// ===============================================================================

	/**
	 * @brief get the data from the event queue
	 * @param data Array to store the event data. Must be at least FWGUI_EVENT_DATA_MAX bytes
	 * @return The oldest event in the queue. See FWGuiEventType for more details.
	 */
	int getEventData(unsigned char* data) WASM_IMPORT("getEventData");
	/**
	 * @brief check if there are events in the queue.
	 * @return 1 if there are events, 0 if there are no events.
	 */
	int hasEvent(void) WASM_IMPORT("hasEvent");

	// ===============================================================================
	// Panels
	// ===============================================================================
	/**
	 * @brief Add a new panel.
	 * @param index the index of the panel. Starts at zero.
	 * @param visible if the panel should be visible.
	 * @param in_rotation TODO
	 * @param use_tile if the panel should use tiles.
	 * @param tile_id the id of the tile to use.
	 * @param bg_red the red value of the background color. 0-255
	 * @param bg_green the green value of the background color. 0-255
	 * @param bg_blue the blue value of the background color. 0-255
	 * @param show_menu if the panel should show the menu.
	 */
	void addPanel(int index, int visible, int in_rotation, int use_tile, int tile_id, int bg_red, int bg_green, int bg_blue, int show_menu)
		WASM_IMPORT("addPanel");

	/// @brief
	/// @param index
	/// @param szCaption
	/// @param iTileID
	/// @param iIconID
	/// @param iRBack
	/// @param iGBack
	/// @param iBBack
	/// @param iRFore
	/// @param iGFore
	/// @param iBFore
	/// @param iLogIndex
	void addPanelPickList(int index,
		const char* szCaption,
		int iTileID,
		int iIconID,
		unsigned char iRBack,
		unsigned char iGBack,
		unsigned iBBack,
		unsigned char iRFore,
		unsigned char iGFore,
		unsigned iBFore,
		int iLogIndex) WASM_IMPORT("addPanelPickList");

	/// @brief
	/// @param iPanel
	/// @param iButtonGreyFromZero
	/// @param message
	void setPanelMenuText(int iPanel, int iButtonGreyFromZero, const char* message) WASM_IMPORT("setPanelMenuText");

	////////// controls
	void addControlLED(int index,
		int iControlIndex,
		int iX,
		int iY,
		ePanelColorLED iColor,
		ePanelSizeLED iSize,
		int iIntialState) WASM_IMPORT("addControlLED"); // redefined and implemented

	void setListItemText(int iLogIndex, int iListIndex, const char* szText) WASM_IMPORT("setListItemText");
	void setListItemSelected(int iLogIndex, int iListIndex);
	void setListItemTopIndex(int iLogIndex, int iListIndex);
	void clearLogOrPlotData(int iLogIndexPlusOne, int iPlotIndexPlusOne) WASM_IMPORT("clearLogOrPlotData");

	void addControlLogList(int index,
		int iControlIndex,
		int visible,
		int iLog,
		int iX,
		int iY,
		int iWidth,
		int iHeight,
		int iFontType,
		int iFontSize,
		int iR,
		int iG,
		int iB,
		int iRFont,
		int iGFont,
		int iBFont,
		int iListMode) WASM_IMPORT("addControlLogList");

	void addControlPlotXAxis(int index, int iControlIndex, int iScrollMode, unsigned long long iTimeMin, unsigned long long iTimeMax)
		WASM_IMPORT("addControlPlotXAxis");

	void addControlPlotData(int iPlotDataIndex, int iR, int iG, int iB) WASM_IMPORT("addControlPlotData");

	void addControlPlot(int index,
		int iControlIndex,
		int visible,
		int iPlotDataIndexBitField,
		int iX,
		int iY,
		int iWidth,
		int iHeight,
		int iMin,
		int iMax,
		int iR,
		int iG,
		int iB) WASM_IMPORT("addControlPlot");
	void addControlNumber(int index,
		int iControlIndex,
		int visible,
		int iX,
		int iY,
		int iWidth,
		int iFontSize,
		int iFontType,
		int iR,
		int iG,
		int iB,
		int iIsFloat,
		int iFloatDigits,
		int bIsHexFormat,
		int bIsUnsigned) WASM_IMPORT("addControlNumber");
	void addControlPicture(int index, int iControlIndex, int iX, int iY, int iPictureId, int visible) WASM_IMPORT("addControlPicture");
	/**
	 * @brief Add a text control to a panel.
	 * @param panel_index the index of the panel
	 * @param control_index the index of the control
	 * @param x the x position
	 * @param y the y position
	 * @param font_type the font type
	 * @param font_size the font size
	 * @param red the red value. 0-255
	 * @param green the green value. 0-255
	 * @param blue the blue value. 0-255
	 * @param text_value the text to display.
	 * */
	void addControlText(int panel_index,
		int control_index,
		int x,
		int y,
		int font_type,
		int font_size,
		int red,
		int green,
		int blue,
		const char* text_value) WASM_IMPORT("addControlText");
	void addControlBargraph(int index,
		int iControlIndex,
		int visible,
		int iX,
		int iY,
		int iWidth,
		int iHeight,
		int iMin,
		int iMax,
		int iR,
		int iG,
		int iB) WASM_IMPORT("addControlBargraph");

	void addControlButton(int index,
		int iControlIndex,
		int visible,
		int iX,
		int iY,
		int iWidth,
		int iHeight,
		int iR,
		int iG,
		int iB,
		int iRFore,
		int iGFore,
		int iBFore,
		const char* szText) WASM_IMPORT("addControlButton");

	void setControlValueMinMax(int index, int iControlIndex, int bEnableMinMax, int iMin, int iMax) WASM_IMPORT("setControlValueMinMax");
	void setControlValueMinMaxF(int index, int iControlIndex, int bEnableMinMax, float iMinF, float iMaxF)
		WASM_IMPORT("setControlValueMinMaxF");

	void setLogDataText(int iLogIndex, const char* szText) WASM_IMPORT("setLogDataText");
	void setPlotData(int iPlotData, int iSettings, int iNewValue) WASM_IMPORT("setPlotData");
	void setControlValue(int index, int iControlIndex, int iNewValue) WASM_IMPORT("setControlValue");
	void setControlValueFloat(int index, int iControlIndex, float fNewValue) WASM_IMPORT("setControlValueFloat");

	/**
	 * @brief Instructs the display processor to not sink any of the button events first
         * @param CanReactToButtons Flag to enable or diable sinking button events on display
  	 */
	void setCanDisplayReactToButtons(int CanReactToButtons) WASM_IMPORT("setCanDisplayReactToButtons");

	/**
	 * @brief exit to the main app menu
	 */
	void exitToMainAppMenu(void) WASM_IMPORT("exitToMainAppMenu");

	/**
	 * @brief Show a panel
	 * @param index the index of the panel to show
	 */
	void showPanel(int index) WASM_IMPORT("showPanel");

	/**
	 * @brief add a picture control from a file to a panel
	 * @param panel_index the index of the panel to add the picture to
	 * @param control_index the index of the control
	 * @param x the x position of the picture
	 * @param y the y position of the picture
	 * @param file_name the name of the file to load. expects the file to be in the /images folder
	 * @param visible if the control should be visible
	 */
	void addControlPictureFromFile(int panel_index, int control_index, int x, int y, const char* file_name, int visible)
		WASM_IMPORT("addControlPictureFromFile");

	// ===============================================================================
	// Debug Print
	// ===============================================================================
	void printInt(const char* szFormatSpec, printOutColor iColor, printOutDataType iDataType, int iDataValue) WASM_IMPORT("printInt");
	void printFloat(const char* szFormatSpec, printOutColor iColor, float fDataItem) WASM_IMPORT("printFloat");

	// ===============================================================================
	// Sensors
	// ===============================================================================
	void setAudioSettings(int bStreamMic,
		int bStreamFFT,
		int bEnableMicPlotData,
		int iMICPlotDataIndex,
		int bEnableFFTPlotData,
		int iFFTPlotDataIndex) WASM_IMPORT("setAudioSettings");

	// ===============================================================================
	// FPGA
	// ===============================================================================
	int loadFPGAFromFile(const char* file_name) WASM_IMPORT("loadFPGAFromFile");

	// ===============================================================================
	// Zoom IO
	// ===============================================================================
	int runZoomIOScript(const char* szScript) WASM_IMPORT("runZoomIOScript");

	// ===============================================================================
	// RTC
	// ===============================================================================
	void getRTC(void) WASM_IMPORT("getRTC");

	// ===============================================================================
	// Sensor Streaming
	// ===============================================================================

	void setSensorSettings(int bStreamAccel,
      int bStreamTemp,
      int iRateMilliseconds,
      int bEnableAccelXPlotData,
      int iAccelXPlotDataIndex,
      int bEnableAccelYPlotData,
      int iAccelYPlotDataIndex,
      int bEnableAccelZPlotData,
      int iAccelZPlotDataIndex,
      int bEnableTempPlotDataC,
      int iTempPlotDataIndexC,
      int bEnableTempPlotDataF,
      int iTempPlotDataIndexF) WASM_IMPORT("setSensorSettings");

	void setAppLogSettings(int bLogIRCodes, int bLogAccel, int bLogTempC, int bLogTempF, int iLogIndex) WASM_IMPORT("setAppLogSettings");

	// ===============================================================================
	// Dialogs
	// ===============================================================================
	void showDialogMsgBox(const char* message, int show_ok, int show_ok_cancel, int show_yes_no, int picture_index, int auto_close_half_sec)
		WASM_IMPORT("showDialogMsgBox");
	void showDialogProgressBar(const char* message, int picture_index, int value, int show_ok_to_close)
		WASM_IMPORT("showDialogProgressBar");
	void showDialogNumEdit(const char* message, int bUnsigned, int hex_format, int use_min_max, int initial_value, int minimum, int maximum)
		WASM_IMPORT("showDialogNumEdit");
	void showDialogNumEditFloat(const char* message, int digits, int use_min_max, float initial_value, int minimum, int maximum)
		WASM_IMPORT("showDialogNumEditFloat");
	void showDialogTextEdit(const char* message, const char* initial_value) WASM_IMPORT("showDialogTextEdit");
	void showDialogPickList(const char* message, int log_index, int default_item) WASM_IMPORT("showDialogPickList");

#ifdef __cplusplus
} // extern "C"
#endif
