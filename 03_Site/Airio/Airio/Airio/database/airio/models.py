from django.db import models

class tbl_airio_data(models.Model):
    timestamp = models.BigIntegerField()
    temperature = models.FloatField()
    humidity = models.FloatField()
    pressure = models.FloatField()
    ozone = models.IntegerField()
    carbonMonoxide = models.IntegerField()
    sulfurDioxide = models.IntegerField()
    nitrogenDioxide = models.IntegerField()
    pm1_0 = models.IntegerField()
    pm2_5 = models.IntegerField()
    pm4_0 = models.IntegerField()
    pm10 = models.IntegerField()
    airq = models.IntegerField()
    vbatt = models.IntegerField()
    cbatt = models.IntegerField()
    fixQuality = models.IntegerField()
    latitude = models.FloatField()
    longitude = models.FloatField()
    altitude = models.IntegerField()
