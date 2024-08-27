#ifndef __TOUCH_H
#define __TOUCH_H

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <strings.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int capture_touch_events(int *x, int *y, int *event_type);

#endif