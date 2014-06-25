#==================================================================================================#
#                                                                                                  #
#  Copyright 2013 MaidSafe.net limited                                                             #
#                                                                                                  #
#  This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,        #
#  version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which    #
#  licence you accepted on initial access to the Software (the "Licences").                        #
#                                                                                                  #
#  By contributing code to the MaidSafe Software, or to this project generally, you agree to be    #
#  bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root        #
#  directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also available   #
#  at: http://www.maidsafe.net/licenses                                                            #
#                                                                                                  #
#  Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed    #
#  under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF   #
#  ANY KIND, either express or implied.                                                            #
#                                                                                                  #
#  See the Licences for the specific language governing permissions and limitations relating to    #
#  use of the MaidSafe Software.                                                                   #
#                                                                                                  #
#==================================================================================================#
#                                                                                                  #
#  Sets up Boost using ExternalProject_Add.                                                        #
#                                                                                                  #
#  Only the first 2 variables should require regular maintenance, i.e. BoostVersion & BoostSHA1.   #
#                                                                                                  #
#  If USE_BOOST_CACHE is set, boost is downloaded, extracted and built to a directory outside of   #
#  the MaidSafe build tree.  The chosen directory can be set in BOOST_CACHE_DIR, or if this is     #
#  empty, an appropriate default is chosen for the given platform.                                 #
#                                                                                                  #
#  Variables set and cached by this module are:                                                    #
#    BoostSourceDir (required for subsequent include_directories calls) and per-library            #
#    variables defining the libraries, e.g. BoostDateTimeLibs, BoostFilesystemLibs.                #
#                                                                                                  #
#==================================================================================================#


include(utils)



set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")


if(APPLE)
  cmake_minimum_required(VERSION 2.8.12.2 FATAL_ERROR)
else()
  cmake_minimum_required(VERSION 2.8.11.1 FATAL_ERROR)
endif()

set(BoostVersion 1.53.0)
set(BoostSHA1 e6dd1b62ceed0a51add3dda6f3fc3ce0f636a7f3)


if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Third_Parties/boost_${BoostVersion}/")


# Create build folder name derived from version
string(REGEX REPLACE "beta\\.([0-9])$" "beta\\1" BoostFolderName ${BoostVersion})
string(REPLACE "." "_" BoostFolderName ${BoostFolderName})
set(BoostFolderName boost_${BoostFolderName})

# If user wants to use a cache copy of Boost, get the path to this location.
if(USE_BOOST_CACHE)
  if(BOOST_CACHE_DIR)
    file(TO_CMAKE_PATH "${BOOST_CACHE_DIR}" BoostCacheDir)
  elseif(WIN32)
    ms_get_temp_dir()
    set(BoostCacheDir "${TempDir}")
  elseif(APPLE)
    set(BoostCacheDir "$ENV{HOME}/Library/Caches")
  else()
    set(BoostCacheDir "$ENV{HOME}/.cache")
  endif()
endif()

# If the cache directory doesn't exist, fall back to use the build root.
if(NOT IS_DIRECTORY "${BoostCacheDir}")
  if(BOOST_CACHE_DIR)
    set(Message "\nThe directory \"${BOOST_CACHE_DIR}\" provided in BOOST_CACHE_DIR doesn't exist.")
    set(Message "${Message}  Falling back to default path at \"${CMAKE_BINARY_DIR}/MaidSafe\"\n")
    message(WARNING "${Message}")
  endif()
  set(BoostCacheDir ${CMAKE_BINARY_DIR})
else()
  if(NOT USE_BOOST_CACHE AND NOT BOOST_CACHE_DIR)
    set(BoostCacheDir "${BoostCacheDir}/MaidSafe")
  endif()
  file(MAKE_DIRECTORY "${BoostCacheDir}")
endif()

# Set up the full path to the source directory
set(BoostSourceDir "${BoostFolderName}_${CMAKE_CXX_COMPILER_ID}_${CMAKE_CXX_COMPILER_VERSION}")
if(HAVE_LIBC++)
  set(BoostSourceDir "${BoostSourceDir}_LibCXX")
