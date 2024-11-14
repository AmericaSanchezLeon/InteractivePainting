import cv2 as cv
import numpy as np
import imutils
import serial, time

#camara = cv.VideoCapture('http://10.5.5.9:8080/live/amba.m3u8')
camara = cv.VideoCapture(0)
if(camara.isOpened() == False): 
  print("Error abriendo el video")

lower = {'Pimiento':(0,60,105), 'Limon':(42,55,75),'Chile manzano':(15,40,120), 'Cebolla':(140,40,65), 'Manzana amarilla':(20,59,119), 'Palita azul':(97, 100, 117)}
upper = {'Pimiento':(5,255,255), 'Limon':(80,255,255),'Chile manzano':(18,255,255), 'Cebolla':(200,255,255),  'Manzana amarilla':(35,255,255), 'Palita azul':(117,255,255) }

colors = {'Pimiento':(0,0,255), 'Limon':(0,255,0), 'Chile manzano':(0, 149, 255), 'Cebolla':(179,0,184), 'Manzana amarilla':(79,241,255),'Palita azul':(255,0,0)}

arduino = serial.Serial("/dev/cu.usbmodem14201", 9600)


def detecta_color(hsv, lower, upper):
    color = ''

    for key, value in upper.items():
        #Crear una transformación morfologica para remover bordes
        kernel = np.ones((9,9),np.uint8)
        mask = cv.inRange(hsv, lower[key], upper[key])
        mask = cv.morphologyEx(mask, cv.MORPH_OPEN, kernel)
        mask = cv.morphologyEx(mask, cv.MORPH_CLOSE, kernel)

        #Encuentra los contornos y los dibuja en un circulo
        cnts = cv.findContours(mask.copy(), cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)[-2]
        #center = None

        #Si se encontraron contornos los procesa
        if len(cnts) > 0:
            #Determinar el contorno maximo para calcular el minimo de un circulo que sera dibujado
            color = key
            #c = max(cnts, key=cv.contourArea)
            #((x, y), radius) = cv.minEnclosingCircle(c)
            #M = cv.moments(c)
            #center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
            #Si el radio esta dentro del tamaño minimo
            #if radius > 0.2:
                #Dibuja el circulo y el punto (centroide) en el frame y actualiza los puntos
                #cv.circle(frame, (int(x), int(y)), int(radius), colors[key], 2)
                #cv.putText(frame,key, (int(x-radius),int(y-radius)), cv.FONT_HERSHEY_SIMPLEX, 0.6,colors[key],2)
    return color

while(camara.isOpened()):
    #Obtener el frame
    _, frame = camara.read()
    #r,h,c,w = 250,90,400,125 
    #roi = frame[r:r+h, c:c+w]
    #hsv_roi = cv.cvtColor(frame, cv.COLOR_BGR2HSV)

    frame = imutils.resize(frame, width=600)
    #Convertir BGR to HSV
    blurred = cv.GaussianBlur(frame, (11, 11), 0)
    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)

    obj = detecta_color(hsv, lower, upper)
    print(obj)
    
    if(obj == 'Pimiento'):
        time.sleep(2)
        arduino.write(b'1')
    elif(obj == 'Limon'):
        time.sleep(2)
        arduino.write(b'2')
    elif(obj == 'Manzana amarilla'):
        time.sleep(2)
        arduino.write(b'3')
    elif(obj == 'Cebolla'):
        time.sleep(2)
        arduino.write(b'4')
    elif(obj == 'Chile manzano'):
        time.sleep(2)
        arduino.write(b'5')
    elif(obj == 'Palita azul'):
        time.sleep(2)
        arduino.write(b'6')
    else:
        time.sleep(2)
        arduino.write(b'0')

    #Muestra el frame
    cv.imshow('Detectar Color',frame)

    #Para salir presiona 'q'
    key = cv.waitKey(1) & 0xFF
    if key == ord("q"):
        break

arduino.close()
camara.release()
cv.destroyAllWindows()