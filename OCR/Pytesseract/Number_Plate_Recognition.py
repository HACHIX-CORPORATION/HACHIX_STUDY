import cv2
import pytesseract

img = cv2.imread("./kia-seltos-car-number-plate-designs.jpeg")

# Detect Number Plate
number_plate_cascade = cv2.CascadeClassifier("haarcascade_russian_plate_number.xml")

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
number_plate_segment = number_plate_cascade.detectMultiScale(gray)

# Recognize the Number Plate
pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"

for x,y,w,h in number_plate_segment:
    segment = gray[y:y+h, x:x+w]
    text = pytesseract.image_to_string(segment, config = r'--psm 6')
    print(text)
    cv2.rectangle(img, (x,y), (x+w,y+h), (255,0,0),2)
    cv2.putText(img, text.strip(), (x,y-30), cv2.FONT_HERSHEY_COMPLEX, 1.5, (0,0,255),3)
    cv2.imshow('a', img)
    cv2.waitKey(0)