endif()
if(HAVE_LIBC++ABI)
  set(BoostSourceDir "${BoostSourceDir}_LibCXXABI")
endif()
if(CMAKE_CL_64)
  set(BoostSourceDir "${BoostSourceDir}_Win64")
endif()
string(REPLACE "." "_" BoostSourceDir ${BoostSourceDir})
set(BoostSourceDir "${BoostCacheDir}/${BoostSourceDir}")

# Check the full path to the source directory is not too long for Windows.  File paths must be less
# than MAX_PATH which is 260.  The current longest relative path Boost tries to create is:
# Build\boost\bin.v2\libs\program_options\build\fd41f4c7d882e24faa6837508d6e5384\libboost_program_options-vc120-mt-gd-1_55.lib.rsp
# which along with a leading separator is 129 chars in length.  This gives a maximum path available
# for 'BoostSourceDir' as 130 chars.
if(WIN32)
  get_filename_component(BoostSourceDirName "${BoostSourceDir}" NAME)
  string(LENGTH "/${BoostSourceDirName}" BoostSourceDirNameLengthWithSeparator)
  math(EXPR AvailableLength 130-${BoostSourceDirNameLengthWithSeparator})
  string(LENGTH "${BoostSourceDir}" BoostSourceDirLength)
  if(${BoostSourceDirLength} GREATER 130)
    set(Msg "\n\nThe path to boost's source is too long to handle all the files which will ")
    set(Msg "${Msg}be created when boost is built.  To avoid this, set the CMake variable ")
    set(Msg "${Msg}USE_BOOST_CACHE to ON and set the variable BOOST_CACHE_DIR to a path ")
    set(Msg "${Msg}which is at most ${AvailableLength} characters long.  For example:\n")
    set(Msg "${Msg}  mkdir C:\\maidsafe_boost\n")
    set(Msg "${Msg}  cmake . -DUSE_BOOST_CACHE=ON -DBOOST_CACHE_DIR=C:\\maidsafe_boost\n\n")
    message(FATAL_ERROR "${Msg}")
  endif()
endif()

# Download boost if required
set(ZipFilePath "${BoostCacheDir}/${BoostFolderName}.tar.bz2")
if(NOT EXISTS ${ZipFilePath})
  message(STATUS "Downloading boost ${BoostVersion} to ${BoostCacheDir}")
endif()
file(DOWNLOAD http://sourceforge.net/projects/boost/files/boost/${BoostVersion}/${BoostFolderName}.tar.bz2/download
     ${ZipFilePath}
     STATUS Status
     SHOW_PROGRESS
     EXPECTED_HASH SHA1=${BoostSHA1}
     )

# Extract boost if required
string(FIND "${Status}" "returning early" Found)
if(Found LESS 0 OR NOT IS_DIRECTORY "${BoostSourceDir}")
  set(BoostExtractFolder "${BoostCacheDir}/boost_unzip")
  file(REMOVE_RECURSE ${BoostExtractFolder})
  file(MAKE_DIRECTORY ${BoostExtractFolder})
  file(COPY ${ZipFilePath} DESTINATION ${BoostExtractFolder})
  message(STATUS "Extracting boost ${BoostVersion} to ${BoostExtractFolder}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xfz ${BoostFolderName}.tar.bz2
                  WORKING_DIRECTORY ${BoostExtractFolder}
                  RESULT_VARIABLE Result
                  )
  if(NOT Result EQUAL 0)
    message(FATAL_ERROR "Failed extracting boost ${BoostVersion} to ${BoostExtractFolder}")
  endif()
  file(REMOVE ${BoostExtractFolder}/${BoostFolderName}.tar.bz2)

  # Get the path to the extracted folder
  file(GLOB ExtractedDir "${BoostExtractFolder}/*")
  list(LENGTH ExtractedDir n)
  if(NOT n EQUAL 1 OR NOT IS_DIRECTORY ${ExtractedDir})
    message(FATAL_ERROR "Failed extracting boost ${BoostVersion} to ${BoostExtractFolder}")
  endif()
  file(RENAME ${ExtractedDir} ${BoostSourceDir})
  file(REMOVE_RECURSE ${BoostExtractFolder})
