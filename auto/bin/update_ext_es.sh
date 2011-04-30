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

#remove comments from GL_OES_EGL_image_external
   sed s/.*"void"/\\tvoid/ < $1/GL_OES_EGL_image_external >tmp
   mv tmp $1/GL_OES_EGL_image_external

# remove duplicates in GL_OES_EGL_image_external and GL_OES_EGL_image
#TODO: fix for duplicate functions ??
    head -1 $1/GL_OES_EGL_image_external > tmp  
	grep -v -F -f $1/GL_OES_EGL_image $1/GL_OES_EGL_image_external >> tmp
	sed 's/txt/ txt \nGL_OES_EGL_image_external /g' tmp > tmp1
	mv tmp1 $1/GL_OES_EGL_image_external
	

# fix GL_OES_EGL_image 
    sed 's/eglImageOES/GLeglImageOES/g' $1/GL_OES_EGL_image > tmp
    mv tmp $1/GL_OES_EGL_image
    cat >> $1/GL_OES_EGL_image <<EOT
	typedef void* GLeglImageOES
EOT

# fix GL_OES_EGL_image_external 
    sed 's/eglImageOES/GLeglImageOES/g' $1/GL_OES_EGL_image_external > tmp
    mv tmp $1/GL_OES_EGL_image_external

# modify GL_SUN_multi_draw_arrays to have SUN version of functions
    sed 's/EXT /SUN /g' $1/GL_SUN_multi_draw_arrays > tmp
    mv tmp $1/GL_SUN_multi_draw_arrays
	
# add missing tokens to GL_OES_texture_3D
	cat >> $1/GL_OES_texture_3D <<EOT
	GL_SAMPLER_3D_OES 0x8B5F
EOT


# Note: IMG/IMG_user_clip_plane has broken function definitions!
  sed s/.*"void"/\\tvoid/ $1/GL_IMG_user_clip_plane >tmp
  sed '$d' < tmp > tmp2
  mv tmp2 $1/GL_IMG_user_clip_plane


# NOTE: GL_COVERAGE_SAMPLES_NV values differ between GL_NV_multisample_coverage
# TODO: Fix this bug??
# presently removing its value from GL_NV_coverage_sample 
    grep -v "GL_COVERAGE_SAMPLES_NV" $1/GL_NV_coverage_sample > tmp
    mv tmp $1/GL_NV_coverage_sample

# clean up
    #rm -f $1/*.bak

fi

