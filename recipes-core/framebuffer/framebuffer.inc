MAINTAINER = "Gary Oliver <go@ao-cs.com>"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=441c28d2cf86e15a37fa47e15a72fbac"

inherit systemd

RPROVIDES_${PN} += "framebuffer"

RDEPENDS_${PN} = " 	\
    bash            	\
"

S = "${WORKDIR}"

SRC_URI = " \
    file://framebuffer.service 	\
    file://find_framebuffer	\
    file://COPYING 		\
"

do_install() {
    install -d ${D}${sbindir}
    install -m 0755 ${S}/find_framebuffer ${D}${sbindir}
    install -d ${D}${systemd_unitdir}/system/
    install -m 0644 ${S}/framebuffer.service ${D}${systemd_unitdir}/system/
}

SYSTEMD_SERVICE_${PN} = "framebuffer.service"

FILES_${PN} += "${systemd_unitdir}/system/* ${sbindir}"
