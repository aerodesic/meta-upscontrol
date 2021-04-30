FILESEXTRAPATHS_prepend := "${THISDIR}/upscontrol:"

SUMMARY = "Display application for UPS and PDU control"
HOMEPAGE = "http://www.robosity.com"
SECTION = "upscontrol"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://extra/COPYING;md5=441c28d2cf86e15a37fa47e15a72fbac"
PR = "r1"
REPO_NAME = "UpsDisplay"
BRANCH ?= ""
SRCREV ?= "${AUTOREV}"

inherit pypi distutils3 setuptools3 systemd

DEPENDS = " \
    intltool-native                     \
    python3-distutils-extra-native      \
    python3-dbus                        \
    python3-pygobject                   \
    python3-spidev                      \
    python3-extra-utils                 \
    python3-numpy                       \
    python3-wxpython                    \
    python3-networkmanager              \
"

RDEPENDS_${PN} += " \
    python3-core                        \
    python3-numpy                       \
    python3-wxpython                    \
    python3-threading                   \
    python3-pygobject                   \
    python3-spidev                      \
    python3-dbus                        \
    python3-rpi-gpio                    \
    python3-systemd                     \
    python3-extra-utils                 \
    python3-networkmanager              \
    bash                                \
    gnupg                               \
"

S = "${WORKDIR}/git"

SRC_URI = " \
    git://git@github.com/aerodesic/${REPO_NAME};protocol=ssh;branch=main     \
    file://${BPN}.service                                                    \
"

SYSTEMD_SERVICE_${PN} = "${PN}.service"

do_install_append() {
    echo "${PN}" > ${D}${PYTHON_SITEPACKAGES_DIR}/${PN}-${PV}.pth

    chmod +x ${D}${bindir}/${PN}

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/${PN}.service ${D}${systemd_unitdir}/system

    install -m 755 -d ${D}/home/upscontrol/
}

# Has a password
def hash_default_password(pw):
    if len(pw) != 0:
        import crypt
        pw=crypt.crypt(pw)

    # Return escaping any $ characters to allow passage through shell
    return pw.replace('$', '\\$')

# Conditionally assign GENTEST_CRYPT_PASSWORD only if GENTEST_PASSWORD is defined
GENTEST_CRYPT_PASSWORD := "${@hash_default_password('${GENTEST_PASSWORD}')}"

FILES_${PN} = "${libdir} ${bindir} ${sysconfdir} ${datadir} ${systemd_unitdir} /home/upscontrol"

SYSTEMD_AUTO_ENABLE_${PN} = "enable"

