from itertools import count
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

plt.style.use('fivethirtyeight')

index = count()

def animate(i):
    data = pd.read_csv('info.csv')
    x = data['times']
    temperature = data['temperature']

    plt.cla()
    plt.plot(x, temperature, label='Temperatura')

    plt.legend(loc='upper left')
    plt.tight_layout()


ani = FuncAnimation(plt.gcf(), animate, interval=1000)

plt.tight_layout()
plt.show()