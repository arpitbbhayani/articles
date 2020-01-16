Would you shave your head and get it tattooed? Probably no, but a slave in ancient Greece was made to do so in the 440 BCE by a ruler named [Histiaeus](https://en.wikipedia.org/wiki/Histiaeus). The text that was tattooed was a secret message that Histiaeus wanted to send to his son-in-law Aristagoras in Miletus. After letting his hair grow back the slave left for Miletus and upon his arrival, the head was shaved again and the message was revealed which told Aristagoras to revolt against the Persians and start the [Ionian revolt](https://en.wikipedia.org/wiki/Ionian_Revolt).

This art of concealing message is called Steganography. The word is derived from the Greek word “στεγαυω” which means "secret writing". In modern times, steganography can be looked into as the study of the art and science of communicating in a way that hides the presence of the communication.

Steganography continued over time to develop into new levels. Invisible inks, microdots, writing behind postal stamps are all examples of steganography in its physical form. Most of these early developments happened during World War I and II where everyone was trying to outsmart each other.

![Microdots and Microdot Camera](https://user-images.githubusercontent.com/4745789/72497176-da0ccd80-3851-11ea-96b0-759d7e62f451.png)

Above image shows imcrodots and camera that generated microdots.

### Steganography and Cryptography

Since the rise of the Internet, the main concern has been security of communication. The sole focus on making everything more secure by the day lead to development of field of Cryptography that deals with hiding the meaning of message. The techniques of cryptography tries to ensure that even when the message goes into wrong hands. it is extremely difficult to extract the true meaning of the message.

Sometimes, it becomes necessary to not only hide the meaning of the message but also hide its existence, and the field that deals with this is called Steganography. Both the fields protect the information in its own way but neither alone is perfect and can be compromised. Hence a hybrid approach where we encrypt the message and then hide its presence, amplifies the security.

Today steganography is mostly used on computers with digital data, like Image, Audio, Video, Network packets, etc, acting as the carriers/cover. There are a bunch of techniques for each of the mentioned carrier but this article only aims to provide an exhaustive overview of Image Steganography.

# Image Steganography

Images are an excellent medium for concealing information because they provide a high degree of redundancy - which means that there are a lots of bits that provide accuracy far greater than necessary for object's use (display). Steganography techniques exploits these redundant bits to hide the information/payload by altering them in such a way that alterations cannot be detected easily.

## Color depth and definition

An image is just a collection of numbers that constitute different intensities in different areas of the image. It is arranged in a gird, which defines the resolution of the image, and each point on the grid is called a pixel. Each pixel is defined by a fixed number of bits and this determines its color scheme. The smallest bit depth is 8. Monochrome and greyscale images use 8 bits for each pixel and are able to display 256 different colours or shades of grey.

![8 bit grayscale monochrome image](https://user-images.githubusercontent.com/4745789/72497072-8e5a2400-3851-11ea-9b28-8705bbfea070.png)

Digital colour images are typically stored in 24-bit pixel depth and use the RGB colour model. All colour variations for the pixels of a 24-bit image are derived from three primary colours: red, green and blue, and each primary colour is represented by 8 bits. Thus each pixel can take of one color from a pallete of 16-million colours.

![24 bit color palette](https://user-images.githubusercontent.com/4745789/72497287-23f5b380-3852-11ea-96e8-e5c8ffca0c9f.png)

## Compression

When working with larger images and greater color depth, the size of raw file can become really really huge and is not possible to transmit it over internet connection. To remedy this, compressed image formats were developed which as you guessed, compresses the pixel information keeping file sizes fairly small making it efficient to transmit it over standard internet connection.

There are two types of compression techniques

### Lossy Compression
Lossy compression creates smaller files by discarding excess image data from the original image.  It removes details that are too small for the human eye to differentiate [15], resulting in close approximations of the original image, although not an exact duplicate

Example: JPEG

### Lossless Compression
Lossless compression, on the other hand, never removes any information from the original image, but instead represents data in mathematical formulas [15].  The original image’s integrity is maintained and the decompressed image output is bit-by-bit identical to the original image input.

Example: PNG, GIF and BMP

Different steganographic algorithms have been developed for both of these compression types and will be explained in the following sections.

# Spatial Domain Techniques
These techniques embed messages in the intensity of the pixels directly.
bit-wise methods that apply bit insertion and noise manipulation
lossless images are best suited
techniques are typically dependent on the image format.

## LSB Substitution
The least significant bit (in other words, the 8th bit) of some or all of the bytes inside an image is changed to a bit of the secret message.
When using a 24-bit image, a bit of each of the red, green and blue colour components can be used, since they are each represented by a byte.
In other words, one can store 3 bits in each pixel.  An 800 × 600 pixel image, can thus store a total amount of 1,440,000 bits or 180,000 bytes of embedded data [19].  For example a grid for 3 pixels of a 24-bit image can be as follows

IMAGE FOR LSB subs.

Since there are 256 possible intensities of each primary colour, changing the LSB of a pixel results in small changes in the intensity of the colours.
changes cannot be perceived by the human eye - thus the message is successfully hidden.
With a well-chosen image, one can even hide the message in the least as well as second to least significant bit and still not see the difference


This approach is very easy to detect.
A slightly more secure system is for the sender and receiver to share a secret key that specifies only certain pixels to be changed

## Randomized LSB
A slightly more secure system is for the sender and receiver to share a secret key that specifies only certain pixels to be changed

## Adaptive LSB
adaptive  LSB  substitution  based  data  hiding  method  for  image.
 it takes care of noise sensitive area for embedding
 This  method  analyzes  the  edges,  brightness  and  texture  masking  of  the cover image to calculate the number of k-bit LSB for secret data embedding. The value of k is high  at  non-sensitive  image  region  and  over  sensitive  image  area  k  value  remain  small  to  balance  overall  visual  quality  of  image.

## PVD
The pixel-value differencing (PVD) scheme uses the difference value between two consecutive pixels in a block to determine how many secret bits should be embedded.
hides large and adaptive k-LSB substitution at edge area of image and PVD for smooth region of  image.
a cover image is partitioned into non-overlapping blocks of two consecutive pixels. A difference value is calculated from the values of the two pixels in each block. All possible difference values are classified into a number of ranges. The selection of the range intervals is based on the characteristics of human vision’s sensitivity to gray value variations from smoothness to contrast. The difference value then is replaced by a new value to embed the value of a sub-stream of the secret message. The number of bits which can be embedded in a pixel pair is decided by the width of the range that the difference value belongs to. The method is designed in such a way that the modification is never out of the range interval. This method provides an easy way to produce a more imperceptible result than those yielded by simple least-significant-bit replacement methods. The embedded secret message can be extracted from the resulting stego-image without referencing the original cover image. Moreover, a pseudo-random mechanism may be used to achieve secrecy


Hiding data in the LSBs of the pixels of a gray-valued image is a common information hid-ing method that utilizes the characteristic of thehuman visionÕs insensitivity to small changes in theimage. This simple LSB embedding approach iseasy for computation, and a large amount of datacan be embedded without great quality loss. Themore LSBs are used for embedding, the moredistorted result will be produced. Not all pixels inan image can tolerate equal amounts of changeswithout causing notice to an observer. The largestnumber of LSBs whose gray values can be changedwithout producing a perceptible artifact in eachpixel is different. Changes of the gray values ofpixels in smooth areas in images are more easilynoticed by human eyes. In the embedding methodwe propose, we simply divide the cover image intoa number of non-overlapping two-pixel blocks.Each block is categorized according to the differ-ence of the gray values of the two pixels in theblock. A small difference value indicates that theblock is in a smooth area and a large one indicatesthat it is in an edged area. The pixels in edgedareas may, as mentioned previously, tolerate largerchanges of pixel values than those in the smoothareas. So, in the proposed method we embed moredata in edged areas than in the smooth areas. Andit is in this way that we keep the changes in theresulting stego-image unnoticeable.A flowchart of the proposed embedding methodis sketched in Fig. 1. The process of quantizationof the differences of the gray values of two-pixelblocks and the process of data embedding aredescribed subsequently.2.1. Quantizatio

https://people.cs.nctu.edu.tw/~whtsai/Journal%20Paper%20PDFs/Wu_&_Tsai_PRL_2003.pdf




## LSB and Palette Based Images
By definition a GIF image cannot have a bit depth greater than 8, thus the maximum number of colours that a GIF can store is 256
GIF images are indexed images where the colours used in the image are stored in a palette, sometimes referred to as a colour lookup table
Each pixel is represented as a single byte and the pixel data is an index to the colour palette



The problem with the palette approach used with GIF images is that should one change the least significant bit of a pixel, it can result in a completely different colour since the index to the colour palette is changed
If adjacent palette entries are similar, there might be little or no noticeable change, but should the adjacent palette entries be very dissimilar, the change would be eviden
One possible solution is to sort the palette so that the colour differences between consecutive colours are minimize
Another solution is to add new colours which are visually similar to the existing colours in the palette.  This requires the original image to have less unique colours than the maximum number of colour
A final solution to the problem is to use greyscale images.  In an 8-bit greyscale GIF image, there are 256 different shades of grey [14].  The changes between the colours are very gradual, making it harder to detect.

## Pixel value differencing (PVD)
## Edges based data embedding method (EBE)
## Random pixel embedding method (RPE)
## Mapping pixel to hidden data method
## Labeling or connectivity method
In [10], authors have introduced a data hiding technique where it finds out the dark area of the  image  to  hide  the  data  using  LSB.  It  converts  it  to  binary  image  and  labels  each  object  using   8   pixel   connectivity   schemes   for   hiding   data   bits.   This   method   required   highcomputation  to  find  dark  region  its  connectivity  and  has  not  tested  on  high  texture  type  of  image. Its hiding capacity totally depends on texture of image.

# Frequency Domain Techniques
In these techniques images are first transformed and then the message is embedded in the image.
involves the manipulation of algorithms and image transforms
These methods hide messages in more significant areas of the cover image, making it more robust.
independent of the image format.

Transform  domain  techniques  have  an  advantage  over  spatial  domain  techniques   as   they   hide   information   in   areas   of   the   image   that   are   less   exposed   to   compression,  cropping,  and  image  processing

## Discrete Fourier transformation technique (DFT).
## Discrete cosine transformation technique (DCT)
## Discrete Wavelet transformation technique (DWT)
## Lossless or reversible method (DCT)
## Embedding in coefficient bits

## JPEG steganography
To compress an image into JPEG format, the RGB colour representation is first converted to a YUV representation. In this representation the Y component corresponds to the luminance (or brightness) and the U and V components stand for chrominance (or colour) [1]

### JPEG Compression

According to research the human eye is more sensitive to changes in the brightness (luminance) of a pixel than to changes in its colour.
This fact is exploited by the JPEG compression by downsampling the colour data to reduce the size of the file. The colour components (U and V) are halved in horizontal and vertical directions, thus decreasing the file size by a factor of 2.

For JPEG, the Discrete Cosine Transform (DCT) is used, but similar transforms are for example the Discrete Fourier Transform (DFT).

the strength of higher frequencies can be diminished, without changing the appearance of the image.

### Steganography
Originally it was thought that steganography would not be possible to use with JPEG images.
One of the major characteristics of steganography is the fact that information is hidden in the redundant bits of an object and since redundant bits are left out when using JPEG it was feared that the hidden message would be destroyed.
somehow keep the message intact it would be difficult to embed the message without the changes being noticeable because of the harsh compression applied.

It is neither feasible nor possible to embed information in an image that uses lossy compression, since the compression would destroy all information in the process

One of these properties of JPEG is exploited to make the changes to the image invisible to the human eye.  During the DCT transformation phase of the compression algorithm, rounding errors occur in the coefficient data that are not noticeable [14].  Although this property is what classifies the algorithm as being lossy,this property can also be used to hide messages.

Thus it is important to recognize that the JPEG compression algorithm is actually divided into lossy and lossless stages.  The DCT and the quantization phase form part of the lossy stage, while the Huffman encoding used to further compress the data is lossless.  Steganography can take place between these two stages

Using the same principles of LSB insertion the message can be embedded into the least significant bits of the coefficients before applying the Huffman encoding.  By embedding the information at this stage, in the transform domain, it is extremely difficult to detect, since it is not in the visual domain.


# Spacial or Freq domain technique

## Patchwork
Patchwork is a statistical technique that uses redundant pattern encoding to embed a message in an image
The algorithm adds redundancy to the hidden information and then scatters it throughout the image.

A pseudorandom generator is used to select two areas of the image (or patches), patch A and patch B [22].  All the pixels in patch A is lightened while the pixels in patch B is darkened [22].  In other words the intensities of the pixels in the one patch are increased by a constant value, while the pixels of the other patch are decreased with the same constant value [6].  The contrast changes in this patch subset encodes one bit and the changes are typically small and imperceptible, while not changing the average luminosity

A disadvantage of the patchwork approach is that only one bit is embedded.  One can embed more bits by first dividing the image into sub-images and applying the embedding to each of them [23].  The advantage of using this technique is that the secret message is distributed over the entire image, so should one patch be destroyed, the others may still survive [17].  This however, depends on the message size, since the message can only be repeated throughout the image if it is small enough.  If the message is too big, it can only be embedded once

## Spread Spectrum
In spread spectrum techniques, hidden data is spread throughout the cover-image making it harder to detect

message is embedded in noise and then combined with the cover image to produce the stego image. Since the power of the embedded signal is much lower than the power of the cover image, the embedded image is not perceptible to the human eye or by computer analysis without access to the original image.


---

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

### Concealing the payload

Given the `text` to conceal, the following function converts the string into bytes, then into bits and finally returns it as a list.

```py
def get_bits(text):
    return list(''.join([bin(b)[2:].zfill(8) for b in
                bytes(text.encode('utf-8'))]))
```

The next step is to read image and access pixels, for this we will use PIL library. Following code reads the image and returns the pixel access object. Using this object we can access any pixel and extract its RGB values.

```py
from PIL import Image

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

The output we see above is the RGB value of the pixel. Next stuff is to write the core function that creates a new pixel map from original pixel map having LSB set with payload's bit stream. If we start substituting bits from the first pixel, how will the reader know where to stop. If there is no stop mark then reader will continue to read the last bits from the entire image which will be gibberish. To solve this we perform LSB with bit stream that represents length of the payload's bit stream. This way the reader will have to read the first 64 bits separately and consider it as the length of the payload and then read that many least significant bits.

```py

```

Now we store this pixel map on disk and this gives the image with our payload concealed in it. Here are two images, left one is the original one while the other one is the one with our payload concealed. Can you spot any difference?

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
