impo;rt cv2
import numpy as np
import os
from PIL import Image
import serial
from time import sleep

#Khởi tạo đường dẫn ứng với Serial của Arduino
ser = serial.Serial('/dev/ttyACM0',9600)

recognizer = cv2.face.LBPHFaceRecognizer_create();
recognizer.read('/home/pi/Face-Recognition-Train-YML-Python-master/recognizer/trainningData.yml')
cascadePath = "/home/pi/Face-Recognition-Train-YML-Python-master/haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascadePath);

font = cv2.FONT_HERSHEY_SIMPLEX

#iniciate id counter
id = 0

# names related to ids: example ==> KUNAL: id=1,  etc
names = ['None', 'Phap','Phat']

#Điều kiện để bắt đầu truyền tín hiệu sang Arduino
face = 0

# Initialize and start realtime video capture
cam = cv2.VideoCapture(0)
cam.set(3, 320) # set video widht
cam.set(4, 240) # set video height

# Define min window size to be recognized as a face
minW = 0.1*cam.get(3)
minH = 0.1*cam.get(4)

while True:
    ret, img =cam.read()
    #img = cv2.flip(img, -1) # Flip vertically
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor = 1.2,
        minNeighbors = 5,
        minSize = (int(minW), int(minH)),
       )

    for(x,y,w,h) in faces:
        cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0), 2)
        id, confidence = recognizer.predict(gray[y:y+h,x:x+w])

        # Check if confidence is less them 100 ==> "0" is perfect match
        if (confidence < 100 ):
            conf = round(100 - confidence)
            print(type(conf))
            if(conf > 30):
                id = names[id]
                confidence = "  {0}%".format(round(100 - confidence))
                cv2.putText(img, str(id), (x+5,y-5), font, 1, (255,255,255), 2)
                cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)
                #print(type(confidence))
                
                #đặt điều kiện để chống nhiễu
                face=6
               
            else:
                id = "unknown"
                confidence = "  {0}%".format(round(100 - confidence))
                cv2.putText(img, str(id), (x+5,y-5), font, 1, (0,0,255), 2)
                cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)
        #truyền tín hiệu sang Arduino  
        if(face==6):
            try:
                while(True):
                    face=0
                    #Chuỗi truyền qua
                    string = 'Open'
                    ser.write(string.encode())
                    #in ra để test xem có truyền được chuỗi qua ko 
                    print('open')            
                    sleep(2)
                    string = ''
                    ser.write(string.encode())
                    
                    
                    #Đóng cổng serial lại thì ko bị đơ cam
                    ser.close()
                    
                    #ser.resume()
            except:
                   print('close')
                   
           
    cv2.imshow('camera',img)

    k = cv2.waitKey(10) & 0xff # Press 'ESC' for exiting video
    if k == 27:
        break


                    
# Do a bit of cleanup
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv2.destroyAllWindows()
