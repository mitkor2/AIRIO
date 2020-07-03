import json
import logging
import datetime

from django.http import HttpResponse
from django.shortcuts import render
from Airio.database.airio.models import *

def receive_data(request):
    try:
        obj = tbl_airio_data()
        data = json.loads(request.POST['data'])['data']
        obj.timestamp = data['timestamp']
        obj.temperature = data['temperature']
        obj.humidity = data['humidity']
        obj.pressure = data['pressure']
        obj.ozone = data['ozone']
        obj.carbonMonoxide = data['carbonMonoxide']
        obj.sulfurDioxide = data['sulfurDioxide']
        obj.nitrogenDioxide = data['nitrogenDioxide']
        obj.pm1_0 = data['pm1_0']
        obj.pm2_5 = data['pm2_5']
        obj.pm4_0 = data['pm4_0']
        obj.pm10 = data['pm10']
        obj.airq = data['airq']
        obj.vbatt = data['vbatt']
        obj.cbatt = data['cbatt']
        obj.fixQuality = data['fixQuality']
        obj.latitude = data['latitude']
        obj.longitude = data['longitude']
        obj.altitude = data['altitude']

        obj.save()

        return HttpResponse('success')

    except Exception as e:
        logging.error(str(e))
        return HttpResponse(str(e), status=500)