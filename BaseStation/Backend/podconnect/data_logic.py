from django.shortcuts import render
from . import models, tcpserver, udpserver, stats_helper
from django.http import HttpResponse, HttpRequest, JsonResponse
from django.core.serializers import serialize
import pickle
import struct

from threading import Lock
import json

def state(request):
    state_data = models.State.objects.latest("date_time")
    toReturn = state_data.state
    return HttpResponse(toReturn)

def stats(request):
    toReturn = stats_helper.getStats()
    return JsonResponse(toReturn, safe=False)

def battery(request):
    can_data = models.CANData.objects.latest("date_time")
    toReturn = {
        "value": can_data.pack_soc
    }
    print(can_data.pack_soc)
    return JsonResponse(toReturn)

def position(request):
    motion_data = models.MotionData.objects.latest("date_time")
    toReturn = {
        "currentDistance":motion_data.position,
        "totalDistance":1200
    }
    return JsonResponse(toReturn)

def stopPressed(request):
    if request.method == "POST":
        print("STOPPING")
        return HttpResponse()

def readyPressed(request):
    if request.method == "POST":
        print("Ready!")
        return HttpResponse()
