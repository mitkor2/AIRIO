import json
from django.http import HttpResponse
from django.shortcuts import render
from Airio.database.airio.models import *

def home_view(request, template_name='home/test1.html'):
    # the blow is to use django orm, to read data from db
    data_list = list(tbl_airio_data.objects.all().values())

    avg_pm1_0 = 0
    for data in data_list:
        avg_pm1_0 += data['pm1_0']

    avg_pm1_0 = avg_pm1_0 / len(data_list)

    data = {
        'data_list': data_list,
        'avg_pm1_0': avg_pm1_0
    }
    return render(request, template_name, data)


def get_latest_data(request):
    try:
        data = list(tbl_airio_data.objects.all().order_by('-id').values())[0]
        return HttpResponse(json.dumps(data), status=200)
    except Exception as e:
        return HttpResponse('error', status=500)