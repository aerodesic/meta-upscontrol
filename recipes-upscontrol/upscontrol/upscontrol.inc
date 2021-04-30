SUMMARY = "Control application for UPS and PDU"
HOMEPAGE = "http://www.robosity.com"
SECTION = "upscontrol"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://extra/COPYING;md5=441c28d2cf86e15a37fa47e15a72fbac"
PR = "r1"
REPO_NAME = "UpsControl"
BRANCH ?= ""
SRCREV ?= "${AUTOREV}"

inherit pypi distutils3 setuptools3 systemd

DEPENDS = " \
    python3-distutils-extra-native      \
    intltool-native                     \
    python3-dbus                        \
    python3-pygobject                   \
    python3-spidev                      \
    python3-extra-utils                 \
"

RDEPENDS_${PN} += " \
    python3-core                        \
    python3-threading                   \
    python3-pygobject                   \
    python3-spidev                      \
    python3-dbus                        \
    python3-rpi-gpio                    \
    python3-systemd                     \
    python3-extra-utils                 \
    bash                                \
"

S = "${WORKDIR}/git"

SRC_URI = " \
    git://git@github.com/aerodesic/${REPO_NAME};protocol=ssh;branch=main        \
    file://${BPN}.conf                                                          \
    file://${BPN}.service                                                       \
"

SYSTEMD_SERVICE_${PN} = "${PN}.service"

do_install_append() {
    echo "${PN}" > ${D}${PYTHON_SITEPACKAGES_DIR}/${PN}-${PV}.pth

    chmod +x ${D}${sbindir}/${PN}

    install -m 755 -d ${D}${sysconfdir}/dbus-1/system.d
    install -m 644 ${WORKDIR}/${PN}.conf ${D}${sysconfdir}/dbus-1/system.d
    install -m 755 -d ${D}${datadir}/dbus-1/system.d
    install -m 644 ${WORKDIR}/${PN}.conf ${D}${datadir}/dbus-1/system.d

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/${PN}.service ${D}${systemd_unitdir}/system

    install -m 755 -d ${D}/home/upscontrol/
}

FILES_${PN} = "${libdir} ${sbindir} ${sysconfdir} ${datadir} ${systemd_unitdir} /home/upscontrol"

SYSTEMD_AUTO_ENABLE_${PN} = "enable"

