from itertools import count
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

plt.style.use('fivethirtyeight')

index = count()

def animate(i):
    data = pd.read_csv('info.csv')
    x = data['times']
    humidity = data['h']
    temperature = data['bmptemp']
    temperaturedht = data['t']
    pressure = data['bmpprea']
    altitude = data['bmpalti']
    uvvalue = data['uvValue']
    is_rain = data['rainvalue']
    co2value = data['co2value']

    plt.cla()
    plt.plot(x, humidity, label='Humedad')
    plt.plot(x, temperature, label='Temperatura')
    plt.plot(x, temperaturedht, label='Temperatura (DHT)')
    #plt.plot(x, pressure, label='Presión Atmosférica')
    plt.plot(x, altitude, label='Altitud')
    plt.plot(x, uvvalue, label='UV')
    plt.plot(x, is_rain, label='Lluvia?')
    plt.plot(x, co2value, label='CO2')

    plt.legend(loc='upper left')
    plt.tight_layout()


ani = FuncAnimation(plt.gcf(), animate, interval=1000)

plt.tight_layout()
plt.show()