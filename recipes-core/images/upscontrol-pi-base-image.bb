SUMMARY = "Basic upscontroller test control image"

include core-image-base.bb

# Remove POE from overlays
RPI_KERNEL_DEVICETREE_OVERLAYS_remove += " overlays/rpi-poe.dtbo"

IMAGE_FEATURES += "splash package-management ssh-server-dropbear hwcodecs"

IMAGE_INSTALL_append += " framebuffer-hdmi"
IMAGE_INSTALL_append += " linux-firmware"
IMAGE_INSTALL_append += " sudo"
IMAGE_INSTALL_append += " i2c-tools"
IMAGE_INSTALL_append += " python3-smbus"
IMAGE_INSTALL_append += " bridge-utils"
IMAGE_INSTALL_append += " hostapd"
IMAGE_INSTALL_append += " dnsmasq"
IMAGE_INSTALL_append += " iptables"
IMAGE_INSTALL_append += " wpa-supplicant"
IMAGE_INSTALL_append += " dhcpcd"
IMAGE_INSTALL_append += " ifupdown iproute2 net-tools"
IMAGE_INSTALL_append += " rootresizer"
IMAGE_INSTALL_append += " net-snmp"
# # Extra for debug
IMAGE_INSTALL_append += " procps"
IMAGE_INSTALL_append += " tcpdump"
# # END DEBUG

# The goods
IMAGE_INSTALL_append += " upsdisplay upscontrol upshttpd"

HOSTNAME = "ups"

LICENSE = "MIT"

# Disable uart
ENABLE_UART = "0"

inherit core-image features_check update-management

# DISABLE_V4GRAPHICS = "1"
REQUIRED_DISTRO_FEATURES = "wayland"
CORE_IMAGE_EXTRA_INSTALL += "weston weston-xwayland weston-init weston-examples gtk+3-demo clutter-1.0-examples sudo"
CORE_IMAGE_EXTRA_INSTALL += "${@bb.utils.contains('DISTRO_FEATURES', 'x11', 'matchbox-terminal', '', d)}"

