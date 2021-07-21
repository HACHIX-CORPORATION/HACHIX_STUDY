import cv2
import pytesseract

img = cv2.imread('aadhar_demo2.jpg')

pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"

text = pytesseract.image_to_string(img, config = r'--psm 3', lang = 'eng')

print(text)


with open('structured_output.txt', mode = 'w') as f:
    f.write(text)

extracted_data = {}


with open('structured_output.txt', 'r') as text_file:
    line_lst = text_file.readlines()


for line in line_lst:
    line_strip = line.strip()
    if 'Name' in line_strip:
        extracted_data['Name'] = " ".join(line_strip.split()[1:])
    if 'DOB' in line_strip:
        extracted_data['Date of Birth'] = line_strip.split()[-1]

print(extracted_data)





