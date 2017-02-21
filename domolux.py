#!/usr/bin/python3

import tsl2561 as ts

import base64
import sys
import json

import urllib.request as urllib2

targetIDX = "154"

domoticzserver = "zwave:8080"
domoticzusername = ""
domoticzpassword = ""
awayDeviceName = "Away"
base64string = base64.encodestring(bytes(('%s:%s' % (domoticzusername, domoticzpassword)).replace('\n', ''), 'utf-8'))


def DomoticzRequest(params):
    url = "http://{0}/json.htm?{1}".format(domoticzserver, params)

    # print (url)

    request = urllib2.Request(url)
    request.add_header("Authorization", "Basic %s" % base64string)
    try:
        response = urllib2.urlopen(request)
        return json.loads(response.read().decode('utf-8'))

    except urllib2.URLError:
        print ("Error - Couldn't open URL")
        return None



if __name__ == '__main__':
    param = "type=command&param=udevice&idx={0}&svalue={1}".format(targetIDX, str(ts.lux()))
    DomoticzRequest(param)
