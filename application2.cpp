#include "fwwasm.h"

#include <array>
#include <cstdint>
#include <ranges>

const auto NUMBER_OF_LEDS = 7;

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    constexpr Color(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {}
};


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

constexpr Color RED(255, 0, 0);
constexpr Color ORANGE(255, 127, 0);
constexpr Color YELLOW(255, 255, 0);
constexpr Color GREEN(0, 255, 0);
constexpr Color LIGHT_GREEN(0, 255, 191);
constexpr Color BLUE(0, 0, 255);
constexpr Color LIGHT_BLUE(0, 191, 255);
constexpr Color INDIGO(75, 0, 130);
constexpr Color VIOLET(238, 130, 238);
constexpr Color PINK(255, 192, 203);
constexpr Color GRAY(0x30, 0x30, 0x30);
constexpr Color WHITE(255, 255, 255);



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

auto setup_panels() -> void {
    // Setup the main panel that shows pip boy
    addPanel(0, 1, 0, 0, 0, 0, 0, 0, 1);
    addControlPictureFromFile(0, 0, 0, 0, "group.fwi", 1);
    addControlText(0, 1, 90, 180, 1, 64, WHITE.red, WHITE.green, WHITE.blue, "Press a Button");
    showPanel(0);
    // Setup the rest of the panels
    setPanelMenuText(0, 0, "Gray");
    setPanelMenuText(0, 1, "Yellow");
    setPanelMenuText(0, 2, "Green");
    setPanelMenuText(0, 3, "Blue");
    setPanelMenuText(0, 4, "Red");
}

auto transmitRadioSignal(uint8_t channel, const char* message, Color ledColor = WHITE, int flashDuration = 250) -> void {
    // Log the transmission (debugging purposes)
    printInt("\nTransmitting on channel %d: %s\n", printOutColor::printColorNormal, printOutDataType::printUInt32, channel);
    
    // Flash LEDs to indicate transmission
    for (int led_index = 0; led_index < NUMBER_OF_LEDS; led_index++) {
        setBoardLED(led_index, ledColor.red, ledColor.green, ledColor.blue, flashDuration, LEDManagerLEDMode::ledpulse);
    }
    
    // Transmit the message
    RadioTxSubFile(channel, message);
    
    // Wait for the radio to stop transmitting
    while (RadioSubFileIsTransmitting() != 0) {
        waitms(33);
    }
    
    // Optional: Play a confirmation sound
    playSoundFromFile("/transmit_complete.wav");
    
    printInt("\nTransmission complete\n", printOutColor::printColorNormal, printOutDataType::printUInt32, 0);
}

auto hacker1(){
    playSoundFromFile("/oe.wav"); // Correct
    for(int i = 0; i < 20; i++) {
        addControlPictureFromFile(4, 0, 0, 0, "cat.fwi", 1);
        showPanel(4);
        waitms(70);
        addControlPictureFromFile(5, 0, 0, 0, "cat2.fwi", 1);
        showPanel(5);
        waitms(70);
        addControlPictureFromFile(6, 0, 0, 0, "cat4.fwi", 1);
        showPanel(6);
        waitms(70);
    }
    addControlPictureFromFile(7, 0, 0, 0, "cat3.fwi", 1);
    showPanel(7);
    addControlText(7, 1, 90, 20, 1, 64, WHITE.red, WHITE.green, WHITE.blue, "Joey Volcic");
    addControlText(7, 2, 90, 40, 1, 64, WHITE.red, WHITE.green, WHITE.blue, "Git: @sammichman");
    addControlText(7, 3, 90, 60, 1, 64, WHITE.red, WHITE.green, WHITE.blue, "Happy GRIZZ HACKS");
    waitms(8000);
    showPanel(0);
}

struct PanelInfo {
    const uint8_t index;
    const FWGuiEventType event_type;
    const Color color;
    const char* text;
    const char* sub_fname;
};

constexpr std::array Panels{
    PanelInfo{1, FWGuiEventType::FWGUI_EVENT_GRAY_BUTTON, GRAY, "GRAY", "/radio/white.sub"},
    PanelInfo{2, FWGuiEventType::FWGUI_EVENT_YELLOW_BUTTON, YELLOW, "YELLOW", "/radio/yellow.sub"},
    PanelInfo{3, FWGuiEventType::FWGUI_EVENT_GREEN_BUTTON, GREEN, "GREEN", "/radio/green.sub"},
    PanelInfo{4, FWGuiEventType::FWGUI_EVENT_BLUE_BUTTON, BLUE, "BLUE", "/radio/blue.sub"},
    PanelInfo{5, FWGuiEventType::FWGUI_EVENT_RED_BUTTON, RED, "RED", "/radio/red.sub"},
};

WASM_EXPORT int main() {
    setup_panels();
    RadioSetRx(1);
    bool trigger = false;
    bool soundPlayed = false; // Track if we've already played the sound for this signal
    int loopCount = 0;
    
    while (1)
    {

        //Flash LED to indicate transmitting
        setBoardLED(0, 0, 0, 255, 100, LEDManagerLEDMode::ledflash);

        // Transmit blue.sub at the beginning of each loop
        RadioTxSubFile(1, "/radio/blue.sub");
        // Wait for the radio to stop transmitting
        while (RadioSubFileIsTransmitting() != 0) {
        waitms(33);
        }

        // Stop LEDS
        setBoardLED(0, 0, 0, 0, 0, LEDManagerLEDMode::ledflash);

        // Switch to receive mode explicitly
        RadioSetIdle(1);
        waitms(50);
        RadioSetRx(1);
        waitms(50);   

      // unsigned char dataBuf[1024];
      // int length;
      int rssi;
      rssi = RadioGetRSSI(1);
      if (rssi > -80) {
        if (loopCount == 0){
            hacker1();

            // trigger = true;
            RadioSetIdle(1);
            waitms(100);
            RadioSetRx(1);
            loopCount = 200;
        }
        else if (loopCount > 0)
        {
            loopCount--;
        }
      } else {
        // printInt("\nBad read, RSSI = %d...\n", printOutColor::printColorNormal, printOutDataType::printUInt32, rssi);
        showPanel(0);
        RadioSetIdle(1);
        waitms(100);
        RadioSetRx(1);
        // soundPlayed = false; // Reset the flag when we lose signal
      }
      waitms(20);
    }
   }
