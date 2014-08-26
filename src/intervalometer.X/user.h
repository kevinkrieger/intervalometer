/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define DISPLAY_TIME_MS 1500
#define SHUTTER_LENGTH_MS 500
#define HALFPRESS_LENGTH_MS 500
#define SHUTTER RA0
#define HALFPRESS RA1
#define LED1 RB1
#define LED2 RB2
#define LED3 RB3

//#define DEBUG

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* Take a picture */
void takepicture(void);

/* Function to increment interval to the next available interval */
void increment_interval(void);

/* Set the global interval_s value in seconds using the global interval value */
void set_interval_s(void);

/* Display the current interval on the LEDs */
void display_interval(void);

/* Store the interval in memory in case of power outage */
void store_interval(void);

void prepare_for_sleep(void);

void InitApp(void);         /* I/O and Peripheral Initialization */
