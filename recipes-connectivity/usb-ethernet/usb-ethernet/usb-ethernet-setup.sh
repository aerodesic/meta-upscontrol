#!/bin/bash
# Iterate over the parameters and build connection names
p=1
while [ "$p" -le "$#" ]; do
  eval "CONNECTION_NAME=\${$p}"
  p=$((p + 1))
  eval "CONNECTION_DEVICE=\${$p}"
  p=$((p + 1))
  eval "CONNECTION_IP=\${$p}"
  p=$((p + 1))
  if [ ! -e /etc/NetworkManager/system-connections/$CONNECTION_NAME.nmconnection ]; then
    nmcli con add con-name "$CONNECTION_NAME" type ethernet ifname $CONNECTION_DEVICE autoconnect yes save yes
    nmcli con modify "$CONNECTION_NAME" ipv4.method shared ipv4.addr "$CONNECTION_IP"
  fi
done
