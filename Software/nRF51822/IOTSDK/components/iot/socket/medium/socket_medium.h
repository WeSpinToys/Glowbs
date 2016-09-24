/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */
#ifndef SOCKET_MEDIUM_H__
#define SOCKET_MEDIUM_H__

#include <stdint.h>
#include "iot_defines.h"

uint32_t  socket_medium_init(void);
void      socket_medium_start(void);
eui64_t * socket_medium_local_iid(void);

#endif
