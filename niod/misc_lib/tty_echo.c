/******************************************************************************
 *
 *    tty_echo.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lessor General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/lessor.html
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 */

//    From unix programming FAQ
//
//    http://www.erlenstar.demon.co.uk/unix/faq_4.html

#include <termios.h>
#include "misc_lib.h"

PRIVATE struct termios stored_settings;

PUBLIC void echo_off(void)
{
	struct termios new_settings;

	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ECHO);
	tcsetattr(0, TCSANOW, &new_settings);
	return;
}

PUBLIC void echo_on(void)
{
	tcsetattr(0, TCSANOW, &stored_settings);
	return;
}
