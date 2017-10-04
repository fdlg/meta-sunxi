DESCRIPTION = "ARM Trusted Firmware"

LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://license.md;md5=829bdeb34c1d9044f393d5a16c068371"

PROVIDES = "virtual/arm-trusted-firmware"

inherit deploy

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

BRANCH = "allwinner"
SRC_URI = "git://github.com/apritzel/arm-trusted-firmware.git;protocol=http;branch=${BRANCH}"

COMPATIBLE_MACHINE = "sun50i"
PLATFORM_sun50i = "sun50iw1p1"

# requires CROSS_COMPILE set by hand as there is no configure script
export CROSS_COMPILE="${TARGET_PREFIX}"

# Let the Makefile handle setting up the CFLAGS and LDFLAGS as it is a standalone application
CFLAGS[unexport] = "1"
LDFLAGS[unexport] = "1"
AS[unexport] = "1"
LD[unexport] = "1"

do_configure() {
	:
}

do_compile() {
	oe_runmake -C ${S} BUILD_BASE=${B} PLAT=${PLATFORM} DEBUG=1 bl31
}

do_install() {
	:
}

OUTPUT_DIR = "${B}/${PLATFORM}/debug"

do_deploy() {
	install -d ${DEPLOYDIR}
	install -m 0644 ${OUTPUT_DIR}/bl31/bl31.elf ${DEPLOYDIR}/bl31-${MACHINE}.elf
	install -m 0644 ${OUTPUT_DIR}/bl31.bin ${DEPLOYDIR}/bl31-${MACHINE}.bin
}
addtask deploy before do_build after do_compile
