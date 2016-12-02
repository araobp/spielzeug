#TensorFlow

##TensorFlow for Raspberry Pi

###Installation

https://github.com/samjabrahams/tensorflow-on-raspberry-pi

###Test

####Hamster

She is my hamster "Ruby" (her name is NOT Python).

![ruby1](./ruby1.jpg)

````
pi@raspberrypi:/usr/local/lib/python2.7/dist-packages/tensorflow/models/image/imagenet $ python classify_image.py --image_file ~/tensorflow/ruby1.jpg
hamster (score = 0.45782)
panpipe, pandean pipe, syrinx (score = 0.32480)
fox squirrel, eastern fox squirrel, Sciurus niger (score = 0.01677)
mousetrap (score = 0.01429)
radiator (score = 0.00905)
```

####Nissan Note
Sample image: https://car.kurumagt.com/wp-content/uploads/2015/08/ivo20150017-300x205.jpg

```
pi@raspberrypi:/usr/local/lib/python2.7/dist-packages/tensorflow/models/image/imagenet $ python classify_image.py --image_file ~/tensorflow/note.png
minivan (score = 0.90877)
minibus (score = 0.02228)
car wheel (score = 0.00255)
beach wagon, station wagon, wagon, estate car, beach waggon, station waggon, waggon (score = 0.00153)
vacuum, vacuum cleaner (score = 0.00121)
```

Nissan Note is not a mini van, but the shape is certainly like a mini van...

##Jupyter for Raspberry Pi

https://github.com/kleinee/jns
