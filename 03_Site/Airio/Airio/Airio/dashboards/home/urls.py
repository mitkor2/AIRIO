from django.urls import path, re_path

from . import views

urlpatterns = [
    path('', views.home_view, name='home_view'),
    path('get_latest_data', views.get_latest_data, name='get_latest_data')
]