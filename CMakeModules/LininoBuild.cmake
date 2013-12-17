# -*- mode: cmake; -*-
#
#  Configure and build OpenWRT environement
#

#set(_openwrt_url "svn://svn.openwrt.org/openwrt/")
set(_openwrt_url "https://github.com/arduino/linino")

macro(openwrt_single_checkout _target _workdir _url _destdir _output )
  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/openwrt/${_output}
    COMMAND svn co ${_openwrt_url}/${_url} ${_destdir}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${_workdir}
    COMMENT "Checkout openwrt sources"
    )
  add_custom_target(${_target} DEPENDS ${CMAKE_BINARY_DIR}/openwrt/${_output})
endmacro()

#
#
function(openwrt_checkout)
  openwrt_single_checkout(openwrt_checkout openwrt branches/backfire . Makefile)

  openwrt_single_checkout(openwrt_package_sqlite3 openwrt/package packages/libs/sqlite3 sqlite3 package/sqlite3/Makefile)

  openwrt_single_checkout(openwrt_package_boost openwrt/package packages/libs/boost boost package/boost/Makefile)

  openwrt_single_checkout(openwrt_package_curl openwrt/package packages/libs/curl curl package/curl/Makefile)

  openwrt_single_checkout(openwrt_package_libmicrohttpd openwrt/package packages/libs/libmicrohttpd libmicrohttpd package/libmicrohttpd/Makefile)

  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/package.done
    COMMAND touch  ${CMAKE_BINARY_DIR}/package.done
    DEPENDS
    ${CMAKE_BINARY_DIR}/openwrt/package/libmicrohttpd/Makefile
    ${CMAKE_BINARY_DIR}/openwrt/package/curl/Makefile
    ${CMAKE_BINARY_DIR}/openwrt/package/boost/Makefile
  )
  add_custom_target(openwrt_package
    DEPENDS  ${CMAKE_BINARY_DIR}/package.done
  )
endfunction(openwrt_checkout)

function(openwrt_configure)
  file(WRITE ${CMAKE_BINARY_DIR}/openwrt/feeds.conf "src-link itwm ${CMAKE_SOURCE_DIR}/package")


  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/feeds.done
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds update -a itwm
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds update packages
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds install  openssl
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds install -p itwm libsml
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds install -p packages uuid
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds install -p packages boost
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds install -p packages sqlite3
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds install -p packages curl
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds install -p packages libmicrohttpd
    COMMAND ${CMAKE_BINARY_DIR}/openwrt/scripts/feeds install -p packages libjson
    COMMAND echo "CONFIG_PACKAGE_libsml=y" >> .config
    COMMAND touch  ${CMAKE_BINARY_DIR}/feeds.done
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/openwrt
    COMMENT "Update feeds"
    DEPENDS ${CMAKE_BINARY_DIR}/package.done
    )
  add_custom_target(openwrt_feeds DEPENDS ${CMAKE_BINARY_DIR}/feeds.done)
  configure_file(dot.config_${DEST_TARGET} ${CMAKE_BINARY_DIR}/openwrt/.config)
  file(APPEND ${CMAKE_BINARY_DIR}/openwrt/.config
    "CONFIG_PACKAGE_libboost=m
CONFIG_PACKAGE_libcurl=m
CONFIG_PACKAGE_libsml=m
CONFIG_PACKAGE_libmicrohttpd=m
CONFIG_PACKAGE_libsqlite3=m
CONFIG_PACKAGE_libuuid=y
CONFIG_PACKAGE_libopenssl=y

CONFIG_PACKAGE_boost-chrono=m
CONFIG_PACKAGE_boost-date_time=m
CONFIG_PACKAGE_boost-filesystem=m
CONFIG_PACKAGE_boost-graph=m
CONFIG_PACKAGE_boost-iostreams=m
CONFIG_PACKAGE_boost-locale=m
CONFIG_PACKAGE_boost-math=m
CONFIG_PACKAGE_boost-program_options=m
CONFIG_PACKAGE_boost-random=m
CONFIG_PACKAGE_boost-regex=m
CONFIG_PACKAGE_boost-serialization=m
CONFIG_PACKAGE_boost-signals=m
CONFIG_PACKAGE_boost-system=m
CONFIG_PACKAGE_boost-test=m
CONFIG_PACKAGE_boost-thread=m
CONFIG_PACKAGE_boost-timer=m
CONFIG_PACKAGE_boost-wave=m

CONFIG_BUSYBOX_CONFIG_STTY=y
CONFIG_BUSYBOX_CONFIG_MODPROBE=y

CONFIG_PACKAGE_kmod-usb-serial=y
CONFIG_PACKAGE_kmod-usb-serial-airprime=y
CONFIG_PACKAGE_kmod-usb-serial-ark3116=y
CONFIG_PACKAGE_kmod-usb-serial-belkin=y
CONFIG_PACKAGE_kmod-usb-serial-ch341=y
CONFIG_PACKAGE_kmod-usb-serial-cp210x=y
CONFIG_PACKAGE_kmod-usb-serial-cypress-m8=y
CONFIG_PACKAGE_kmod-usb-serial-ftdi=y
CONFIG_PACKAGE_kmod-usb-serial-keyspan=y
CONFIG_PACKAGE_kmod-usb-serial-mct=y
CONFIG_PACKAGE_kmod-usb-serial-motorola-phone=y
CONFIG_PACKAGE_kmod-usb-serial-option=y
CONFIG_PACKAGE_kmod-usb-serial-oti6858=y
CONFIG_PACKAGE_kmod-usb-serial-pl2303=y
CONFIG_PACKAGE_kmod-usb-serial-sierrawireless=y
CONFIG_PACKAGE_kmod-usb-serial-visor=y
CONFIG_PACKAGE_kmod-usb-storage=m
")

endfunction(openwrt_configure)

macro(openwrt_env)
  openwrt_checkout()
  openwrt_configure()
  
endmacro(openwrt_env)
