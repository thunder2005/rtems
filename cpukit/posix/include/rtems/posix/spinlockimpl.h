/**
 * @file
 * 
 * @brief Inlined Routines from the POSIX Spinlock Manager
 *
 * This file contains the static inlin implementation of the inlined
 * routines from the POSIX Spinlock Manager.
 */

/*
 *  COPYRIGHT (c) 1989-2011.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  Copyright (c) 2016 embedded brains GmbH
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifndef _RTEMS_POSIX_SPINLOCKIMPL_H
#define _RTEMS_POSIX_SPINLOCKIMPL_H

#include <pthread.h>

#include <rtems/score/isrlevel.h>

#if defined(RTEMS_SMP)
#include <rtems/score/percpu.h>
#include <rtems/score/smplockticket.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if SIZEOF_PTHREAD_SPINLOCK_T > 4
#define POSIX_SPINLOCKS_ARE_SELF_CONTAINED
#endif

typedef struct {
#if defined(RTEMS_SMP)
  SMP_ticket_lock_Control Lock;
#else
  unsigned int reserved[ 2 ];
#endif
  ISR_Level interrupt_state;
} POSIX_Spinlock_Control;

#if !defined(POSIX_SPINLOCKS_ARE_SELF_CONTAINED)
extern POSIX_Spinlock_Control _POSIX_Spinlock_Global;

extern int _POSIX_Spinlock_Nest_level;

#if defined(RTEMS_SMP)
extern uint32_t _POSIX_Spinlock_Owner;
#endif
#endif

RTEMS_INLINE_ROUTINE POSIX_Spinlock_Control *_POSIX_Spinlock_Get(
  pthread_spinlock_t *lock
)
{
#if defined(POSIX_SPINLOCKS_ARE_SELF_CONTAINED)
  return (POSIX_Spinlock_Control *) lock;
#else
  (void) lock;
  return &_POSIX_Spinlock_Global;
#endif
}

#ifdef __cplusplus
}
#endif

#endif
/*  end of include file */
