# import the necessary packages
import numpy as np
import argparse
import cv2
import os
import shutil
import stat

main_path = '/home/pi/Pic'
newfolder_path = 'Outputs'
outputfolder_path = str(main_path + '/' + newfolder_path)
print outputfolder_path
os.chdir(str(main_path))
os.mkdir(str(newfolder_path))
os.chmod(str(newfolder_path), stat.S_IXOTH | stat.S_IWOTH | stat.S_IROTH  | stat.S_IREAD | stat.S_IWRITE | stat.S_IEXEC | stat.S_IRWXO)
lst_paths = []
from os.path import join
# to scan the directory for jpg files and to store the path to them
for (dirname, dirs, files) in os.walk(str(main_path)):
   for filename in files:
       if filename.endswith('.jpg') :
           thefile = os.path.join(dirname,filename)
           print 'path=' , thefile
           lst_paths.append(thefile)
lst_paths
print lst_paths
print len(lst_paths)

# load the image           
lst_outputs = []
number_paths = len(lst_paths)
for j in range(0,number_paths):
   image = cv2.imread(str(lst_paths[j]))

   # define the list of boundaries
   boundaries = [
	([17, 15, 100], [50, 56, 200]),
	([86, 31, 4], [220, 88, 50]),
	([25, 146, 190], [62, 174, 250]),
	([103, 86, 65], [145, 133, 128])
   ]

# loop over the boundaries
   for (lower, upper) in boundaries:
           # create NumPy arrays from the boundaries
           lower = np.array(lower, dtype = "uint8")
           upper = np.array(upper, dtype = "uint8")
    
           # find the colors within the specified boundaries and apply
           # the mask
           mask = cv2.inRange(image, lower, upper)
           output = cv2.bitwise_and(image, image, mask = mask)
           lst_outputs.append(output)
           # show the images
           cv2.imshow("image", image)
           cv2.imshow("output", output)
           cv2.waitKey(0)
           
   number_outputs = len(lst_outputs)
   lst_outputs
   filename = 'color_ouput'

   for i in range(0,number_outputs):
           cv2.imwrite(os.path.join(str(outputfolder_path),filename + str(i+1) + '.png'),lst_outputs[i])

shutil.make_archive('/home/pi/Pic/Outputs_exp', 'zip', '/home/pi/Pic/Outputs')     
