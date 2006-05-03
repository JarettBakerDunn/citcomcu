/*
 * CitcomCU is a Finite Element Code that solves for thermochemical
 * convection within a three dimensional domain appropriate for convection
 * within the Earth's mantle. Cartesian and regional-spherical geometries
 * are implemented. See the file README contained with this distribution
 * for further details.
 * 
 * Copyright (C) 1994-2005 California Institute of Technology
 * Copyright (C) 2000-2005 The University of Colorado
 *
 * Authors: Louis Moresi, Shijie Zhong, and Michael Gurnis
 *
 * For questions or comments regarding this software, you may contact
 *
 *     Luis Armendariz <luis@geodynamics.org>
 *     http://geodynamics.org
 *     Computational Infrastructure for Geodynamics (CIG)
 *     California Institute of Technology
 *     2750 East Washington Blvd, Suite 210
 *     Pasadena, CA 91007
 *
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 2 of the License, or any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */


/***********************************************************************
 *                                                                     *
 * WARNING: This file is auto-generated by the script `prototypes.py'. *
 *                                                                     *
 * Since the function prototypes can be generated, you should modify   *
 * the function definitions instead. You can then use the script to    *
 * keep the headers up to date.                                        *
 *                                                                     *
 * You can add (almost) anything you want in the section between the   *
 * BEGIN and END comments and it will be preserved.  Anything outside  *
 * those comments will be overwritten in the next pass.                *
 *                                                                     *
 * Ignore this warning if you will be maintaining this file manually   *
 * from now on.                                                        *
 *                                                                     *
 ***********************************************************************/


#ifndef __TOPO_GRAVITY_H__
#define __TOPO_GRAVITY_H__

/** BEGIN **/
#include "element_definitions.h"
#include "global_defs.h"
/** END **/

/* Topo_gravity.c */
void get_CBF_topo(struct All_variables *E, float *H, float *HB);
void get_STD_topo(struct All_variables *E, float *tpg, float *tpgb, int ii);

/* cproto command: /usr/bin/cproto -q -p -f 3 Topo_gravity.c */
#endif