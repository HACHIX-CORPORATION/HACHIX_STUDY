import cv2
import pytesseract
import numpy as np
from imutils.object_detection import non_max_suppression


img = cv2.imread('D:/downloads/OCR_LNP.PNG')

## -------------  Load the pre-trained models ---------------
model = cv2.dnn.readNet('D:/downloads/frozen_east_text_detection.pb')

## -------------  Prepare the image  ----------------
# use multiple of 32 to set the new img shape
height, width, _ = img.shape
new_height = (height//32)*32
new_width = (width//32)*32
print(new_height, new_width)

# get the ratio change in width and height
h_ratio = height/new_height
w_ratio = width/new_width
print(h_ratio, w_ratio)

blob = cv2.dnn.blobFromImage(img, 1, (new_width, new_height),(123.68, 116.78, 103.94), True, False)

## -------------  Forward Propagation  -------------
model.setInput(blob)
(geometry, scores) = model.forward(model.getUnconnectedOutLayersNames())


## -------------   Post-Processing  ----------------
rectangles = []
confidence_score = []
for i in range(geometry.shape[2]):
    for j in range(0, geometry.shape[3]):
        
        if scores[0][0][i][j] < 0.1:
            continue
            
        bottom_x = int(j*4 + geometry[0][1][i][j])
        bottom_y = int(i*4 + geometry[0][2][i][j])
        

        top_x = int(j*4 - geometry[0][3][i][j])
        top_y = int(i*4 - geometry[0][0][i][j])
        
        rectangles.append((top_x, top_y, bottom_x, bottom_y))
        confidence_score.append(float(scores[0][0][i][j]))
		
		
# use Non-max suppression to get the required rectangles
fin_boxes = non_max_suppression(np.array(rectangles), probs=confidence_score, overlapThresh=0.5)


## --------------- Tell Pytesseract the path of Tesseract.exe -------------
pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'


## ---------------  Recognize the text using Pytesseract in each segment -----------
img_copy = img.copy()
for (x1, y1, x2, y2) in fin_boxes:

    x1 = int(x1 * w_ratio)
    y1 = int(y1 * h_ratio)
    x2 = int(x2 * w_ratio)
    y2 = int(y2 * h_ratio)
    
    segment = img[y1:y2+4, x1:x2+2, :]
    
    segment_gray = cv2.cvtColor(segment, cv2.COLOR_BGR2GRAY)
    ret, thresh = cv2.threshold(segment_gray, 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)

    text = pytesseract.image_to_string(thresh, config=r"--psm 8")

    cv2.rectangle(img_copy, (x1, y1), (x2, y2), (0, 255, 0), 2)
    cv2.putText(img_copy, text.strip(), (x1,y1-2), cv2.FONT_HERSHEY_COMPLEX, 0.7, (0,0,255),2)

cv2.imshow("Text Detection", img_copy)
cv2.waitKey(0)

