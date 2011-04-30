#!/bin/bash
##
## Copyright (C) 2002-2008, Marcelo E. Magallon <mmagallo[]debian org>
## Copyright (C) 2002-2008, Milan Ikits <milan ikits[]ieee org>
##
## This program is distributed under the terms and conditions of the GNU
## General Public License Version 2 as published by the Free Software
## Foundation or, at your option, any later version.
##
## Parameters:
##
##       $1: Extensions directory
##       $2: Registry directory
##       $3: The black list

set -e

if [ ! -d $1 ] ; then
    mkdir $1

# Parse each of the extensions in the registry
    find $2 -name doc -type d -prune -o -name \*.txt -print | \
	grep -v -f $3 | sort | bin/parse_spec.pl $1

# remove duplicates in EGL_KHR_lock_surface and EGL_KHR_lock_surface2
   head -3 $1/EGL_KHR_lock_surface2 > tmp 
   grep -v -F -f $1/EGL_KHR_lock_surface $1/EGL_KHR_lock_surface2  >> tmp
   mv tmp $1/EGL_KHR_lock_surface2
   

# remove duplicates functions in EGL_KHR_fence_sync and EGL_KHR_reusable_sync
#TODO : fix for duplicate functions ??
    grep -v -F -f $1/EGL_KHR_reusable_sync $1/EGL_KHR_fence_sync  > tmp
    mv tmp $1/EGL_KHR_fence_sync
 
# remove quadlet in EGL_KHR_gl_renderbuffer_image, EGL_KHR_gl_texture_2D_image,
# EGL_KHR_gl_texture_3D_image and EGL_KHR_gl_texture_cubemap_image. 
# All are part of same extension spec file.
    head -3 $1/EGL_KHR_gl_renderbuffer_image > tmp 
    mv tmp $1/EGL_KHR_gl_renderbuffer_image
	head -3 $1/EGL_KHR_gl_texture_cubemap_image > tmp 
    mv tmp $1/EGL_KHR_gl_texture_cubemap_image
	head -3 $1/EGL_KHR_gl_texture_3D_image > tmp 
    mv tmp $1/EGL_KHR_gl_texture_3D_image



# fix EGL_KHR_image_base
   cat >> $1/EGL_KHR_image_base <<EOT
	typedef void *EGLImageKHR
EOT

# fix EGL_KHR_reusable_sync
  cat >> $1/EGL_KHR_reusable_sync <<EOT
	typedef void* EGLSyncKHR
	typedef khronos_utime_nanoseconds_t EGLTimeKHR
EOT

# fix EGL_NV_sync
  cat >> $1/EGL_NV_sync <<EOT
	typedef void* EGLSyncNV
	typedef khronos_utime_nanoseconds_t EGLTimeNV
EOT



# clean up
    rm -f $1/*.bak

fi

