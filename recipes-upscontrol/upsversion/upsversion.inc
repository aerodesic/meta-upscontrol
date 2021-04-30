SUMMARY = "Version identifier for UPS and PDU software."
HOMEPAGE = "http://www.robosity.com"
SECTION = "upscontrol"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=441c28d2cf86e15a37fa47e15a72fbac"

do_install_append() {
	# Install the /etc/systemversion file
	install -m 755 -d ${D}${sysconfdir}
	echo ${PV} > ${D}${sysconfdir}/systemversion
}

RDEPENDS_${PN} = "upscontrol upsdisplay upshttpd"

FILES_${PN} = "${sysconfdir}"

