#include "FTRLab.hpp"

WiFiServer server = WiFiServer(3333);
WiFiClient client;

char chipId[CHIP_ID_MAX_SIZE];
hw_timer_t *mdnsUpdateTimer = NULL;

Board board = Board();
