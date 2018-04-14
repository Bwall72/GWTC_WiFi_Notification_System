#define RED 14
#define GREEN 5
#define BLUE 16

#define NUM_NOTIFICATIONS 3

String keys[] = {"key0", "key1", "key2"};

// RGB LED
const int red[10]   = {255, 0, 0, 90, 35, 0, 95, 0, 80, 80};
const int green[10] = {0, 255, 0, 60, 70, 60, 90, 45, 40, 60}; 
const int blue[10]  = {0, 0, 255, 0, 90, 50, 25, 70, 0, 70};
#define RED_OFF   analogWrite(RED, 0)
#define GREEN_OFF analogWrite(GREEN, 0)
#define BLUE_OFF  analogWrite(BLUE, 0)
int active[NUM_NOTIFICATIONS];
int notifications = 0;

// Button
#define BUTTON 12

// notification array values
#define KEY0 0
#define KEY1 1
#define KEY2 2

// dweet
dweet client;
#define THING "brandonwemosd1"
#define DELAY 3000 // polling rate for dweet
HTTPClient http;


// i: polling dweet
// j: RGB LED color switch
// k: other loops
int i = 0, j = 0, k = 0;

int poll_time;
int led_time;

void reset_dweet();
void run_dweet();
void run_led();
void check_reset();
void print_active();
