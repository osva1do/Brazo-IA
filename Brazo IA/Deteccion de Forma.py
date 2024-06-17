import cv2
import serial, time

ard = serial.Serial('COM3', 9600)
cap = cv2.VideoCapture(0)

def getContours(img):
    contours, Hierarchy = cv2.findContours(img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    for cnt in contours:
        area = cv2.contourArea(cnt)

        if area > 500:
            cv2.drawContours(frame, cnt, -1, (255, 0, 0), 3)
            perimeter = cv2.arcLength(cnt, True)
            aprox = cv2.approxPolyDP(cnt, 0.02 * perimeter, True)
            objCorner = len(aprox)
            x, y, w, h = cv2.boundingRect(aprox)

            if objCorner == 3:
                objectType = "TRIANGULO"
                com = "T"
                ard.write(com.encode())
                time.sleep(5)

            elif objCorner == 4:
                objectType = "RECTANGULO"
                com = "R"
                ard.write(com.encode())
                time.sleep(5)

            elif objCorner > 4:
                objectType = "CIRCULO"
                com = "C"
                ard.write(com.encode())
                time.sleep(5)
                
            else:
                objectType = "NONE"
                com = "D"
                ard.write(com.encode())
                time.sleep(5)

            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
            cv2.putText(frame, objectType, (x + (w//2)-10, y + (h//2) - 10), cv2.FONT_HERSHEY_COMPLEX, 0.7, (0, 0, 0))


while True:
    ret, frame = cap.read()
    imgGray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    imgBlur = cv2.GaussianBlur(imgGray, (7, 7), 1)
    imgCanny = cv2.Canny(imgBlur, 50, 50)
    getContours(imgCanny)

    cv2.imshow('Deteccion de figuras', frame)

    if cv2.waitKey(1) == 9:
        com = "D"
        ard.write(com.encode())
        time.sleep(1)

    if cv2.waitKey(1) == 27:
        break