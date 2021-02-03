# Use, modification, and distribution are
# subject to the Boost Software License, Version 1.0. (See accompanying
# file LICENSE.txt)
#
# Copyright Rene Rivera 2020.

# For Drone CI we use the Starlark scripting language to reduce duplication.
# As the yaml syntax for Drone CI is rather limited.
#
#
globalenv={}
linuxglobalimage="cppalliance/droneubuntu1604:1"
windowsglobalimage="cppalliance/dronevs2019"

def main(ctx):
  return [
  linux_cxx("TOOLSET=gcc CXXSTD=03,11 Job 0", "g++", packages="", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': 'b6589fc6ab'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc-4.4 CXXSTD=98,0x Job 1", "g++", packages="g++-4.4", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc-4.4', 'CXXSTD': '98,0x', 'DRONE_JOB_UUID': '356a192b79'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc-4.6 CXXSTD=03,0x Job 2", "g++", packages="g++-4.6", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc-4.6', 'CXXSTD': '03,0x', 'DRONE_JOB_UUID': 'da4b9237ba'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc-5 CXXSTD=03,11 Job 3", "g++-5", packages="g++-5", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc-5', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': '77de68daec'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc-5 CXXSTD=14,1z Job 4", "g++-5", packages="g++-5", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc-5', 'CXXSTD': '14,1z', 'DRONE_JOB_UUID': '1b64538924'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc-6 CXXSTD=03,11 Job 5", "g++-6", packages="g++-6", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc-6', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': 'ac3478d69a'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc-6 CXXSTD=14,1z Job 6", "g++-6", packages="g++-6", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc-6', 'CXXSTD': '14,1z', 'DRONE_JOB_UUID': 'c1dfd96eea'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc-7 CXXSTD=03,11 Job 7", "g++-7", packages="g++-7", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc-7', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': '902ba3cda1'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc-7 CXXSTD=14,17 Job 8", "g++-7", packages="g++-7", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc-7', 'CXXSTD': '14,17', 'DRONE_JOB_UUID': 'fe5dbbcea5'}, globalenv=globalenv),
  linux_cxx("TOOLSET=clang CXXSTD=03,11 Job 9", "clang++", packages="", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'clang', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': '0ade7c2cf9'}, globalenv=globalenv),
  linux_cxx("TOOLSET=clang CXXSTD=14,1z Job 10", "clang++", packages="libstdc++-4.9-dev", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'clang', 'CXXSTD': '14,1z', 'DRONE_JOB_UUID': 'b1d5781111'}, globalenv=globalenv),
  # Not building  #
  #  osx_cxx("TOOLSET=clang CXXSTD=03,11 Job 11", "clang++", packages="", buildtype="boost", buildscript="drone", environment={'TOOLSET': 'clang', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': '17ba079149'}, globalenv=globalenv),
  # Not building  #
  #  osx_cxx("TOOLSET=clang CXXSTD=14,1z Job 12", "clang++", packages="", buildtype="boost", buildscript="drone", environment={'TOOLSET': 'clang', 'CXXSTD': '14,1z', 'DRONE_JOB_UUID': '7b52009b64'}, globalenv=globalenv),
    ]

# from https://github.com/boostorg/boost-ci
load("@boost_ci//ci/drone/:functions.star", "linux_cxx","windows_cxx","osx_cxx","freebsd_cxx")
