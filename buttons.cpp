#include "fwwasm.h"


// Define sound frequencies for different buttons
#define SOUND_GRAY    440  // A4
#define SOUND_YELLOW  494  // B4
#define SOUND_GREEN   523  // C5
#define SOUND_BLUE    587  // D5
#define SOUND_RED     659  // E5
#define SOUND_DURATION 100 // Duration in milliseconds

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
    addControlText(0, 1, 80, 50, 0, 24, 255, 255, 255, "I hate free wili");
    addControlText(0, 2, 80, 100, 0, 20, 200, 200, 255, "Waiting...");
    addControlText(0, 3, 80, 130, 0, 16, 255, 220, 180, "Count: 0");
    
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
    
    // Counter for button presses
    int pressCount = 0;
    
    // Main event loop
    while (1) {
        if (hasEvent()) {
            int eventType = getEventData(eventData);
            
            if (eventType >= FWGUI_EVENT_GRAY_BUTTON && eventType <= FWGUI_EVENT_RED_BUTTON) {
                pressCount++;
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
                
                // Enhanced display information
                // Line 1: Button name and action
                char displayBuffer[32];
                pos = 0;
                for (int i = 0; buttonName[i]; i++) displayBuffer[pos++] = buttonName[i];
                displayBuffer[pos++] = ' ';
                displayBuffer[pos++] = '-';
                displayBuffer[pos++] = ' ';
                for (int i = 0; actionName[i]; i++) displayBuffer[pos++] = actionName[i];
                displayBuffer[pos] = '\0';
                
                // Update text with enhanced information
                addControlText(0, 2, 80, 100, 0, 20, 200, 200, 255, displayBuffer);
                
                // Add count information on a second line
                char countBuffer[16];
                pos = 0;
                const char* countPrefix = "Count: ";
                for (int i = 0; countPrefix[i]; i++) countBuffer[pos++] = countPrefix[i];
                
                // Convert count to string
                int tempCount = pressCount;
                char digits[10];
                int digitPos = 0;
                
                do {
                    digits[digitPos++] = '0' + (tempCount % 10);
                    tempCount /= 10;
                } while (tempCount > 0);
                
                // Reverse the digits
                for (int i = digitPos - 1; i >= 0; i--) {
                    countBuffer[pos++] = digits[i];
                }
                countBuffer[pos] = '\0';
                
                // Add count text on a new line
                addControlText(0, 3, 80, 130, 0, 16, 255, 220, 180, countBuffer);
                
                // Play a sound based on which button was pressed
                int frequency = 440; // Default frequency (A4)
                
                switch (eventType) {
                    case FWGUI_EVENT_GRAY_BUTTON:
                        frequency = SOUND_GRAY;
                        break;
                    case FWGUI_EVENT_YELLOW_BUTTON:
                        frequency = SOUND_YELLOW;
                        break;
                    case FWGUI_EVENT_GREEN_BUTTON:
                        frequency = SOUND_GREEN;
                        break;
                    case FWGUI_EVENT_BLUE_BUTTON:
                        frequency = SOUND_BLUE;
                        break;
                    case FWGUI_EVENT_RED_BUTTON:
                        frequency = SOUND_RED;
                        break;
                }
                
                // Play the sound
                
                playSoundFromFile("/audio/fish.wav");
                // playSoundFromFrequencyAndDuration(frequency, SOUND_DURATION, 0.2, 0);
                
                // Flash LED briefly
                setBoardLED(0, 0, 255, 0, 100, ledflash);
            }
        }
        
        // Increased delay to reduce processing
        waitms(20);
    }
    
    return 0;
}
