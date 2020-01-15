Would you shave your head and get it tattooed? Probably no, but a slave in ancient Greece was made to do so in the 440 BCE by a ruler named [Histiaeus](https://en.wikipedia.org/wiki/Histiaeus). The text that was tattooed was a secret message that Histiaeus wanted to send to his son-in-law Aristagoras in Miletus. After letting his hair grow back the slave left for Miletus and upon his arrival, the head was shaved again and the message was revealed which told Aristagoras to revolt against the Persians and start the [Ionian revolt](https://en.wikipedia.org/wiki/Ionian_Revolt).

This art of concealing message is called Steganography. The word is derived from the Greek word “στεγαυω” which means "secret writing". In modern times, steganography can be looked into as the study of the art and science of communicating in a way that hides the presence of the communication.

Steganography continued over time to develop into new levels. Invisible inks, microdots, writing behind postal stamps are all examples of Steganography in its physical form. Most of these early developments happened during World War I and II where everyone was trying to outsmart each other.

Post the digital revolution, we started manipulating media like Images, Audio, Video, Network Packets, DNA, Quantum, etc to conceal information. There are a bunch of techniques in each of the mentioned segment but in this article, we will focus on Image Steganography.

# Image Steganography

An image is composed of pixels and each pixel has 3 components for 3 primary colors Red, Blue, and Green. The perceived superposition of intensities of 3 primary colors determines the final color of the pixel. For example: When pure red is mixed with pure green we get yellow; or as shown in the diagram below, when we want an intermediary pale greenish shade we have mix red, blue and green in the right proportion.

![rgb superposition](https://user-images.githubusercontent.com/4745789/72423997-454f9480-37ab-11ea-9ffc-1513db5715ef.png)

We perceive an image as a whole, we never do it pixel by pixel. Unless there is a difference above a certain threshold we cannot comprehend the change. Image steganography uses this to conceal information. To understand steganography in detail we take a look at the Least Significant Bit (LSB) substitution method which is one of the easiest techniques to understand and implement.

## LSB Substitution

An image is made up of pixels and each pixel contains 3 primary color components - red, blue and green. The intensity of each primary color ranges from 0 to 255 (both inclusive) which means each takes up 8 bits thus each pixel takes up 3 x 8 = 24 bits of space. In LSB substitution we alter the last bit of each primary color of each pixel and when we do so the intensity alters by +-1 and our eye cannot perceive the difference. The following image shows 10 shades of red, blue and green, each differs from its neighbors by 1.

![Color +-5 for RGB](https://user-images.githubusercontent.com/4745789/72420704-37971080-37a5-11ea-9d28-54cce1efaae7.png)

Now as we have seen that altering the LSB of any color does not drastically change the colors, we can use the LSB to store one bit of information from the secret data (payload); and this is exactly was LSB Substitution does, it reads the payload bit by bit and updates the LSB of each primary color of pixel and thus without making any substantial changes to the image, conceals the information.

Take an image in which you want to conceal information. This cat image looks purrrfect for concealing information

![cat](https://user-images.githubusercontent.com/4745789/72431117-0ecd4600-37ba-11ea-9674-f108827de7e7.png)

and the secret text that we want to conceal is "I am not a cat I am a Flerken and I am the gateway to pocket dimensions.".

### Concealing the data

Given the `text` to conceal, the following function converts the string into bytes, then into bits and finally returns it as a list.

```py
def get_bits(text):
    return list(''.join([bin(b)[2:].zfill(8) for b in
                bytes(text.encode('utf-8'))]))
```

The next step is to read image and access pixels, for this we will use PIL library. Following code reads the image and returns the pixel access object. Using this object we can access any pixel and extract its RGB values.

```py
def read_image(path):
  """The function read_image, reads the image from the path `path`
  and returns the pixel map loaded in memory.

  Any exceptions raised by PIL library are unhandled.
  """

  # open the image given the path
  im = Image.open(path)

  # load the pixel map.
  pixel_map = im.load()

  # log some meta information about the image
  print('the image read from path {} has following properties'.format(path))
  print('size: {} x {}'.format(*im.size))
  print('format: {}'.format(im.format))

  # close the file. always.
  im.close()

  # return the pixel map.
  return pixel_map
```

to access pixel in 11th row and 21st column all we have to do is

```py
>>> pixel_map = read_image("path to the image.png")
>>> print(pixel_map[10,20])
(4, 6, 70)
```

The output we see above is the RGB value of the pixel.

Code to get bit stream from it

Code to update image and save

IMAGE THAT SHOWS THE DIFFERENCE

### REtrieving the data

Read first 2 bits that suggest length

Itereate and compose bit stream

bits to text

### Finding limits

Find amount of data you could conceal in an image.

And distortion you get in image due to it.

What happens when you do it for 2 bits

What happens when you do it for 3 bits

## Randomized LSB Substitution

Upgrade over predictable LSB

[a](https://pdfs.semanticscholar.org/c3c9/9ceaffb05c380b9953933945a9cd6fc1f707.pdf)
[b](https://www.lirmm.fr/~wpuech/enseignement/master_informatique/Compression_Insertion/articles/10_article_examen_PUECH_compression.pdf)

## Other methods in image

[](https://pdfs.semanticscholar.org/bb26/1e7f02f8597b37a2f71e55c2e2c21aa7575f.pdf)
[](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.364.3275&rep=rep1&type=pdf)
[](http://bit.kuas.edu.tw/~jihmsp/2011/vol2/JIH-MSP-2011-03-005.pdf)

# Other steganography in Digital Space

### Audio

### Video

### DNA

### Quantum

# Conclusion

This is the first article in the series of Steganography that detailed out Image Steganography. I hope you reaped some benefits out of it. The future articles on Steganography will talk about how Steganography is done on carriers like Audio, Network, DNA and Quantum states and will also dive into one of the most interesting applications of Steganography - a Steganographic File System. So stay tuned and watch this space for more.