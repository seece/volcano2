/* Some utility functions to help with porting. */

static void itoa_fake(int value, char* buf, int base) {
	// base is ignored, always 10
	sprintf(buf, "%d", value);
}

