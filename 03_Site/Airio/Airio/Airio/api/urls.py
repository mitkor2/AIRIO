from django.urls import path, re_path

from . import views

urlpatterns = [
    path('receive_data', views.receive_data, name='receive_data'),
]