endif()

unset(b2Path CACHE)
find_program(b2Path NAMES b2 PATHS ${BoostSourceDir} NO_DEFAULT_PATH)

if(NOT b2Path)
  message(STATUS "Building b2 (bjam)")
  if(MSVC)
    set(b2Bootstrap "bootstrap.bat")
  else()
    set(b2Bootstrap "./bootstrap.sh")
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
      list(APPEND b2Bootstrap --with-toolset=clang)
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
      list(APPEND b2Bootstrap --with-toolset=gcc)
    endif()
  endif()
  execute_process(COMMAND ${b2Bootstrap} WORKING_DIRECTORY ${BoostSourceDir}
                  RESULT_VARIABLE Result OUTPUT_VARIABLE Output ERROR_VARIABLE Error)
  if(NOT Result EQUAL 0)
    message(FATAL_ERROR "Failed running ${b2Bootstrap}:\n${Output}\n${Error}\n")
  endif()
  endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${BoostSourceDir}/Build)
  # Set up general b2 (bjam) command line arguments
set(b2Args ./b2 link=static threading=multi runtime-link=shared --build-dir=Build stage -d+2 --hash )
if("${CMAKE_BUILD_TYPE}" STREQUAL "ReleaseNoInline")
  list(APPEND b2Args cxxflags="${RELEASENOINLINE_FLAGS}")
endif()
if("${CMAKE_BUILD_TYPE}" STREQUAL "DebugLibStdcxx")
  list(APPEND b2Args define=_GLIBCXX_DEBUG)
endif()

# Set up platform-specific b2 (bjam) command line arguments
if(MSVC)
  if(MSVC11)
    list(APPEND b2Args toolset=msvc-11.0)
  elseif(MSVC12)
    list(APPEND b2Args toolset=msvc-12.0)
  endif()
  list(APPEND b2Args
              define=_BIND_TO_CURRENT_MFC_VERSION=1
              define=_BIND_TO_CURRENT_CRT_VERSION=1
              --layout=versioned
              )
  if(${TargetArchitecture} STREQUAL "x86_64")
    list(APPEND b2Args address-model=64)
  endif()
elseif(APPLE)
  list(APPEND b2Args variant=release toolset=clang cxxflags=-fPIC cxxflags=-std=c++11 cxxflags=-stdlib=libc++
                     linkflags=-stdlib=libc++ architecture=combined address-model=32_64 --layout=tagged)
elseif(UNIX)
  list(APPEND b2Args variant=release cxxflags=-fPIC cxxflags=-std=c++11 -sNO_BZIP2=1 --layout=tagged)
  # Need to configure the toolset based on whatever version CMAKE_CXX_COMPILER is
  string(REGEX MATCH "[0-9]+\\.[0-9]+" ToolsetVer "${CMAKE_CXX_COMPILER_VERSION}")
  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    list(APPEND b2Args toolset=clang-${ToolsetVer})
    if(HAVE_LIBC++)
      list(APPEND b2Args cxxflags=-stdlib=libc++ linkflags=-stdlib=libc++)
    endif()
  elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    list(APPEND b2Args toolset=gcc-${ToolsetVer})
  endif()
endif()


message(${b2Args} )
# Start boost build
execute_process(COMMAND ${b2Args} WORKING_DIRECTORY ${BoostSourceDir}
                  RESULT_VARIABLE Result OUTPUT_VARIABLE Output ERROR_VARIABLE Error)

                  
# Create the directory
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Third_Parties/boost_${BoostVersion}/include")
file(COPY "${BoostSourceDir}/stage/lib" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Third_Parties/boost_${BoostVersion}/")
file(COPY "${BoostSourceDir}/boost" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Third_Parties/boost_${BoostVersion}/include")

endif()
# Clean
file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/${BoostFolderName}.tar.bz2")

