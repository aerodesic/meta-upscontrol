#
# Add a an eth1 for USB access.
#
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=441c28d2cf86e15a37fa47e15a72fbac"

inherit systemd

SYSTEMD_SERVICE_${PN} = "${PN}.service"
SYSTEMD_AUTO_ENABLE_${PN} = "enable"

RDEPENDS_${PN} += " bash"

S = "${WORKDIR}"

SRC_URI += " \
	file://${BPN}-setup.sh		\
	file://COPYING			\
	file://${BPN}.service		\
"

do_install_append() {
    install -d -m 0755 ${D}${sbindir}
    install -m 0755 ${WORKDIR}/${PN}-setup.sh ${D}${sbindir}
    chmod +x ${D}${sbindir}/${PN}-setup.sh

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/${PN}.service ${D}${systemd_unitdir}/system

    # Fix up symbolic directories in files
    for file in ${D}${systemd_unitdir}/system/${PN}.service ${D}${sbindir}/${PN}-setup.sh; do 
        sed -i -e 's#@SYSCONFDIR@#${sysconfdir}#g' ${file}
        sed -i -e 's#@SBINDIR@#${sbindir}#g' ${file}
        sed -i -e 's#@BINDIR@#${bindir}#g' ${file}
	sed -i -e 's#@USB_ETHERNET_CONNECTIONS@#${USB_ETHERNET_CONNECTIONS}#g' ${file}
    done
}

FILES_${PN} += "${sysconfdir} ${sbindir} ${bindir}"
