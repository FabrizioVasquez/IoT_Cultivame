import paho.mqtt.client as mqttClient
import csv
import time

# global
x_axis = 0
fieldnames_ = ['times','humidity','temperature']

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to broker")
        global Connected                #Use global variable
        Connected = True                #Signal connection 
    else:
        print("Connection failed")



def on_message(client, userdata, message):    
    #print("Message received: "  + message.payload.decode('utf-8'))
    global x_axis
    with open('info.csv',"a", newline='') as file:
        csv_writer = csv.DictWriter(file,fieldnames = fieldnames_) #RMP
        # file.write(str(message.payload.decode('utf-8'))+"\n")
        vars = str(message.payload.decode('utf-8'))
        list_vars = vars.split(',')

        rows = {
            "times": x_axis,
            "humidity": list_vars[0],
            "temperature": list_vars[1]
        }

        csv_writer.writerow(rows)
        print(x_axis,list_vars)

        x_axis +=1
        
    time.sleep(1)
  
Connected = False   #global variable for the state of the connection
  
broker_address= "192.168.171.2"     #Broker address
port = 1883                         #Broker port
user = "HUAWEIP10lite"                    #Connection username
password = "9261566b39f3"            #Connection password
  
with open('info.csv',"w",newline='') as file:
    csv_writer = csv.DictWriter(file,fieldnames = fieldnames_)
    csv_writer.writeheader()
    file.close()

client = mqttClient.Client("Python")               #create new instance
client.username_pw_set(user, password=password)    #set username and password
client.on_connect= on_connect                      #attach function to callback
client.on_message= on_message                      #attach function to callback
  
client.connect(broker_address, port=port)          #connect to broker
  
client.loop_start()        #start the loop
  
while Connected != True:    #Wait for connection
    time.sleep(0.1)
  
client.subscribe("test/topic")
  
try:
    while True:
        time.sleep(1)
  
except KeyboardInterrupt:
    print("exiting")
    client.disconnect()
    client.loop_stop()