#include "fwwasm.h"

// Use const char arrays for fixed strings to reduce memory usage
const char* const GRAY_BTN = "graybutton";
const char* const YELLOW_BTN = "yellowbutton";
const char* const GREEN_BTN = "greenbutton";
const char* const BLUE_BTN = "bluebutton";
const char* const RED_BTN = "redbutton";
const char* const UNKNOWN = "unknown";

const char* const CLICKED = "clicked";
const char* const DBLCLICK = "doubleclick";
const char* const LONGPRESS = "longpress";
const char* const POWERUP = "poweruppressed";

// Function to get string name of button event
const char* getEventName(int eventType) {
    switch (eventType) {
        case FWGUI_EVENT_GRAY_BUTTON: return GRAY_BTN;
        case FWGUI_EVENT_YELLOW_BUTTON: return YELLOW_BTN;
        case FWGUI_EVENT_GREEN_BUTTON: return GREEN_BTN;
        case FWGUI_EVENT_BLUE_BUTTON: return BLUE_BTN;
        case FWGUI_EVENT_RED_BUTTON: return RED_BTN;
        default: return UNKNOWN;
    }
}

// Function to get string description of button action
const char* getButtonData(int iValue) {
    switch (iValue) {
        case 0: return CLICKED;
        case 1: return DBLCLICK;
        case 2: return LONGPRESS;
        case 3: return POWERUP;
        default: return UNKNOWN;
    }
}

// Main entry point
WASM_EXPORT int main() {
    // Set up a simple UI - use a single panel
    addPanel(0, 1, 1, 0, 0, 0, 0, 0, 1);
    addControlText(0, 1, 80, 50, 0, 24, 255, 255, 255, "Press button for UART data");
    addControlText(0, 2, 80, 100, 0, 20, 200, 200, 255, "Waiting...");
    
    // Simple menu text
    setPanelMenuText(0, 0, "Gray");
    setPanelMenuText(0, 1, "Yellow");
    setPanelMenuText(0, 2, "Green");
    setPanelMenuText(0, 3, "Blue");
    setPanelMenuText(0, 4, "Red");
    
    showPanel(0);
    
    // Use a smaller buffer (32 bytes instead of 64)
    unsigned char eventData[FW_GET_EVENT_DATA_MAX];
    char uartBuffer[32];
    
    // Main event loop
    while (1) {
        if (hasEvent()) {
            int eventType = getEventData(eventData);
            
            if (eventType >= FWGUI_EVENT_GRAY_BUTTON && eventType <= FWGUI_EVENT_RED_BUTTON) {
                const char* buttonName = getEventName(eventType);
                const char* actionName = getButtonData(eventData[0]);
                
                // Simple concatenation to avoid sprintf
                // Format: "BTN:name,ACT:action\r\n"
                int pos = 0;
                const char* prefix1 = "BTN:";
                const char* sep = ",ACT:";
                const char* suffix = "\r\n";
                
                // Manual string building to avoid sprintf
                for (int i = 0; prefix1[i]; i++) uartBuffer[pos++] = prefix1[i];
                for (int i = 0; buttonName[i]; i++) uartBuffer[pos++] = buttonName[i];
                for (int i = 0; sep[i]; i++) uartBuffer[pos++] = sep[i];
                for (int i = 0; actionName[i]; i++) uartBuffer[pos++] = actionName[i];
                for (int i = 0; suffix[i]; i++) uartBuffer[pos++] = suffix[i];
                
                // Send the buffer with exact length
                UARTDataWrite((unsigned char*)uartBuffer, pos);
                
                // Update text with minimal information
                addControlText(0, 2, 80, 100, 0, 20, 200, 200, 255, buttonName);
                
                // Flash LED briefly
                setBoardLED(0, 0, 255, 0, 100, ledflash);
            }
        }
        
        // Increased delay to reduce processing
        waitms(20);
    }
    
    return 0;
}