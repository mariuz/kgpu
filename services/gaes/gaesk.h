/* This work is licensed under the terms of the GNU GPL, version 2.  See
 * the GPL-COPYING file in the top-level directory.
 *
 * Copyright (c) 2010-2011 University of Utah and the Flux Group.
 * All rights reserved.
 *
 * KGPU GAES header
 */

#ifndef __GAESK_H__
#define __GAESK_H__

#include "gaes_common.h"

#define GAES_ECB_SIZE_THRESHOLD (PAGE_SIZE)

struct async_gaes_info {
    int (*callback)(struct async_gaes_info*);
    void *data;
};


static void big_u128_add(u8 *ctr, u64 offset, u8 *res)
{
    u64 c = be64_to_cpu((u64*)(ctr+8));

    c += offset;
    *(u64*)(res) = *(u64*)(ctr);
    *(u64*)(res+8) = cpu_to_be64(c);
}

static void cvt_endian_u32(u32* buf, int n)
{
  u8* b = (u8*)buf;
  int nb = n*4;
  
  u8 t;
  int i;
  
  for (i=0; i<nb; i+=4, b+=4) {
    t = b[0];
    b[0] = b[3];
    b[3] = t;
    
    t = b[1];
    b[1] = b[2];
    b[2] = t;
  }
}


static void dump_page_content(u8 *p)
{
    int r,c;
    printk("dump page content:\n");
    for (r=0; r<16; r++) {
	for (c=0; c<32; c++)
	    printk("%02x ", p[r*32+c]);
	printk("\n");
    }
}

#endif
