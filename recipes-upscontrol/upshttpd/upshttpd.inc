SUMMARY = "HTML for UPS and PDU Controller"
HOMEPAGE = "http://www.robosity.com"
SECTION = "upscontrol"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://extra/COPYING;md5=441c28d2cf86e15a37fa47e15a72fbac"
PR = "r1"
REPO_NAME = "UpsHttpd"
BRANCH ?= ""
SRCREV ?= "${AUTOREV}"

S = "${WORKDIR}/git"

WWW_PAGES = "/www/pages"
WWW_APPS = "/www/apps"

SRC_URI = " \
    git://git@github.com/aerodesic/${REPO_NAME};protocol=ssh;branch=main    \
"

DEPENDS = "\
    openssl-native                      \
"

RDEPENDS_${PN} += "\
    lighttpd                            \
    lighttpd-module-rewrite             \
    lighttpd-module-alias               \
    lighttpd-module-auth                \
    lighttpd-module-fastcgi             \
    lighttpd-module-cgi                 \
    lighttpd-module-compress            \
    lighttpd-module-ssi                 \
    lighttpd-module-accesslog           \
    lighttpd-module-authn-file          \
    lighttpd-module-openssl             \
    lighttpd-module-redirect            \
    python3-requests                    \
    python3-flask                       \
    python3-flask-restful               \
    python3-flask-login                 \
    python3-flask-uploads               \
    python3-waitress                    \
    python3-flup                        \
    python3-pytz                        \
    python3-aniso8601                   \
    python3-core				\
"

do_install_append() {
    # Generate server key good for 100 years.
    install -m 755 -d ${D}${sysconfdir}/lighttpd/ssl/upscontrol.local
    openssl req -new -x509  \
            -keyout ${D}${sysconfdir}/lighttpd/ssl/upscontrol.local/upscontrol.pem \
            -out ${D}${sysconfdir}/lighttpd/ssl/upscontrol.local/upscontrol.pem \
            -days 36500 \
            -nodes <<EOF
US
Oregon
Corvallis
Robosity
UPS and PDU Control
www.robosity.com
go@robosity.com
EOF

    install -m 755 -d ${D}${sysconfdir}/lighttpd.d/
    install -m 644 ${S}/conf/upshttpd.conf ${D}${sysconfdir}/lighttpd.d

    install -m 755 -d ${D}${WWW_PAGES}/static
    install -m 644 ${S}/js/* ${D}${WWW_PAGES}/static/
    install -m 644 ${S}/css/* ${D}${WWW_PAGES}/static/
    install -m 644 ${S}/images/* ${D}${WWW_PAGES}/static/

    install -m 755 -d ${D}${WWW_APPS}/templates
    install -m 644 ${S}/html/* ${D}${WWW_APPS}/templates

    install -m 644 ${S}/fcgi/* ${S}/extra/*.py ${D}${WWW_APPS}
    chmod +x ${D}${WWW_APPS}/*.fcgi
    # Protect the secret key file
    chmod 600 ${D}${WWW_APPS}/secret_key.py
}

FILES_${PN} = "${sysconfdir} ${sysconfdir}/lighttpd/ssl/upshttpd.local ${sysconfdir}/lighttpd.d ${WWW_PAGES} ${WWW_APPS}"

