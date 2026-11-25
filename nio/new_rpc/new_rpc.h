/******************************************************************************
 *
 *    new_rpc.h
 *
 *    Copyright (C) 2002-2005  <Chris Nystrom>
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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

#ifndef _NEW_RPC_H
#define _NEW_RPC_H

#ifndef _TYPES_H
#include "types.h"
#endif

#ifndef _SOCK_LIB_H
#include "sock_lib.h"
#endif

#define NRPC_EXIT         (-1)
#define NRPC_REVERSE      (-2)
#define NRPC_INVALID      (-3)

#ifdef  __cplusplus
extern "C" {
#endif

void   nrpc_init_server(void);
void   nrpc_welcome(char *str);

int    nrpc_init_client(SOCKET s);
void   nrpc_send_message(void);
void   nrpc_send_response(void);
void   nrpc_reverse(void);
void   nrpc_exit(void);
//void   nrpc_close(void);

void   nrpc_set_function(Sint16 func_num);
Sint16 nrpc_get_function(void);
void   nrpc_std_response(void);
void   nrpc_wait_for_reverse(void);

#ifdef  __cplusplus
}
#endif

#endif /* _NEW_RPC_H */

